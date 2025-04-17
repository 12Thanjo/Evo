#pragma once


namespace evo{

	// https://devblogs.microsoft.com/oldnewthing/20190710-00/?p=102678
	template<typename, typename = void>
	constexpr bool is_type_complete_v = false;

	template<typename T>
	constexpr bool is_type_complete_v<T, std::void_t<decltype(sizeof(T))>> = true;



	template<typename T>
	EVO_NODISCARD constexpr auto optimal_small_vector_size() noexcept -> size_t {
		struct BigData{
			size_t size;
			size_t capacity;
			T* data;
		};

		const size_t max_optimal_small_buffer_size = sizeof(BigData) - 1;

		if constexpr(is_type_complete_v<T> == false){
			return 0;
		}else if constexpr(sizeof(T) > max_optimal_small_buffer_size){
			return 0;
		}else{
			return max_optimal_small_buffer_size / sizeof(T);
		}
	};


	template<typename T, size_t SMALL_CAPACITY = optimal_small_vector_size<T>()>
	class SmallVector{
		public:
			using value_type             = T;
			using size_type              = size_t;
			using difference_type        = std::ptrdiff_t;
			using reference              = T&;
			using const_reference        = const T&;
			using pointer                = T*;
			using const_pointer          = const T*;
			using iterator               = Iterator<T>;
			using const_iterator         = ConstIterator<T>;
			using reverse_iterator       = ReverseIterator<T>;
			using const_reverse_iterator = ConstReverseIterator<T>;


			static constexpr bool USES_SMALL_BUFFER = SMALL_CAPACITY != 0;


			//////////////////////////////////////////////////////////////////////
			// constructors / destructors

			EVO_NODISCARD constexpr SmallVector() noexcept {
				if constexpr(USES_SMALL_BUFFER){
					this->set_small_size(0);
				}else{
					std::memset(&this->contents.big, 0, sizeof(BigData));
				}
			}

			constexpr ~SmallVector() noexcept {
				std::destroy_n(this->data(), this->size());

				if constexpr(USES_SMALL_BUFFER){
					if(this->is_big()){
						std::free(this->contents.big.data);
					}
				}else{
					std::free(this->contents.big.data);
				}
			}


			///////////////////////////////////
			// copy

			EVO_NODISCARD constexpr SmallVector(const SmallVector<T, SMALL_CAPACITY>& rhs) noexcept {
				std::construct_at(this, rhs.begin(), rhs.end());
			};

			constexpr auto operator=(const SmallVector<T, SMALL_CAPACITY>& rhs) noexcept -> SmallVector<T, SMALL_CAPACITY>& {
				std::destroy_at(this);
				std::construct_at(this, rhs.begin(), rhs.end());

				return *this;
			};


			///////////////////////////////////
			// move

			EVO_NODISCARD constexpr SmallVector(SmallVector<T, SMALL_CAPACITY>&& rhs) noexcept {
				if constexpr(USES_SMALL_BUFFER){
					if(rhs.is_small()){
						this->set_small_size(static_cast<SmallSizeType>(rhs.size()));
						std::move(rhs.begin(), rhs.end(), this->get_small_data());
						rhs.clear();

					}else{
						std::memcpy(this, &rhs, sizeof(SmallVector<T, SMALL_CAPACITY>));
						std::memset(&rhs, 0, sizeof(SmallVector<T, SMALL_CAPACITY>));
					}

				}else{
					std::memcpy(this, &rhs, sizeof(SmallVector<T, SMALL_CAPACITY>));
					std::memset(&rhs, 0, sizeof(SmallVector<T, SMALL_CAPACITY>));
				}
			};


			constexpr auto operator=(SmallVector<T, SMALL_CAPACITY>&& rhs) noexcept -> SmallVector<T, SMALL_CAPACITY>& {
				std::destroy_at(this);
				std::construct_at(this, std::move(rhs));

				return *this;
			};


			///////////////////////////////////
			// deleted special member functions

