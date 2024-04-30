#pragma once

#include <array>

namespace evo{
	
	// reference: https://en.cppreference.com/w/cpp/container/vector
	// 			  https://en.cppreference.com/w/cpp/container/array
	// I attempted to make this somewhat like a what std implementation might be


	//////////////////////////////////////////////////////////////////////
	// static vector

	template<typename T, size_t CAPACITY>
	class StaticVector{
		public:
			using value_type             = T;
			using size_type              = CapacityType<CAPACITY>::type;
			using difference_type        = std::ptrdiff_t;
			using reference              = T&;
			using const_reference        = const T&;
			using pointer                = T*;
			using const_pointer          = const T*;
			using iterator               = Iterator<T>;
			using const_iterator         = ConstIterator<T>;
			using reverse_iterator       = ReverseIterator<T>;
			using const_reverse_iterator = ConstReverseIterator<T>;


			//////////////////////////////////////////////////////////////////////
			// constructors / destructors


			EVO_NODISCARD constexpr StaticVector() noexcept = default;
			constexpr ~StaticVector() noexcept { this->clear(); };


			///////////////////////////////////
			// copy

			EVO_NODISCARD constexpr StaticVector(const StaticVector<T, CAPACITY>& rhs) noexcept : current_size(rhs.size()) {
				for(size_t i = 0; i < this->size(); i+=1){
					this->data_block[i] = rhs[i];
				}
			};


			constexpr auto operator=(const StaticVector<T, CAPACITY>& rhs) noexcept -> StaticVector<T, CAPACITY>& {
				this->current_size = rhs.size();

				for(size_t i = 0; i < this->size(); i+=1){
					this->data_block[i] = rhs[i];
				}

				return *this;
			};


			///////////////////////////////////
			// move

			EVO_NODISCARD constexpr StaticVector(StaticVector<T, CAPACITY>&& rhs) noexcept : current_size(std::exchange(rhs.current_size, 0)) {
				for(size_t i = 0; i < this->size(); i+=1){
					this->data_block[i] = std::move(rhs[i]);
				}
			};


			constexpr auto operator=(StaticVector<T, CAPACITY>&& rhs) noexcept -> StaticVector<T, CAPACITY>& {
				this->current_size = std::exchange(rhs.current_size, 0);

				for(size_t i = 0; i < this->size(); i+=1){
					this->data_block[i] = std::move(rhs[i]);
				}

				return *this;
			};


			///////////////////////////////////
			// deleted special member functions

			constexpr StaticVector(const StaticVector<T, CAPACITY>&&) = delete;
			constexpr StaticVector<T, CAPACITY>& operator=(const StaticVector<T, CAPACITY>&&) = delete;


			///////////////////////////////////
			// construct from initializer list

			EVO_NODISCARD constexpr StaticVector(std::initializer_list<T> init_list) noexcept : current_size(init_list.size()) {
				EVO_DEBUG_ASSERT(init_list.size() < CAPACITY);

				for(size_t i = 0; i < init_list.size(); i+=1){
					this->data_block[i] = std::move(*(init_list.begin() + i));
				}
			};

			constexpr auto operator=(std::initializer_list<T> init_list) noexcept -> StaticVector<T, CAPACITY>& {
				EVO_DEBUG_ASSERT(init_list.size() < CAPACITY);
				
				this->resize(0);

				for(size_t i = 0; i < init_list.size(); i+=1){
					this->data_block[i] = std::move(*(init_list.begin() + i));
				}

				this->current_size = init_list.size();

				return *this;
			};





			//////////////////////////////////////////////////////////////////////
			// element access

			///////////////////////////////////
			// at

			EVO_NODISCARD constexpr auto at(size_t index) noexcept -> T& {
				EVO_DEBUG_ASSERT(index < this->current_size);

				return this->data_block[index];
			};

			EVO_NODISCARD constexpr auto at(size_t index) const noexcept -> const T& {
				EVO_DEBUG_ASSERT(index < this->current_size);

				return this->data_block[index];
			};


			template<std::enable_if<std::is_same_v<size_type, size_t>> = false>
			EVO_NODISCARD constexpr auto at(size_type index) noexcept -> T& { return this->at(size_t(index)); };

			template<std::enable_if<std::is_same_v<size_type, size_t>> = false>
			EVO_NODISCARD constexpr auto at(size_type index) const noexcept -> const T& { return this->at(size_t(index)); };



