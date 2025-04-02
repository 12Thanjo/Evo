#pragma once

#include <iterator>

namespace evo{


	template<typename T, bool ALLOW_SMALL_BUFFER_OPT = true>
	class UnmovableVector{
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


			//////////////////////////////////////////////////////////////////////
			// constructors / destructors


			EVO_NODISCARD UnmovableVector() noexcept {
				std::memset(this, 0, sizeof(UnmovableVector<T>));
			};
			EVO_NODISCARD UnmovableVector(size_t reserve_ammount) noexcept {
				std::memset(this, 0, sizeof(UnmovableVector<T>));
				this->reserve(reserve_ammount);
			};
			~UnmovableVector() noexcept {
				if(this->empty() == false){
					this->clear();
				}
			};

			UnmovableVector(const UnmovableVector&) = delete;
			UnmovableVector(UnmovableVector&&) = delete;


			//////////////////////////////////////////////////////////////////////
			// element access

			///////////////////////////////////
			// at

			EVO_NODISCARD auto at(size_t index) noexcept -> T& {
				EVO_DEBUG_ASSERT(index < this->size());

				return this->data()[index];
			};

			EVO_NODISCARD auto at(size_t index) const noexcept -> const T& {
				EVO_DEBUG_ASSERT(index < this->size());

				return this->data()[index];
			};


			///////////////////////////////////
			// operator[]

			EVO_NODISCARD auto operator[](size_t index)       noexcept ->       T& { return this->at(index); };
			EVO_NODISCARD auto operator[](size_t index) const noexcept -> const T& { return this->at(index); };


			///////////////////////////////////
			// front

			EVO_NODISCARD auto front() noexcept -> T& {
				return *this->data();
			};

			EVO_NODISCARD auto front() const noexcept -> const T& {
				return *this->data();
			};


			///////////////////////////////////
			// front

			EVO_NODISCARD auto back() noexcept -> T& {
				return this->data()[this->size() - 1];
			};

			EVO_NODISCARD auto back() const noexcept -> const T& {
				return this->data()[this->size() - 1];
			};


			///////////////////////////////////
			// data

			EVO_NODISCARD auto data() noexcept -> T* {
				if constexpr(ALLOW_SMALL_BUFFER_OPT){
					if(this->is_small()){
						return (T*)this->_data.small.data;
					}else{
						return this->_data.big.data;	
					}
				}else{
					return this->_data.big.data;
				}
			};

			EVO_NODISCARD auto data() const noexcept -> const T* {
				if constexpr(ALLOW_SMALL_BUFFER_OPT){
					if(this->is_small()){
						return (T*)this->_data.small.data;
					}else{
						return this->_data.big.data;	
					}
				}else{
					return this->_data.big.data;
				}
			};


			//////////////////////////////////////////////////////////////////////
			// iterators

			EVO_NODISCARD auto begin()        noexcept -> iterator       { return iterator{this->data()};       };
			EVO_NODISCARD auto begin()  const noexcept -> const_iterator { return const_iterator{this->data()}; };
			EVO_NODISCARD auto cbegin() const noexcept -> const_iterator { return const_iterator{this->data()}; };

			EVO_NODISCARD auto end()        noexcept -> iterator       { return iterator{&this->data()[this->size()]};       };
			EVO_NODISCARD auto end()  const noexcept -> const_iterator { return const_iterator{&this->data()[this->size()]}; };
			EVO_NODISCARD auto cend() const noexcept -> const_iterator { return const_iterator{&this->data()[this->size()]}; };


			EVO_NODISCARD auto rbegin()        noexcept -> reverse_iterator       { return reverse_iterator{&this->data()[this->size()-1]};       };
			EVO_NODISCARD auto rbegin()  const noexcept -> const_reverse_iterator { return const_reverse_iterator{&this->data()[this->size()-1]}; };
			EVO_NODISCARD auto crbegin() const noexcept -> const_reverse_iterator { return const_reverse_iterator{&this->data()[this->size()-1]}; };

			EVO_NODISCARD auto rend()        noexcept -> reverse_iterator       { return reverse_iterator{this->data()-1};       };
			EVO_NODISCARD auto rend()  const noexcept -> const_reverse_iterator { return const_reverse_iterator{this->data()-1}; };
			EVO_NODISCARD auto crend() const noexcept -> const_reverse_iterator { return const_reverse_iterator{this->data()-1}; };



			//////////////////////////////////////////////////////////////////////
			// capacity

			EVO_NODISCARD auto empty() const noexcept -> bool { return this->size() == 0; };

