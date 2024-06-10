#pragma once



namespace evo{

	//////////////////////////////////////////////////////////////////////
	// forward declarations

	template<typename T, size_t CAPACITY>
	class StaticVector;



	// template<typename T>
	// class ArrayProxyIterator;

	template<typename T>
	class ArrayProxyConstIterator;


	// template<typename T>
	// class ArrayProxyReverseIterator;

	template<typename T>
	class ArrayProxyConstReverseIterator;



	//////////////////////////////////////////////////////////////////////
	// array proxy

	// interface to an array of data
	// this is designed for use in function parameters as it can hold temporaries


	template<typename T>
	class ArrayProxy{
		public:
			using value_type = T;
			using size_type = size_t;
			using difference_type = std::ptrdiff_t;
			using reference = T&;
			using const_reference = const T&;
			using pointer = T*;
			using const_pointer = const T*;
			// using iterator = ArrayProxyIterator<T>;
			using const_iterator = ArrayProxyConstIterator<T>;
			// using reverse_iterator = ArrayProxyReverseIterator<T>;
			using const_reverse_iterator = ArrayProxyConstReverseIterator<T>;

			//////////////////////////////////////////////////////////////////////
			// constructors

			EVO_NODISCARD constexpr ArrayProxy()                 noexcept : count(0), data_ptr(nullptr) {};
			EVO_NODISCARD constexpr ArrayProxy( std::nullptr_t ) noexcept : count(0), data_ptr(nullptr) {};
			EVO_NODISCARD constexpr ArrayProxy(const T& value)   noexcept : count(1), data_ptr(&value)  {};


			EVO_NODISCARD constexpr ArrayProxy(const T* array_ptr, size_t array_count) noexcept
				: count(array_count), data_ptr(array_ptr) {};

			EVO_NODISCARD constexpr ArrayProxy(const std::initializer_list<T> init_list) noexcept
				: count(init_list.size()), data_ptr(init_list.begin()) {};

			EVO_NODISCARD constexpr ArrayProxy(const std::vector<T>& vector) noexcept
				: count(vector.size()), data_ptr(vector.data()) {};


			template<size_t COUNT>
			EVO_NODISCARD constexpr ArrayProxy(const std::array<T, COUNT>& array) noexcept
				: count(array.size()), data_ptr(array.data()) {};


			template<size_t COUNT>
			EVO_NODISCARD constexpr ArrayProxy(const std::span<T, COUNT>& span) noexcept
				: count(span.size()),  data_ptr(span.data()) {};



			template<size_t COUNT>
			EVO_NODISCARD constexpr ArrayProxy(const evo::StaticVector<T, COUNT>& static_vector) noexcept
				: count(static_vector.size()), data_ptr(static_vector.data()) {};


			template<size_t COUNT>
			EVO_NODISCARD constexpr ArrayProxy(const evo::SmallVector<T, COUNT>& small_vector) noexcept
				: count(small_vector.size()), data_ptr(small_vector.data()) {};

			//////////////////////////////////////////////////////////////////////
			// iterators

			#if defined(EVO_CONFIG_DEBUG)
				// iterators are bounds checked in debug mode

				// EVO_NODISCARD constexpr auto begin() noexcept -> iterator {
				// 	return iterator(this->data_ptr, this);
				// };

				EVO_NODISCARD constexpr auto begin() const noexcept -> const_iterator {
					return const_iterator(this->data_ptr, this);
				};

				EVO_NODISCARD constexpr auto cbegin() const noexcept -> const_iterator {
					return const_iterator(this->data_ptr, this);
				};



				// EVO_NODISCARD constexpr auto end() noexcept -> iterator {
				// 	return iterator(&this->data_ptr[this->count], this);
				// };

				EVO_NODISCARD constexpr auto end() const noexcept -> const_iterator {
					return const_iterator(&this->data_ptr[this->count], this);
				};

				EVO_NODISCARD constexpr auto cend() const noexcept -> const_iterator {
					return const_iterator(&this->data_ptr[this->count], this);
				};



				// EVO_NODISCARD constexpr auto rbegin() noexcept -> reverse_iterator {
				// 	return reverse_iterator(&this->data_ptr[this->count], this);
				// };

				EVO_NODISCARD constexpr auto rbegin() const noexcept -> const_reverse_iterator {
					return const_reverse_iterator(&this->data_ptr[this->count], this);
				};

				EVO_NODISCARD constexpr auto crbegin() const noexcept -> const_reverse_iterator {
					return const_reverse_iterator(&this->data_ptr[this->count], this);
				};



				// EVO_NODISCARD constexpr auto rend() noexcept -> reverse_iterator {
				// 	return reverse_iterator(this->data_ptr, this);
				// };

				EVO_NODISCARD constexpr auto rend() const noexcept -> const_reverse_iterator {
					return const_reverse_iterator(this->data_ptr, this);
				};