			SmallVector(const SmallVector<T, SMALL_CAPACITY>&&) = delete;
			SmallVector<T, SMALL_CAPACITY>& operator=(const SmallVector<T, SMALL_CAPACITY>&&) = delete;


			///////////////////////////////////
			// construct from initializer list

			EVO_NODISCARD constexpr SmallVector(std::initializer_list<T> init_list) noexcept {
				std::construct_at(this, init_list.begin(), init_list.end());
			};

			constexpr auto operator=(std::initializer_list<T> init_list) noexcept -> SmallVector<T, SMALL_CAPACITY>& {
				std::destroy_at(this);
				std::construct_at(this, init_list.begin(), init_list.end());

				return *this;
			};


			///////////////////////////////////
			// construct from iterators

			template<class InputIt>
			EVO_NODISCARD constexpr SmallVector(InputIt first, InputIt last) noexcept {
				std::construct_at(this);

				this->reserve(std::distance(first, last));
				for(auto i = first; i != last; ++i){
					this->emplace_back(*i);
				}
			};





			//////////////////////////////////////////////////////////////////////
			// element access

			///////////////////////////////////
			// at

			EVO_NODISCARD constexpr auto at(size_t index) noexcept -> T& {
				EVO_DEBUG_ASSERT(index < this->size());

				return this->data()[index];
			};

			EVO_NODISCARD constexpr auto at(size_t index) const noexcept -> const T& {
				EVO_DEBUG_ASSERT(index < this->size());

				return this->data()[index];
			};


			///////////////////////////////////
			// operator[]

			EVO_NODISCARD constexpr auto operator[](size_t index)       noexcept ->       T& { return this->at(index); };
			EVO_NODISCARD constexpr auto operator[](size_t index) const noexcept -> const T& { return this->at(index); };


			///////////////////////////////////
			// front

			EVO_NODISCARD constexpr auto front() noexcept -> T& {
				return this->at(0);
			};

			EVO_NODISCARD constexpr auto front() const noexcept -> const T& {
				return this->at(0);
			};


			///////////////////////////////////
			// back

			EVO_NODISCARD constexpr auto back() noexcept -> T& {
				return this->at(this->size() - 1);
			};

			EVO_NODISCARD constexpr auto back() const noexcept -> const T& {
				return this->at(this->size() - 1);
			};


			///////////////////////////////////
			// data

			EVO_NODISCARD constexpr auto data() noexcept -> T* {
				if constexpr(USES_SMALL_BUFFER){
					if(this->is_small()){
						return this->get_small_data();
					}else{
						return this->contents.big.data;
					}
				}else{
					return this->contents.big.data;
				}
			};

			EVO_NODISCARD constexpr auto data() const noexcept -> const T* {
				if constexpr(USES_SMALL_BUFFER){
					if(this->is_small()){
						return this->get_small_data();
					}else{
						return this->contents.big.data;
					}
				}else{
					return this->contents.big.data;
				}
			};


			//////////////////////////////////////////////////////////////////////
			// iterators

			EVO_NODISCARD constexpr auto begin()        noexcept -> iterator       { return iterator{this->data()};       };
			EVO_NODISCARD constexpr auto begin()  const noexcept -> const_iterator { return const_iterator{this->data()}; };
			EVO_NODISCARD constexpr auto cbegin() const noexcept -> const_iterator { return const_iterator{this->data()}; };

			EVO_NODISCARD constexpr auto end()        noexcept -> iterator       { return iterator{&this->data()[this->size()]};       };
			EVO_NODISCARD constexpr auto end()  const noexcept -> const_iterator { return const_iterator{&this->data()[this->size()]}; };
			EVO_NODISCARD constexpr auto cend() const noexcept -> const_iterator { return const_iterator{&this->data()[this->size()]}; };


			EVO_NODISCARD constexpr auto rbegin()        noexcept -> reverse_iterator       { return reverse_iterator{&this->data()[this->size()-1]};      };
			EVO_NODISCARD constexpr auto rbegin()  const noexcept -> const_reverse_iterator { return const_reverse_iterator{&this->data()[this->size()-1]};};
			EVO_NODISCARD constexpr auto crbegin() const noexcept -> const_reverse_iterator { return const_reverse_iterator{&this->data()[this->size()-1]};};