			EVO_NODISCARD auto size() const noexcept -> size_t {
				if constexpr(ALLOW_SMALL_BUFFER_OPT){
					if(this->is_small()){
						return this->_data.small.size;
					}else{
						return this->_data.big.size;
					}
				}else{
					return this->_data.big.size;
				}
			};

			EVO_NODISCARD static auto max_size() noexcept -> size_t { return std::numeric_limits<difference_type>::max() >> 1; };

			EVO_NODISCARD auto capacity() const noexcept -> size_t {
				if constexpr(ALLOW_SMALL_BUFFER_OPT){
					if(this->is_small()){
						return this->_data.small.capacity & ((1 << 7) - 1);
					}else{
						return this->_data.big.capacity;
					}
				}else{
					return this->_data.big.capacity;
				}
			};


			//////////////////////////////////////////////////////////////////////
			// modify

			///////////////////////////////////
			// reserve

			auto reserve(size_t reserve_ammount) noexcept -> void {
				EVO_DEBUG_ASSERT(reserve_ammount != 0);
				EVO_DEBUG_ASSERT(this->capacity() == 0);

				if constexpr(ALLOW_SMALL_BUFFER_OPT){
					if(UnmovableVector<T>::may_use_small(reserve_ammount)){
						this->_data.small.capacity = uint8_t(reserve_ammount | 1 << 7);
						
					}else{
						this->_data.big.data = (T*)std::malloc(reserve_ammount * sizeof(T));
						this->_data.big.capacity = reserve_ammount;	
					}

				}else{
					this->_data.big.data = (T*)std::malloc(reserve_ammount * sizeof(T));
					this->_data.big.capacity = reserve_ammount;
				}
			};


			///////////////////////////////////
			// resize

			auto resize(size_t reserve_ammount) noexcept -> void {
				static_assert(std::is_default_constructible<T>(), "T must be default constructible");

				this->reserve(reserve_ammount);
				this->set_size(reserve_ammount);

				if constexpr(std::is_trivially_default_constructible<T>() == false){
					for(T& elem : *this){
						std::construct_at(&elem);
					}
				}
			};


			///////////////////////////////////
			// clear

			auto clear() noexcept -> void {
				EVO_DEBUG_ASSERT(this->capacity() != 0);

				std::destroy_n(this->data(), this->size());

				if constexpr(ALLOW_SMALL_BUFFER_OPT){
					if(this->is_small() == false){ std::free(this->_data.big.data); }
				}else{
					std::free(this->_data.big.data);
				}

				std::memset(this, 0, sizeof(UnmovableVector));
			};


			///////////////////////////////////
			// insert

			auto insert(const_iterator pos, const T& value) noexcept -> iterator {
				EVO_DEBUG_ASSERT(this->size() < this->capacity());
				EVO_DEBUG_ASSERT(pos.inBounds(this->begin(), this->end()));

				*this->end() = value;

				this->set_size(this->size() + 1);

				const auto begin = this->rbegin();
				const auto end = reverse_iterator{const_cast<T*>(&*pos)};


				for(reverse_iterator i = begin; i != end; ++i){
					std::swap(*i, *std::next(i));
				}

				return iterator{const_cast<T*>(&*pos)};
			};


			auto insert(const_iterator pos, T&& value) noexcept -> iterator {
				EVO_DEBUG_ASSERT(this->size() < this->capacity());
				EVO_DEBUG_ASSERT(pos.inBounds(this->begin(), this->end()));

				*this->end() = std::move(value);

				this->set_size(this->size() + 1);

				const auto begin = this->rbegin();
				const auto end = reverse_iterator{const_cast<T*>(&*pos)};


				for(reverse_iterator i = begin; i != end; ++i){
					std::swap(*i, *std::next(i));
				}

				return iterator{const_cast<T*>(&*pos)};
			};


			// not implemented yet: auto insert(const_iterator pos, size_type count, const T& value) noexcept -> iterator
			// not implemented yet: template<class InputIt> auto insert(const_iterator pos, InputIt first, InputIt last) noexcept -> iterator
			// not implemented yet: auto insert(const_iterator pos, std::initializer_list<T> ilist) noexcept -> void;


			// not implemented yet: insert_range


			///////////////////////////////////
			// emplace

			template<class... Args>
			auto emplace(const_iterator pos, Args&&... args) noexcept -> iterator {
				EVO_DEBUG_ASSERT(this->size() < this->capacity());
				EVO_DEBUG_ASSERT(pos.inBounds(this->begin(), this->end()));

				std::construct_at(&*this->end(), std::forward<Args>(args)...);

				this->set_size(this->size() + 1);

				const auto begin = this->rbegin();
				const auto end = reverse_iterator{const_cast<T*>(&*pos)};


				for(reverse_iterator i = begin; i != end; ++i){
					std::swap(*i, *std::next(i));
				}

				return iterator{const_cast<T*>(&*pos)};
			};


