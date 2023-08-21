#pragma once

#include <array>

namespace evo{
	
	// reference: https://en.cppreference.com/w/cpp/container/vector
	// 			  https://en.cppreference.com/w/cpp/container/array
	// I attempted to make this somewhat like a what std implementation might be


	template<typename T, size_t CAPACITY>
	class StaticVector{
		public:
			using value_type = T;
			using size_type = CapacityType<CAPACITY>::type;
			using difference_type = std::ptrdiff_t; // not 100% sure this is correct
			using reference = T&;
			using const_reference = const T&;
			using pointer = T*;
			using const_pointer = const T*;
			using iterator = std::array<T, CAPACITY>::iterator;
			using const_iterator = std::array<T, CAPACITY>::const_iterator;
			using reverse_iterator = std::array<T, CAPACITY>::reverse_iterator;
			using const_reverse_iterator = std::array<T, CAPACITY>::const_reverse_iterator;


			//////////////////////////////////////////////////////////////////////
			// constructors / destructors

			EVO_NODISCARD constexpr StaticVector() noexcept = default;

			// EVO_NODISCARD constexpr StaticVector(std::array<T, CAPACITY>        in_arr) noexcept : data_block(std::move( in_arr) ) {};
			EVO_NODISCARD constexpr StaticVector(const std::array<T, CAPACITY>& in_arr) noexcept : data_block(in_arr)			    {};
			EVO_NODISCARD constexpr StaticVector(std::array<T, CAPACITY>&&      in_arr) noexcept : data_block(std::move( in_arr) ) {};
			EVO_NODISCARD constexpr StaticVector(std::initializer_list<T>    init_list) noexcept : data_block(init_list)		    {};

			// EVO_NODISCARD constexpr ~StaticVector() noexcept = default;

			EVO_NODISCARD constexpr auto operator =(const std::array<T, CAPACITY>& in_arr) noexcept -> void { this->data_block = in_arr;            };
			EVO_NODISCARD constexpr auto operator =(std::array<T, CAPACITY>&&      in_arr) noexcept -> void { this->data_block = std::move(in_arr); };
			EVO_NODISCARD constexpr auto operator =(std::initializer_list<T>    init_list) noexcept -> void { this->data_block = init_list;         };

			EVO_NODISCARD constexpr auto operator =(const StaticVector<T, CAPACITY>& in_arr) noexcept -> void {
				this->data_block = in_arr.data_block;
				this->_size = in_arr._size;
			};
			// EVO_NODISCARD constexpr auto operator =(StaticVector<T, CAPACITY>&&      in_arr) noexcept -> void {
			// 	this->data_block = std::move(in_arr.data_block);
			// 	this->_size = in_arr._size;
			// };


			EVO_NODISCARD constexpr operator std::span<T, CAPACITY>() noexcept {
				return this->data;
			};


			//////////////////////////////////////////////////////////////////////
			// element access

			///////////////////////////////////
			// at

			EVO_NODISCARD constexpr auto at(size_type index) noexcept -> T& {
				EVO_DEBUG_ASSERT(index < this->_size);

				return this->data_block[index];
			};

			EVO_NODISCARD constexpr auto at(size_type index) const noexcept -> const T& {
				EVO_DEBUG_ASSERT(index < this->_size);

				return this->data_block[index];
			};



			///////////////////////////////////
			// operator[]

			EVO_NODISCARD constexpr auto operator[](size_type index) noexcept -> T& {
				return this->at(index);
			};

			EVO_NODISCARD constexpr auto operator[](size_type index) const noexcept -> const T& {
				return this->at(index);
			};



			///////////////////////////////////
			// front

			EVO_NODISCARD constexpr auto front() noexcept -> T& {
				return this->data_block.front();
			};

			EVO_NODISCARD constexpr auto front() const noexcept -> const T& {
				return this->data_block.front();
			};



			///////////////////////////////////
			// back

			EVO_NODISCARD constexpr auto back() noexcept -> T& {
				return this->data_block.back();
			};

			EVO_NODISCARD constexpr auto back() const noexcept -> const T& {
				return this->data_block.back();
			};



			///////////////////////////////////
			// data
			EVO_NODISCARD constexpr auto data() noexcept -> T* { return this->data_block.data(); };

			EVO_NODISCARD constexpr auto data() const noexcept -> const T* { return this->data_block.data(); };