			///////////////////////////////////
			// operator[]

			EVO_NODISCARD constexpr auto operator[](size_t index)       noexcept ->       T& { return this->at(index); };
			EVO_NODISCARD constexpr auto operator[](size_t index) const noexcept -> const T& { return this->at(index); };

			template<std::enable_if<std::is_same_v<size_type, size_t>> = false>
			EVO_NODISCARD constexpr auto operator[](size_type index)       noexcept ->       T& { return this->at(index); };

			template<std::enable_if<std::is_same_v<size_type, size_t>> = false>
			EVO_NODISCARD constexpr auto operator[](size_type index) const noexcept -> const T& { return this->at(index); };


			///////////////////////////////////
			// front

			EVO_NODISCARD constexpr auto front() noexcept -> T& {
				return *this->data_block;
			};

			EVO_NODISCARD constexpr auto front() const noexcept -> const T& {
				return *this->data_block;
			};


			///////////////////////////////////
			// front

			EVO_NODISCARD constexpr auto back() noexcept -> T& {
				return this->data_block[this->size() - 1];
			};

			EVO_NODISCARD constexpr auto back() const noexcept -> const T& {
				return this->data_block[this->size() - 1];
			};


			///////////////////////////////////
			// data

			EVO_NODISCARD constexpr auto data() noexcept -> T* {
				return this->data_block;
			};

			EVO_NODISCARD constexpr auto data() const noexcept -> const T* {
				return this->data_block;
			};


			//////////////////////////////////////////////////////////////////////
			// iterators

			EVO_NODISCARD constexpr auto begin()        noexcept -> iterator       { return iterator{this->data()};       };
			EVO_NODISCARD constexpr auto begin()  const noexcept -> const_iterator { return const_iterator{this->data()}; };
			EVO_NODISCARD constexpr auto cbegin() const noexcept -> const_iterator { return const_iterator{this->data()}; };

			EVO_NODISCARD constexpr auto end()        noexcept -> iterator       { return iterator{&this->data()[this->size()]};       };
			EVO_NODISCARD constexpr auto end()  const noexcept -> const_iterator { return const_iterator{&this->data()[this->size()]}; };
			EVO_NODISCARD constexpr auto cend() const noexcept -> const_iterator { return const_iterator{&this->data()[this->size()]}; };


			EVO_NODISCARD constexpr auto rbegin()        noexcept -> reverse_iterator       {return reverse_iterator{&this->data()[this->size()-1]};      };
			EVO_NODISCARD constexpr auto rbegin()  const noexcept -> const_reverse_iterator {return const_reverse_iterator{&this->data()[this->size()-1]};};
			EVO_NODISCARD constexpr auto crbegin() const noexcept -> const_reverse_iterator {return const_reverse_iterator{&this->data()[this->size()-1]};};

			EVO_NODISCARD constexpr auto rend()        noexcept -> reverse_iterator       { return reverse_iterator{this->data()[-1]};       };
			EVO_NODISCARD constexpr auto rend()  const noexcept -> const_reverse_iterator { return const_reverse_iterator{this->data()[-1]}; };
			EVO_NODISCARD constexpr auto crend() const noexcept -> const_reverse_iterator { return const_reverse_iterator{this->data()[-1]}; };



			//////////////////////////////////////////////////////////////////////
			// capacity

			EVO_NODISCARD constexpr auto empty() const noexcept -> bool { return this->current_size == 0; };

			EVO_NODISCARD constexpr auto size() const noexcept -> size_t { return size_t(this->current_size); };

			EVO_NODISCARD constexpr auto max_size() const noexcept -> size_t { return size_t(this->current_size); };

			EVO_NODISCARD constexpr auto capacity() const noexcept -> size_t { return size_t(CAPACITY); };


			//////////////////////////////////////////////////////////////////////
			// modify

			///////////////////////////////////
			// clear

			constexpr auto clear() noexcept -> void {
				for(size_t i = 0; i < this->current_size; i+=1){
					std::destroy_at(&this->data_block[i]);
				}

				this->current_size = 0;
			};


			///////////////////////////////////
			// insert