			///////////////////////////////////
			// erase

			auto erase(const_iterator pos) noexcept -> iterator {
				EVO_DEBUG_ASSERT(pos.inBounds(this->begin(), this->end()));
				
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

				this->pop_back();

				return output;
			};

			// not implemented yet: auto erase(const_iterator first, const_iterator last) noexcept -> iterator


			///////////////////////////////////
			// push_back

			auto push_back(const T& value) noexcept -> void {
				EVO_DEBUG_ASSERT(this->size() < this->capacity());

				this->data()[this->size()] = value;
				this->set_size(this->size() + 1);
			};

			auto push_back(T&& value) noexcept -> void {
				EVO_DEBUG_ASSERT(this->size() < this->capacity());

				this->data()[this->size()] = std::move(value);
				this->set_size(this->size() + 1);
			};


			///////////////////////////////////
			// emplace_back

			template<class... Args>
			auto emplace_back(Args&&... args) noexcept -> T& {
				EVO_DEBUG_ASSERT(this->size() < this->capacity());

				T& new_object = this->data()[this->size()];
				std::construct_at(&new_object, std::forward<Args>(args)...);

				this->set_size(this->size() + 1);
				return new_object;
			};


			// not implemented yet: append_range

			///////////////////////////////////
			// pop_back

			auto pop_back() noexcept -> void {
				EVO_DEBUG_ASSERT(this->size() > 0);

				this->set_size(this->size() - 1);
				std::destroy_at(&this->back());
			};



			//////////////////////////////////////////////////////////////////////
			// operators

			EVO_NODISCARD auto operator==(const UnmovableVector& rhs) const noexcept -> bool {
				if(this->size() != rhs.size()){ return false; }

				for(size_t i = 0; const T& rhs_elem : rhs){
					if(rhs_elem != this->at(i)){ return false; }
				
					i += 1;
				}

				return true;
			}

			EVO_NODISCARD auto operator!=(const UnmovableVector& rhs) const noexcept -> bool {
				if(this->size() != rhs.size()){ return true; }

				for(size_t i = 0; const T& rhs_elem : rhs){
					if(rhs_elem != this->at(i)){ return true; }
				
					i += 1;
				}

				return false;
			}




			EVO_NODISCARD constexpr operator std::span<T>() noexcept {
				return std::span<T>(this->data(), this->size());
			};


		private:
			EVO_NODISCARD auto is_small() const -> bool {
				static_assert(ALLOW_SMALL_BUFFER_OPT, "This function should not be called if not allowed to do small-buffer optimization");

				return bool(this->_data.small.capacity >> 7);
			}

			EVO_NODISCARD static auto may_use_small(size_t capacity) -> bool {
				static_assert(ALLOW_SMALL_BUFFER_OPT, "This function should not be called if not allowed to do small-buffer optimization");

				const size_t required_buffer_size = sizeof(T) * capacity;
				static constexpr size_t BITS_REQUIRED_TO_HOLD_METADATA = 16;
				return sizeof(UnmovableVector<T>) - BITS_REQUIRED_TO_HOLD_METADATA <= required_buffer_size;
			}



			auto set_size(size_t new_size) -> void {
				EVO_DEBUG_ASSERT(new_size <= std::numeric_limits<uint8_t>::max());

				if constexpr(ALLOW_SMALL_BUFFER_OPT){
					if(this->is_small()){
						this->_data.small.size = uint8_t(new_size);
					}else{
						this->_data.big.size = new_size;
					}
				}else{
					this->_data.big.size = new_size;
				}
			}

	
		private:
			union{
				struct /* small */ {
					uint8_t capacity;
					uint8_t size;
					evo::byte data[sizeof(size_t)*2 + sizeof(T*) - sizeof(uint8_t)*2];
				} small;

				struct /* big */ {
					size_t capacity;
					size_t size;
					T* data;
				} big;
			} _data;
	};

	static_assert(sizeof(UnmovableVector<int>) == sizeof(size_t)*3, "evo::UnmovableVector is incorrect size");

};





namespace std{

	template<typename T, bool ALLOW_SMALL_BUFFER_OPT>
	struct hash<evo::UnmovableVector<T, ALLOW_SMALL_BUFFER_OPT>>{
		auto operator()(const evo::UnmovableVector<T, ALLOW_SMALL_BUFFER_OPT>& unmovable_vec) const noexcept -> size_t {
			size_t hash_value = 0;
			for(const T& value : unmovable_vec){
				hash_value = evo::hashCombine(hash_value, hash<T>{}(value));
			}
			return hash_value;
		};
	};
	
}