				EVO_NODISCARD constexpr auto crend() const noexcept -> const_reverse_iterator {
					return const_reverse_iterator(this->data_ptr, this);
				};



			#else
				// EVO_NODISCARD constexpr auto begin() noexcept -> iterator {
				// 	return iterator(this->data_ptr);
				// };

				EVO_NODISCARD constexpr auto begin() const noexcept -> const_iterator {
					return const_iterator(this->data_ptr);
				};

				EVO_NODISCARD constexpr auto cbegin() const noexcept -> const_iterator {
					return const_iterator(this->data_ptr);
				};



				// EVO_NODISCARD constexpr auto end() noexcept -> iterator {
				// 	return iterator(&this->data_ptr[this->count]);
				// };

				EVO_NODISCARD constexpr auto end() const noexcept -> const_iterator {
					return const_iterator(&this->data_ptr[this->count]);
				};

				EVO_NODISCARD constexpr auto cend() const noexcept -> const_iterator {
					return const_iterator(&this->data_ptr[this->count]);
				};




				// EVO_NODISCARD constexpr auto rbegin() noexcept -> reverse_iterator {
				// 	return reverse_iterator(&this->data_ptr[this->count]);
				// };

				EVO_NODISCARD constexpr auto rbegin() const noexcept -> const_reverse_iterator {
					return const_reverse_iterator(&this->data_ptr[this->count]);
				};

				EVO_NODISCARD constexpr auto crbegin() const noexcept -> const_reverse_iterator {
					return const_reverse_iterator(&this->data_ptr[this->count]);
				};



				// EVO_NODISCARD constexpr auto rend() noexcept -> reverse_iterator {
				// 	return reverse_iterator(this->data_ptr);
				// };

				EVO_NODISCARD constexpr auto rend() const noexcept -> const_reverse_iterator {
					return const_reverse_iterator(this->data_ptr);
				};

				EVO_NODISCARD constexpr auto crend() const noexcept -> const_reverse_iterator {
					return const_reverse_iterator(this->data_ptr);
				};



			#endif


			//////////////////////////////////////////////////////////////////////
			// element access


			EVO_NODISCARD constexpr auto at(size_t index) const noexcept -> const T& {
				EVO_DEBUG_ASSERT(index < this->count);

				return this->data_ptr[index];
			};


			EVO_NODISCARD constexpr auto front() const noexcept -> const T* {
				return this->data_ptr;
			};


			EVO_NODISCARD constexpr auto back() const noexcept -> const T* {
				return this->data_ptr + this->count;
			};


			EVO_NODISCARD constexpr auto operator[](size_t index) const noexcept -> const T& {
				return this->at(index);
			};


			EVO_NODISCARD constexpr auto data() const noexcept -> const T* { return this->data_ptr; };


			//////////////////////////////////////////////////////////////////////
			// observers

			EVO_NODISCARD constexpr auto size() const noexcept -> size_t { return this->count; };
			EVO_NODISCARD constexpr auto size_bytes() const noexcept -> size_t { return this->count * sizeof(T); };

			EVO_NODISCARD constexpr auto empty() const noexcept -> bool { return this->count == 0; };


			//////////////////////////////////////////////////////////////////////
			// subviews

			EVO_NODISCARD constexpr auto first(size_t num) const noexcept -> ArrayProxy<T> {
				EVO_DEBUG_ASSERT(num <= this->count); // num too big

				return ArrayProxy<T>{this->data_ptr, num};
			};

			EVO_NODISCARD constexpr auto last(size_t num) const noexcept -> ArrayProxy<T> {
				EVO_DEBUG_ASSERT(num <= this->count); // num too big

				return ArrayProxy<T>{&this->data_ptr[count - num], num};
			};

			EVO_NODISCARD constexpr auto subarr(size_t start, size_t end) const noexcept -> ArrayProxy<T> {
				EVO_DEBUG_ASSERT(end <= this->count); // end it out of bounds
				EVO_DEBUG_ASSERT(start <= end); // start cannot be after the end

				return ArrayProxy<T>{&this->data_ptr[start], end - start + 1};
			};



	
		private:
			const size_t count;
			const T* data_ptr;
	};


	//////////////////////////////////////////////////////////////////////
	// iterators

	// template<typename T>
	// class ArrayProxyIterator{
	// 	public:
	// 		#if defined(EVO_CONFIG_DEBUG)
	// 			ArrayProxyIterator(T* ptr, const ArrayProxy<T>* parent_ptr) noexcept : iter(ptr), parent(parent_ptr) {};
	// 			ArrayProxyIterator(const T* ptr, const ArrayProxy<T>* parent_ptr) noexcept : iter(const_cast<T*>(ptr)), parent(parent_ptr) {};