			//////////////////////////////////////////////////////////////////////
			// iterators


			EVO_NODISCARD constexpr auto begin()        noexcept -> iterator       { return iterator{this->data(), 0};       };
			EVO_NODISCARD constexpr auto begin()  const noexcept -> const_iterator { return const_iterator{this->data(), 0}; };
			EVO_NODISCARD constexpr auto cbegin() const noexcept -> const_iterator { return const_iterator{this->data(), 0}; };

			EVO_NODISCARD constexpr auto end()        noexcept -> iterator       { return iterator{this->data(), this->_size};       };
			EVO_NODISCARD constexpr auto end()  const noexcept -> const_iterator { return const_iterator{this->data(), this->_size}; };
			EVO_NODISCARD constexpr auto cend() const noexcept -> const_iterator { return const_iterator{this->data(), this->_size}; };


			EVO_NODISCARD constexpr auto rbegin()        noexcept -> reverse_iterator       { return reverse_iterator{this->data(), this->_size};       };
			EVO_NODISCARD constexpr auto rbegin()  const noexcept -> const_reverse_iterator { return const_reverse_iterator{this->data(), this->_size}; };
			EVO_NODISCARD constexpr auto crbegin() const noexcept -> const_reverse_iterator { return const_reverse_iterator{this->data(), this->_size}; };

			EVO_NODISCARD constexpr auto rend()        noexcept -> reverse_iterator       { return reverse_iterator{this->data(), 0};       };
			EVO_NODISCARD constexpr auto rend()  const noexcept -> const_reverse_iterator { return const_reverse_iterator{this->data(), 0}; };
			EVO_NODISCARD constexpr auto crend() const noexcept -> const_reverse_iterator { return const_reverse_iterator{this->data(), 0}; };



			//////////////////////////////////////////////////////////////////////
			// capacity

			EVO_NODISCARD constexpr auto empty() const noexcept -> bool { return this->_size == 0; };

			EVO_NODISCARD constexpr auto size() const noexcept -> size_t { return size_t(this->_size); };

			EVO_NODISCARD constexpr auto max_size() const noexcept -> size_t { return size_t(this->_size); };

			EVO_NODISCARD constexpr auto capacity() const noexcept -> size_t { return size_t(CAPACITY); };



			//////////////////////////////////////////////////////////////////////
			// modify

			constexpr auto clear() noexcept -> void { this->_size = 0; };


			// not implemented yet: insert
			// not implemented yet: insert_range
			// not implemented yet: emplace
			// not implemented yet: erase


			///////////////////////////////////
			// push_back

			constexpr auto push_back(const T& value) noexcept -> void {
				EVO_DEBUG_ASSERT(this->_size < CAPACITY);

				this->data_block[this->_size] = value;
				this->_size += 1;
			};

			constexpr auto push_back(T&& value) noexcept -> void {
				EVO_DEBUG_ASSERT(this->_size < CAPACITY);

				this->data_block[this->_size] = std::move(value);
				this->_size += 1;
			};

			template<class... Args>
			constexpr auto emplace_back(Args&&... args) noexcept -> T& {
				EVO_DEBUG_ASSERT(this->_size < CAPACITY);

				T* new_object = &this->data_block[this->_size];
				// new_object = new(new_object) T(std::forward<Args>(args)...);
				std::construct_at(new_object, std::forward<Args>(args)...);
				this->_size += 1;
				return *new_object;
			};

			// not implemented yet: append
			// not implemented yet: append_range

			constexpr auto pop_back() noexcept -> T& {
				EVO_DEBUG_ASSERT(this->_size > 0);

				this->_size -= 1;
				return std::move(this->data_block[this->_size]);
			};

			constexpr auto resize(size_type new_size) noexcept -> void {
				EVO_DEBUG_ASSERT(new_size < CAPACITY);

				if(this->_size > new_size){
					for(ui32 i = new_size; i < this->_size; i++){
						// this->data_block.~T();
						std::destroy_at(*this->data_block[i]);
					}
				}else{
					for(ui32 i = new_size; i < this->_size; i++){
						std::construct_at(*this->data_block[i]);
					}
				}

				this->_size = new_size;
			};

			// not implemented yet: swap

	
		private:
			std::array<T, CAPACITY> data_block{};
			size_type _size = 0;
			
	};

};