			EVO_NODISCARD constexpr auto rend()        noexcept -> reverse_iterator       { return reverse_iterator{this->data()-1};       };
			EVO_NODISCARD constexpr auto rend()  const noexcept -> const_reverse_iterator { return const_reverse_iterator{this->data()-1}; };
			EVO_NODISCARD constexpr auto crend() const noexcept -> const_reverse_iterator { return const_reverse_iterator{this->data()-1}; };



			//////////////////////////////////////////////////////////////////////
			// capacity

			EVO_NODISCARD constexpr auto empty() const noexcept -> bool {
				return this->size() == 0;
			};

			EVO_NODISCARD constexpr auto size() const noexcept -> size_t {
				if constexpr(USES_SMALL_BUFFER){
					if(this->is_small()){
						return this->get_small_size();
					}else{
						return this->contents.big.size;
					}
				}else{
					return this->contents.big.size;
				}
			};

			EVO_NODISCARD constexpr static auto max_size() noexcept -> size_t {
				return (std::numeric_limits<size_t>::max() >> 1) / sizeof(T);
			};

			EVO_NODISCARD constexpr auto capacity() const noexcept -> size_t {
				if constexpr(USES_SMALL_BUFFER){
					if(this->is_small()){
						return SMALL_CAPACITY;
					}else{
						return this->contents.big.capacity;
					}
				}else{
					return this->contents.big.capacity;
				}
			};


			EVO_NODISCARD constexpr static auto small_capacity() noexcept -> size_t {
				return SMALL_CAPACITY;
			};


			//////////////////////////////////////////////////////////////////////
			// modify

			///////////////////////////////////
			// clear

			constexpr auto clear() noexcept -> void {
				std::destroy_at(this);
				std::construct_at(this);
			};


			///////////////////////////////////
			// reserve

			constexpr auto reserve(size_t new_capacity) noexcept -> void {
				if constexpr(USES_SMALL_BUFFER){
					if(new_capacity > SMALL_CAPACITY){
						this->make_big(new_capacity);
					}

				}else{
					if(new_capacity > this->contents.big.capacity){
						this->realloc(new_capacity);
					}
				}
			};


			///////////////////////////////////
			// insert

			constexpr auto insert(const_iterator pos, const T& value) noexcept -> iterator {
				return this->emplace(pos, value);
			};


			constexpr auto insert(const_iterator pos, T&& value) noexcept -> iterator {
				return this->emplace(pos, std::move(value));
			};


			// not implemented yet: auto insert(const_iterator pos, size_type count, const T& value) noexcept -> iterator
			// not implemented yet: template<class InputIt> auto insert(const_iterator pos, InputIt first, InputIt last) noexcept -> iterator
			// not implemented yet: auto insert(const_iterator pos, std::initializer_list<T> ilist) noexcept -> void;


			// not implemented yet: insert_range


			///////////////////////////////////
			// emplace

			constexpr auto emplace(const_iterator pos, auto&&... args) noexcept -> iterator {
				EVO_DEBUG_ASSERT(pos.inBounds(this->begin(), this->end()));

				size_t index = (size_t(&*pos) - size_t(this->data())) / sizeof(T);

				if(this->is_small() && this->size() == SMALL_CAPACITY){
					this->make_big(SMALL_CAPACITY * 2);
				}
				this->emplace_back(std::forward<decltype(args)>(args)...);

				pos = const_iterator(this->data() + index);

				const auto begin = this->rbegin();
				const auto end = reverse_iterator{const_cast<T*>(&*pos)};


				for(reverse_iterator iter = begin; iter != end; ++iter){
					std::swap(*iter, *std::next(iter));
				}

				return iterator{const_cast<T*>(&*pos)};
			};


			///////////////////////////////////
			// erase