	// 		#else
	// 			ArrayProxyIterator(T* ptr) noexcept : iter(ptr) {};
	// 			ArrayProxyIterator(const T* ptr) noexcept : iter(const_cast<T*>(ptr)) {};

	// 		#endif

	// 		~ArrayProxyIterator() = default;


	// 		constexpr auto operator++() noexcept -> ArrayProxyIterator<T>& {
	// 			EVO_DEBUG_ASSERT(this->iter < this->parent->back()); // already at end

	// 			this->iter++;
	// 			return *this;
	// 		};

	// 		constexpr auto operator++(int) const noexcept -> ArrayProxyIterator<T> {
	// 			EVO_DEBUG_ASSERT(this->iter < this->parent->back()); // already at end

	// 			ArrayProxyIterator iterator = *this;
	// 			++(*this);
	// 			return iterator;
	// 		};


	// 		constexpr auto operator--() noexcept -> ArrayProxyIterator<T>& {
	// 			EVO_DEBUG_ASSERT(this->iter < this->parent->front()); // already at beginning

	// 			this->iter--;
	// 			return *this;
	// 		};

	// 		constexpr auto operator--(int) const noexcept -> ArrayProxyIterator<T> {
	// 			EVO_DEBUG_ASSERT(this->iter < this->parent->front()); // already at beginning

	// 			ArrayProxyIterator iterator = *this;
	// 			--(*this);
	// 			return iterator;
	// 		};



	// 		EVO_NODISCARD constexpr auto operator*() const noexcept -> T& {
	// 			return *this->iter;
	// 		};

	// 		EVO_NODISCARD constexpr auto operator->() const noexcept -> T* {
	// 			return this->iter;
	// 		};

	// 		EVO_NODISCARD constexpr auto operator==(const ArrayProxyIterator<T>& rhs) const noexcept -> bool {
	// 			return this->iter == rhs.iter;
	// 		};

	// 		EVO_NODISCARD constexpr auto operator!=(const ArrayProxyIterator<T>& rhs) const noexcept -> bool {
	// 			return this->iter != rhs.iter;
	// 		};

	
	// 	private:
	// 		T* iter;

	// 		#if defined(EVO_CONFIG_DEBUG)
	// 			const ArrayProxy<T>* parent;
	// 		#endif
	// };




	template<typename T>
	class ArrayProxyConstIterator{
		public:
			#if defined(EVO_CONFIG_DEBUG)
				ArrayProxyConstIterator(const T* ptr, const ArrayProxy<T>* parent_ptr) noexcept : iter(ptr), parent(parent_ptr) {};
			#else
				ArrayProxyConstIterator(const T* ptr) noexcept : iter(ptr) {};
			#endif

			~ArrayProxyConstIterator() = default;


			constexpr auto operator++() noexcept -> ArrayProxyConstIterator<T>& {
				EVO_DEBUG_ASSERT(this->iter < this->parent->back()); // already at end

				this->iter++;
				return *this;
			};

			constexpr auto operator++(int) const noexcept -> ArrayProxyConstIterator<T> {
				EVO_DEBUG_ASSERT(this->iter < this->parent->back()); // already at end

				ArrayProxyConstIterator iterator = *this;
				++(*this);
				return iterator;
			};



			constexpr auto operator--() noexcept -> ArrayProxyConstIterator<T>& {
				EVO_DEBUG_ASSERT(this->iter < this->parent->back()); // already at end

				this->iter--;
				return *this;
			};

			constexpr auto operator--(int) const noexcept -> ArrayProxyConstIterator<T> {
				EVO_DEBUG_ASSERT(this->iter < this->parent->front()); // already at beginning

				ArrayProxyConstIterator iterator = *this;
				--(*this);
				return iterator;
			};



			EVO_NODISCARD constexpr auto operator*() const noexcept -> const T& {
				return *this->iter;
			};

			EVO_NODISCARD constexpr auto operator->() const noexcept -> const T* {
				return this->iter;
			};

			EVO_NODISCARD constexpr auto operator==(const ArrayProxyConstIterator<T>& rhs) const noexcept -> bool {
				return this->iter == rhs.iter;
			};

			EVO_NODISCARD constexpr auto operator!=(const ArrayProxyConstIterator<T>& rhs) const noexcept -> bool {
				return this->iter != rhs.iter;
			};

	
		private:
			const T* iter;

			#if defined(EVO_CONFIG_DEBUG)
				const ArrayProxy<T>* parent;
			#endif
	};







	// template<typename T>
	// class ArrayProxyReverseIterator{
	// 	public:
	// 		#if defined(EVO_CONFIG_DEBUG)
	// 			ArrayProxyReverseIterator(T* ptr, const ArrayProxy<T>* parent_ptr) noexcept : iter(ptr), parent(parent_ptr) {};
	// 			ArrayProxyReverseIterator(const T* ptr, const ArrayProxy<T>* parent_ptr) noexcept : iter(const_cast<T*>(ptr)), parent(parent_ptr) {};