			constexpr auto insert(const_iterator pos, const T& value) noexcept -> iterator {
				EVO_DEBUG_ASSERT(this->current_size < this->capacity());

				*this->end() = value;

				this->current_size += 1;

				const auto begin = this->rbegin();
				const auto end = reverse_iterator{const_cast<T*>(&*pos)};


				for(reverse_iterator i = begin; i != end; ++i){
					std::swap(*i, *std::next(i));
				}

				return iterator{const_cast<T*>(&*pos)};
			};


			constexpr auto insert(const_iterator pos, T&& value) noexcept -> iterator {
				EVO_DEBUG_ASSERT(this->current_size < this->capacity());

				*this->end() = std::move(value);

				this->current_size += 1;

				const auto begin = this->rbegin();
				const auto end = reverse_iterator{const_cast<T*>(&*pos)};


				for(reverse_iterator i = begin; i != end; ++i){
					std::swap(*i, *std::next(i));
				}

				return iterator{const_cast<T*>(&*pos)};
			};


			// not implemented yet: constexpr auto insert(const_iterator pos, size_type count, const T& value) noexcept -> iterator
			// not implemented yet: template<class InputIt> constexpr auto insert(const_iterator pos, InputIt first, InputIt last) noexcept -> iterator
			// not implemented yet: constexpr auto insert(const_iterator pos, std::initializer_list<T> ilist) noexcept -> void;


			// not implemented yet: insert_range


			///////////////////////////////////
			// emplace

			template<class... Args>
			constexpr auto emplace(const_iterator pos, Args&&... args) noexcept -> iterator {
				EVO_DEBUG_ASSERT(this->current_size < this->capacity());

				std::construct_at(&*this->end(), std::forward<Args>(args)...);

				this->current_size += 1;

				const auto begin = this->rbegin();
				const auto end = reverse_iterator{const_cast<T*>(&*pos)};


				for(reverse_iterator i = begin; i != end; ++i){
					std::swap(*i, *std::next(i));
				}

				return iterator{const_cast<T*>(&*pos)};
			};


			///////////////////////////////////
			// erase

			constexpr auto erase(const_iterator pos) noexcept -> iterator {
				std::destroy_at(&*pos);

				iterator output = [&](){
					if(pos == this->end()){
						return --this->end();
					}else{
						return iterator{const_cast<T*>(&*pos)};
					}
				}();

				for(iterator i = output; i != this->end(); ++i){
					*std::prev(i) = std::move(*i);
				}

				return output;
			};

			// not implemented yet: constexpr auto erase(const_iterator first, const_iterator last) noexcept -> iterator


			///////////////////////////////////
			// push_back

			constexpr auto push_back(const T& value) noexcept -> void {
				EVO_DEBUG_ASSERT(this->size() < CAPACITY);

				this->data_block[this->size()] = value;
				this->current_size += 1;
			};

			constexpr auto push_back(T&& value) noexcept -> void {
				EVO_DEBUG_ASSERT(this->size() < CAPACITY);

				this->data_block[this->size()] = std::move(value);
				this->current_size += 1;
			};


			///////////////////////////////////
			// emplace_back

			template<class... Args>
			constexpr auto emplace_back(Args&&... args) noexcept -> T& {
				EVO_DEBUG_ASSERT(this->size() < CAPACITY);

				T& new_object = this->data_block[this->size()];
				std::construct_at(&new_object, std::forward<Args>(args)...);

				this->current_size += 1;
				return new_object;
			};


			// not implemented yet: append_range

			///////////////////////////////////
			// pop_back

			constexpr auto pop_back() noexcept -> void {
				EVO_DEBUG_ASSERT(this->size() > 0);

				this->current_size -= 1;
				std::destroy_at(&this->back());
			};


			///////////////////////////////////
			// resize

			template<std::enable_if<std::is_same_v<size_type, size_t>> = false>
			constexpr auto resize(size_type new_size) noexcept -> void {
				this->resize(size_t(new_size));
			};

			constexpr auto resize(size_t new_size) noexcept -> void {
				EVO_DEBUG_ASSERT(new_size < CAPACITY);

				if(new_size < this->size()){
					for(size_type i = new_size; i < this->size(); i++){
						std::destroy_at(&this->data_block[i]);
					}
				}else{
					for(size_type i = new_size; i < this->size(); i++){
						std::construct_at(&this->data_block[i]);
					}
				}

				this->current_size = new_size;
			};


			// not implemented yet: swap

	
		private:
			union{
				byte data_block_dummy = 0;
				T data_block[CAPACITY];
			};
			size_type current_size = 0;
			
	};





};


