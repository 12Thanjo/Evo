#pragma once



namespace evo{


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
			using const_iterator = ConstIterator<T>;
			using const_reverse_iterator = ConstReverseIterator<T>;

			//////////////////////////////////////////////////////////////////////
			// constructors

			[[nodiscard]] constexpr ArrayProxy()                 noexcept : count(0), data_ptr(nullptr) {};
			[[nodiscard]] constexpr ArrayProxy( std::nullptr_t ) noexcept : count(0), data_ptr(nullptr) {};
			[[nodiscard]] constexpr ArrayProxy(const T& value)   noexcept : count(1), data_ptr(&value)  {};


			[[nodiscard]] constexpr ArrayProxy(const T* array_ptr, size_t array_count) noexcept
				: count(array_count), data_ptr(array_ptr) {};

			[[nodiscard]] constexpr ArrayProxy(const std::initializer_list<T> init_list) noexcept
				: count(init_list.size()), data_ptr(init_list.begin()) {};

			[[nodiscard]] constexpr ArrayProxy(const std::vector<T>& vector) noexcept
				: count(vector.size()), data_ptr(vector.data()) {};


			template<size_t COUNT>
			[[nodiscard]] constexpr ArrayProxy(const std::array<T, COUNT>& array) noexcept
				: count(array.size()), data_ptr(array.data()) {};


			template<size_t COUNT>
			[[nodiscard]] constexpr ArrayProxy(const std::span<T, COUNT>& span) noexcept
				: count(span.size()),  data_ptr(span.data()) {};



			template<size_t COUNT>
			[[nodiscard]] constexpr ArrayProxy(const StaticVector<T, COUNT>& static_vector) noexcept
				: count(static_vector.size()), data_ptr(static_vector.data()) {};


			template<size_t COUNT>
			[[nodiscard]] constexpr ArrayProxy(const SmallVector<T, COUNT>& small_vector) noexcept
				: count(small_vector.size()), data_ptr(small_vector.data()) {};


			template<size_t COUNT>
			[[nodiscard]] constexpr ArrayProxy(const UnmovableVector<T>& unmovable_vector) noexcept
				: count(unmovable_vector.size()), data_ptr(unmovable_vector.data()) {};


			//////////////////
			// copy and move

			[[nodiscard]] constexpr ArrayProxy(const ArrayProxy<T>&) = default;

			constexpr auto operator=(const ArrayProxy<T>& rhs) -> ArrayProxy<T>& {
				std::construct_at(this, rhs);
				return *this;
			}


			[[nodiscard]] constexpr ArrayProxy(ArrayProxy<T>&&) = default;

			constexpr auto operator=(ArrayProxy<T>&& rhs) -> ArrayProxy<T>& {
				std::construct_at(this, std::move(rhs));
				return *this;
			}


			//////////////////////////////////////////////////////////////////////
			// iterators

			[[nodiscard]] constexpr auto begin()  const noexcept -> const_iterator { return const_iterator{this->data()}; };
			[[nodiscard]] constexpr auto cbegin() const noexcept -> const_iterator { return const_iterator{this->data()}; };

			[[nodiscard]] constexpr auto end()  const noexcept -> const_iterator { return const_iterator{&this->data()[this->size()]}; };
			[[nodiscard]] constexpr auto cend() const noexcept -> const_iterator { return const_iterator{&this->data()[this->size()]}; };


			[[nodiscard]] constexpr auto rbegin()  const noexcept -> const_reverse_iterator { return const_reverse_iterator{&this->data()[this->size()-1]}; };
			[[nodiscard]] constexpr auto crbegin() const noexcept -> const_reverse_iterator { return const_reverse_iterator{&this->data()[this->size()-1]}; };

			[[nodiscard]] constexpr auto rend()  const noexcept -> const_reverse_iterator { return const_reverse_iterator{this->data()-1}; };
			[[nodiscard]] constexpr auto crend() const noexcept -> const_reverse_iterator { return const_reverse_iterator{this->data()-1}; };

		


			//////////////////////////////////////////////////////////////////////
			// element access


			[[nodiscard]] constexpr auto at(size_t index) const noexcept -> const T& {
				EVO_DEBUG_ASSERT(index < this->count);

				return this->data_ptr[index];
			};


			[[nodiscard]] constexpr auto front() const noexcept -> const T& {
				return this->data_ptr[0];
			};


			[[nodiscard]] constexpr auto back() const noexcept -> const T& {
				return this->data_ptr[this->size() - 1];
			};


			[[nodiscard]] constexpr auto operator[](size_t index) const noexcept -> const T& {
				return this->at(index);
			};


			[[nodiscard]] constexpr auto data() const noexcept -> const T* { return this->data_ptr; };


			//////////////////////////////////////////////////////////////////////
			// observers

			[[nodiscard]] constexpr auto size() const noexcept -> size_t { return this->count; };
			[[nodiscard]] constexpr auto size_bytes() const noexcept -> size_t { return this->count * sizeof(T); };

			[[nodiscard]] constexpr auto empty() const noexcept -> bool { return this->count == 0; };


			//////////////////////////////////////////////////////////////////////
			// subviews

			[[nodiscard]] constexpr auto first(size_t num) const noexcept -> ArrayProxy<T> {
				EVO_DEBUG_ASSERT(num <= this->count); // num too big

				return ArrayProxy<T>{this->data_ptr, num};
			};

			[[nodiscard]] constexpr auto last(size_t num) const noexcept -> ArrayProxy<T> {
				EVO_DEBUG_ASSERT(num <= this->count); // num too big

				return ArrayProxy<T>{&this->data_ptr[count - num], num};
			};

			[[nodiscard]] constexpr auto subarr(size_t start, size_t num_elems) const noexcept -> ArrayProxy<T> {
				EVO_DEBUG_ASSERT(start <= this->count); // sub-arr is not in-bounds
				EVO_DEBUG_ASSERT(start + num_elems <= this->count); // sub-arr is not in-bounds
				EVO_DEBUG_ASSERT(num_elems != 0);

				return ArrayProxy<T>{&this->data_ptr[start], num_elems};
			};



			//////////////////////////////////////////////////////////////////////
			// operators

			[[nodiscard]] constexpr auto operator==(const ArrayProxy<T>& rhs) const -> bool {
				if(this->size() != rhs.size()){ return false; }

				for(size_t i = 0; i < this->size(); i+=1){
					if(this->at(i) != rhs[i]){ return false; }
				}

				return true;
			}


	
		private:
			const T* data_ptr;
			const size_t count;
	};

	
};