	// 		#else
	// 			ArrayProxyReverseIterator(T* ptr) noexcept : iter(ptr) {};
	// 			ArrayProxyReverseIterator(const T* ptr) noexcept : iter(const_cast<T*>(ptr)) {};

	// 		#endif

	// 		~ArrayProxyReverseIterator() = default;


	// 		constexpr auto operator++() noexcept -> ArrayProxyReverseIterator<T>& {
	// 			EVO_DEBUG_ASSERT(this->iter < this->parent->front()); // already at beginning

	// 			this->iter--;
	// 			return *this;
	// 		};

	// 		constexpr auto operator++(int) const noexcept -> ArrayProxyReverseIterator<T> {
	// 			EVO_DEBUG_ASSERT(this->iter < this->parent->front()); // already at beginning

	// 			ArrayProxyReverseIterator iterator = *this;
	// 			--(*this);
	// 			return iterator;
	// 		};


	// 		constexpr auto operator--() noexcept -> ArrayProxyReverseIterator<T>& {
	// 			EVO_DEBUG_ASSERT(this->iter < this->parent->back()); // already at end

	// 			this->iter++;
	// 			return *this;
	// 		};

	// 		constexpr auto operator--(int) const noexcept -> ArrayProxyReverseIterator<T> {
	// 			EVO_DEBUG_ASSERT(this->iter < this->parent->back()); // already at end

	// 			ArrayProxyReverseIterator iterator = *this;
	// 			++(*this);
	// 			return iterator;
	// 		};



	// 		EVO_NODISCARD constexpr auto operator*() const noexcept -> T& {
	// 			return *this->iter;
	// 		};

	// 		EVO_NODISCARD constexpr auto operator->() const noexcept -> T* {
	// 			return this->iter;
	// 		};

	// 		EVO_NODISCARD constexpr auto operator==(const ArrayProxyReverseIterator<T>& rhs) const noexcept -> bool {
	// 			return this->iter == rhs.iter;
	// 		};

	// 		EVO_NODISCARD constexpr auto operator!=(const ArrayProxyReverseIterator<T>& rhs) const noexcept -> bool {
	// 			return this->iter != rhs.iter;
	// 		};

	
	// 	private:
	// 		T* iter;

	// 		#if defined(EVO_CONFIG_DEBUG)
	// 			const ArrayProxy<T>* parent;
	// 		#endif
	// };




	template<typename T>
	class ArrayProxyConstReverseIterator{
		public:
			#if defined(EVO_CONFIG_DEBUG)
				ArrayProxyConstReverseIterator(const T* ptr, const ArrayProxy<T>* parent_ptr) noexcept : iter(ptr), parent(parent_ptr) {};
			#else
				ArrayProxyConstReverseIterator(const T* ptr) noexcept : iter(ptr) {};
			#endif

			~ArrayProxyConstReverseIterator() = default;




			constexpr auto operator++() noexcept -> ArrayProxyConstReverseIterator<T>& {
				EVO_DEBUG_ASSERT(this->iter < this->parent->front()); // already at beginning

				this->iter--;
				return *this;
			};

			constexpr auto operator++(int) const noexcept -> ArrayProxyConstReverseIterator<T> {
				EVO_DEBUG_ASSERT(this->iter < this->parent->back()); // already at end

				ArrayProxyConstReverseIterator iterator = *this;
				--(*this);
				return iterator;
			};



			constexpr auto operator--() noexcept -> ArrayProxyConstReverseIterator<T>& {
				EVO_DEBUG_ASSERT(this->iter < this->parent->back()); // already at end

				this->iter++;
				return *this;
			};

			constexpr auto operator--(int) const noexcept -> ArrayProxyConstReverseIterator<T> {
				EVO_DEBUG_ASSERT(this->iter < this->parent->front()); // already at beginning

				ArrayProxyConstReverseIterator iterator = *this;
				++(*this);
				return iterator;
			};



			EVO_NODISCARD constexpr auto operator*() const noexcept -> const T& {
				return *this->iter;
			};

			EVO_NODISCARD constexpr auto operator->() const noexcept -> const T* {
				return this->iter;
			};

			EVO_NODISCARD constexpr auto operator==(const ArrayProxyConstReverseIterator<T>& rhs) const noexcept -> bool {
				return this->iter == rhs.iter;
			};

			EVO_NODISCARD constexpr auto operator!=(const ArrayProxyConstReverseIterator<T>& rhs) const noexcept -> bool {
				return this->iter != rhs.iter;
			};

	
		private:
			const T* iter;

			#if defined(EVO_CONFIG_DEBUG)
				const ArrayProxy<T>* parent;
			#endif
	};





	
};