			constexpr auto erase(const_iterator pos) noexcept -> iterator {
				EVO_DEBUG_ASSERT(pos.inBounds(this->begin(), this->end()));

				std::destroy_at(&*pos);

				iterator output = [&](){
					if(pos == this->end()){
						return --this->end();
					}else{
						return iterator{const_cast<T*>(&*pos)};
					}
				}();


				for(auto iter = iterator{const_cast<T*>(&*pos)}; iter != --this->end(); ++iter){
					std::swap(*iter, *std::next(iter));
				}


				if constexpr(USES_SMALL_BUFFER){
					if(this->is_small()){
						this->set_small_size(static_cast<SmallSizeType>(this->get_small_size() - 1));
					}else{
						this->contents.big.size -= 1;
					}
				}else{
					this->contents.big.size -= 1;
				}

				return output;
			};

			// not implemented yet: auto erase(const_iterator first, const_iterator last) noexcept -> iterator


			///////////////////////////////////
			// push_back

			constexpr auto push_back(const T& value) noexcept -> void { this->emplace_back(value); };
			constexpr auto push_back(T&& value) noexcept -> void { this->emplace_back(std::move(value)); };


			///////////////////////////////////
			// emplace_back


			constexpr auto emplace_back(auto&&... args) noexcept -> T& {
				const auto emplace_back_big = [&](auto&&... args) -> T& {
					if(this->contents.big.size == this->contents.big.capacity){
						this->realloc(this->contents.big.capacity * 2);
					}

					T* new_elem_ptr = &this->contents.big.data[this->contents.big.size];
					std::construct_at(new_elem_ptr, std::forward<decltype(args)>(args)...);
					this->contents.big.size += 1;
					return *new_elem_ptr;
				};


				if constexpr(USES_SMALL_BUFFER){
					if(this->is_small()){
						const size_t current_size = this->get_small_size();
						if(current_size == SMALL_CAPACITY){
							this->make_big(SMALL_CAPACITY * 2);

							T* new_elem_ptr = &this->contents.big.data[this->contents.big.size];
							std::construct_at(new_elem_ptr, std::forward<decltype(args)>(args)...);
							this->contents.big.size += 1;
							return *new_elem_ptr;

						}else{
							T* new_elem_ptr = &this->get_small_data()[current_size];
							std::construct_at(new_elem_ptr, std::forward<decltype(args)>(args)...);
							this->set_small_size(static_cast<SmallSizeType>(current_size + 1));
							return *new_elem_ptr;
						}
					}else{
						return emplace_back_big(std::forward<decltype(args)>(args)...);
					}

				}else{
					if(this->contents.big.size != 0){
						return emplace_back_big(std::forward<decltype(args)>(args)...);

					}else{
						this->reserve(4);
						std::construct_at(this->contents.big.data, std::forward<decltype(args)>(args)...);
						this->contents.big.size += 1;
						return *this->contents.big.data;
					}
				}
			};


			// not implemented yet: append_range

			///////////////////////////////////
			// pop_back

			constexpr auto pop_back() noexcept -> void {
				EVO_DEBUG_ASSERT(this->empty() == false);

				if constexpr(USES_SMALL_BUFFER){
					if(this->is_small()){
						const size_t new_size = this->get_small_size() - 1;
						std::destroy_at(&this->get_small_data()[new_size]);
						this->set_small_size(static_cast<SmallSizeType>(new_size));

					}else{
						std::destroy_at(&this->contents.big.data[this->contents.big.size - 1]);
						this->contents.big.size -= 1;
					}

				}else{
					std::destroy_at(&this->contents.big.data[this->contents.big.size - 1]);
					this->contents.big.size -= 1;
				}
			};


			///////////////////////////////////
			// resize

			// TODO: optimize
			constexpr auto resize(size_t new_size) noexcept -> void {
				while(new_size < this->size()){
					this->pop_back();
				}

				if(new_size > this->size()){
					this->reserve(new_size);
					while(new_size > this->size()){
						this->emplace_back();
					}
				}
			};


			// not implemented yet: swap



			//////////////////////////////////////////////////////////////////////
			// operators

			EVO_NODISCARD constexpr auto operator==(const SmallVector& rhs) const noexcept -> bool {
				if(this->size() != rhs.size()){ return false; }

				for(size_t i = 0; i < this->size(); i+=1){
					if(this->at(i) != rhs.at(i)){ return false; }
				}

				return true;
			};



			EVO_NODISCARD constexpr operator std::span<T>() noexcept {
				return std::span<T>(this->data(), this->size());
			};



		private:
			constexpr auto realloc(size_t new_capacity) noexcept -> void {
				EVO_DEBUG_ASSERT(this->size() <= new_capacity);

				T* new_buffer = (T*)std::malloc(new_capacity * sizeof(T));
				for(size_t i = 0; i < this->contents.big.size; i+=1){
					std::construct_at(&new_buffer[i], std::move(this->contents.big.data[i]));
				}
				std::free(this->contents.big.data);
				this->contents.big.data = new_buffer;
				this->contents.big.capacity = new_capacity;
			};

			constexpr auto make_big(size_t new_capacity) noexcept -> void {
				EVO_DEBUG_ASSERT(this->size() <= new_capacity);

				const size_t current_size = this->get_small_size();

				T* new_buffer = (T*)std::malloc(new_capacity * sizeof(T));
				for(size_t i = 0; i < current_size; i+=1){
					std::construct_at(&new_buffer[i], std::move(this->get_small_data()[i]));
				}
				this->contents.big.size = current_size;
				this->contents.big.capacity = new_capacity;
				this->contents.big.data = new_buffer;
			};

	


		private:	
			using SmallSizeType = CapacityType<SMALL_CAPACITY << 1>::type;

			// This being this complex is needed if the type is not complete
 			static constexpr size_t SMALL_BUFFER_SIZE = [](){
				if constexpr(USES_SMALL_BUFFER){
					return SMALL_CAPACITY * sizeof(T);
				}else{
					return 0;
				}
			}();

			// data contains the size and buffer to get around C++ not having packed structs
			struct SmallData{
				byte data[SMALL_BUFFER_SIZE + sizeof(SmallSizeType)];
			};

			struct BigData{
				size_t size;
				size_t capacity;
				T* data;
			};


			// TODO: is having the set bit on small fastest? Maybe it's better on big because data is on the heap
			EVO_NODISCARD constexpr auto get_small_size() const noexcept -> size_t { return size_t(*(SmallSizeType*)this->contents.small.data & ((1 << 7) - 1)); };

			EVO_NODISCARD constexpr auto get_small_data() const noexcept -> const T* { return (T*)(this->contents.small.data + sizeof(SmallSizeType)); };
			EVO_NODISCARD constexpr auto get_small_data()       noexcept ->       T* { return (T*)(this->contents.small.data + sizeof(SmallSizeType)); };



			EVO_NODISCARD constexpr auto set_small_size(SmallSizeType new_size) noexcept -> void {
				*(SmallSizeType*)this->contents.small.data = new_size;
				*(byte*)&this->contents |= 1 << 7;
			};



			EVO_NODISCARD constexpr auto is_small() const noexcept -> bool { return bool((*(byte*)&this->contents) >> 7); };
			EVO_NODISCARD constexpr auto is_big() const noexcept -> bool { return !this->is_small(); };



			union{
				SmallData small;
				BigData big;
			} contents;
	};


	static_assert(sizeof(SmallVector<int>) == sizeof(size_t) * 3, "evo::SmallVector is not the expected size");

};



namespace std{

	template<typename T, size_t SMALL_CAPACITY>
	struct hash<evo::SmallVector<T, SMALL_CAPACITY>>{
		auto operator()(const evo::SmallVector<T, SMALL_CAPACITY>& small_vec) const noexcept -> size_t {
			size_t hash_value = 0;
			for(const T& value : small_vec){
				hash_value = evo::hashCombine(hash_value, hash<T>{}(value));
			}
			return hash_value;
		};
	};
	
}



