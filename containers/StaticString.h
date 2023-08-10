#pragma once



namespace evo{
	
	template<size_t CAPACITY>
	class StaticString{
		public:
			using value_type = char;
			using size_type = CapacityType<CAPACITY>::type;
			using difference_type = std::ptrdiff_t; // not 100% sure this is correct
			using reference = char&;
			using const_reference = const char&;
			using pointer = char*;
			using const_pointer = const char*;
			using iterator = std::array<char, CAPACITY>::iterator;
			using const_iterator = std::array<char, CAPACITY>::const_iterator;
			using reverse_iterator = std::array<char, CAPACITY>::reverse_iterator;
			using const_reverse_iterator = std::array<char, CAPACITY>::const_reverse_iterator;


			//////////////////////////////////////////////////////////////////////
			// constructors / destructors

			constexpr StaticString() noexcept = default;

			constexpr StaticString(const char* chars) noexcept { this->operator=(chars); };

			constexpr StaticString(const std::string& str) noexcept { this->operator=(str); };
			constexpr StaticString(std::string&& str) noexcept { this->operator=(str); };

			template<size_t StrSize>
			constexpr StaticString(const StaticString<StrSize>& str) noexcept { this->operator=(str); };

			// constexpr ~StaticString() noexcept = default;


			constexpr auto operator =(const char* chars) noexcept -> void {
				for(size_type i = 0; i < CAPACITY; i+=1){
					this->data_block[i] = chars[i];
					
					if(chars[i] == '\0'){
						this->resize(i);
						return;
					}
				}

				this->resize(CAPACITY);
			};

			constexpr auto operator =(const std::string& str) noexcept -> void {
				EVO_DEBUG_ASSERT(str.size() <= this->capacity()); // const std::string& parameter passed in is larger than the static string capacity

				::memcpy(this->data(), str.data(), str.size());
				this->resize(static_cast<size_type>(str.size()));
			};

			constexpr auto operator =(std::string&& str) noexcept -> void {
				EVO_DEBUG_ASSERT(str.size() <= this->capacity()); // std::string&& parameter passed in is larger than the static string capacity

				::memcpy(this->data(), str.data(), str.size());
				this->resize(static_cast<size_type>(str.size()));
			};


			template<size_t StrSize>
			constexpr auto operator =(const StaticString<StrSize>& str) noexcept -> void {
				EVO_DEBUG_ASSERT(str.size() <= this->capacity()); // attempted to copy static string larger than capacity

				this->data_block = str.data_block;
				this->_remaining_capacity = str._remaining_capacity;
			};



			//////////////////////////////////////////////////////////////////////
			// element access

			///////////////////////////////////
			// at

			EVO_NODISCARD constexpr auto at(size_type index) noexcept -> char& {
				EVO_DEBUG_ASSERT(index < this->size()); // index is outsize bounds of string data
				return this->data_block[index];
			};

			EVO_NODISCARD constexpr auto at(size_type index) const noexcept -> const char& {
				EVO_DEBUG_ASSERT(index < this->size()); // index is outsize bounds of string data
				return this->data_block[index];
			};


			///////////////////////////////////
			// operator[]

			EVO_NODISCARD constexpr auto operator[](size_type index) noexcept -> char& {
				return this->at(index);
			};

			EVO_NODISCARD constexpr auto operator[](size_type index) const noexcept -> const char& {
				return this->at(index);
			};



			///////////////////////////////////
			// front

			EVO_NODISCARD constexpr auto front() noexcept -> char& {
				return this->data_block.front();
			};

			EVO_NODISCARD constexpr auto front() const noexcept -> const char& {
				return this->data_block.front();
			};



			///////////////////////////////////
			// back

			EVO_NODISCARD constexpr auto back() noexcept -> char& {
				return this->data_block.back();
			};

			EVO_NODISCARD constexpr auto back() const noexcept -> const char& {
				return this->data_block.back();
			};



			///////////////////////////////////
			// data
			EVO_NODISCARD constexpr auto data() noexcept -> char* { return this->data_block.data(); };

			EVO_NODISCARD constexpr auto data() const noexcept -> const char* { return this->data_block.data(); };




			///////////////////////////////////
			// c_str

			EVO_NODISCARD constexpr auto c_str() const noexcept -> const char* {
				if(this->_remaining_capacity != 0){
					const_cast<char&>(this->data_block[CAPACITY - this->_remaining_capacity]) = '\0';
				}

				return this->data();
			};



			//////////////////////////////////////////////////////////////////////
			// Iterators


			EVO_NODISCARD constexpr auto begin()        noexcept -> iterator       { return iterator{this->data(), 0};       };
			EVO_NODISCARD constexpr auto begin()  const noexcept -> const_iterator { return const_iterator{this->data(), 0}; };
			EVO_NODISCARD constexpr auto cbegin() const noexcept -> const_iterator { return const_iterator{this->data(), 0}; };

			EVO_NODISCARD constexpr auto end()        noexcept -> iterator       { return iterator{this->data(), this->size()};       };
			EVO_NODISCARD constexpr auto end()  const noexcept -> const_iterator { return const_iterator{this->data(), this->size()}; };
			EVO_NODISCARD constexpr auto cend() const noexcept -> const_iterator { return const_iterator{this->data(), this->size()}; };


			EVO_NODISCARD constexpr auto rbegin()        noexcept -> reverse_iterator       { return reverse_iterator{this->data(), this->size()};       };
			EVO_NODISCARD constexpr auto rbegin()  const noexcept -> const_reverse_iterator { return const_reverse_iterator{this->data(), this->size()}; };
			EVO_NODISCARD constexpr auto crbegin() const noexcept -> const_reverse_iterator { return const_reverse_iterator{this->data(), this->size()}; };

			EVO_NODISCARD constexpr auto rend()        noexcept -> reverse_iterator       { return reverse_iterator{this->data(), 0};       };
			EVO_NODISCARD constexpr auto rend()  const noexcept -> const_reverse_iterator { return const_reverse_iterator{this->data(), 0}; };
			EVO_NODISCARD constexpr auto crend() const noexcept -> const_reverse_iterator { return const_reverse_iterator{this->data(), 0}; };



			//////////////////////////////////////////////////////////////////////
			// Capacity

			EVO_NODISCARD constexpr auto empty() const noexcept -> bool {
				return this->_remaining_capacity == CAPACITY;
			};


			EVO_NODISCARD constexpr auto size() const noexcept -> size_t {
				return static_cast<size_t>(CAPACITY - this->_remaining_capacity);
			};


			EVO_NODISCARD constexpr auto max_size() const noexcept -> size_t {
				return static_cast<size_t>(CAPACITY);
			};


			EVO_NODISCARD constexpr auto capacity() const noexcept -> size_t {
				return static_cast<size_t>(CAPACITY);
			};	



			constexpr auto clear() noexcept -> void { this->_remaining_capacity = CAPACITY; };

			// not implemented yet: insert
			// not implemented yet: insert_range
			// not implemented yet: erase

			constexpr auto push_back(char value) noexcept -> void {
				EVO_DEBUG_ASSERT(this->_remaining_capacity > 0); // string is already at full capacity

				this->data_block[this->size()] = value;
				this->_remaining_capacity -= 1;
			};

			constexpr auto pop_back(char value) noexcept -> void {
				EVO_DEBUG_ASSERT(this->_remaining_capacity < CAPACITY); // string is already empty

				this->_remaining_capacity += 1;
			};


	

			///////////////////////////////////
			// append / operator +=

			// not implemented yet: append_range

			constexpr auto append(const char* chars) const -> void {
				auto chars_length = strnlen_s(chars, this->_remaining_capacity + 1);
				EVO_DEBUG_ASSERT(chars_length <= this->_remaining_capacity); // Attempted to add string that is longer than current capacity

				::memcpy(this->data_block[this->size()], chars, chars_length);
				this->_remaining_capacity += chars_length;
			};

			constexpr auto append(const std::string& str) const -> void {
				EVO_DEBUG_ASSERT(str.size() <= this->_remaining_capacity); // Attempted to add string that is longer than current capacity

				::memcpy(this->data_block[this->size()], str.data(), str.size());
				this->_remaining_capacity += str.size();
			};

			template<size_t StrSize>
			constexpr auto append(const StaticString<StrSize>& str) const -> void {
				EVO_DEBUG_ASSERT(str.size() <= this->_remaining_capacity); // Attempted to add string that is longer than current capacity

				::memcpy(this->data_block[this->size()], str.data(), str.size());
				this->_remaining_capacity += str.size();
			};




			constexpr auto operator +=(const char* chars) const -> void {
				this->append(chars);
			};

			constexpr auto operator +=(const std::string& str) const -> void {
				this->append(str);
			};

			template<size_t StrSize>
			constexpr auto operator +=(const StaticString<StrSize>& str) const -> void {
				this->append(str);
			};


			//////////////////////////////////////////////////////////////////////
			// operator ==

			EVO_NODISCARD constexpr auto operator ==(const char* chars) const -> bool {
				for(size_t i = 0; i < this->size(); i+=1){
					if(chars[i] == '\0'){
						return false;
					}
				}

				return chars[this->size()] == '\0';
			};



			EVO_NODISCARD constexpr auto operator ==(const std::string& str) const noexcept -> bool {
				return this->operator==(std::string_view{str.data(), str.size()});
			};


			template<size_t StrSize>
			EVO_NODISCARD constexpr auto operator ==(const StaticString<StrSize>& str) const noexcept -> bool {
				return this->operator==(std::string_view{str.data(), str.size()});
			};


			 



			// not implemented yet: compare
			// not implemented yet: starts_with
			// not implemented yet: ends_with
			// not implemented yet: contains
			// not implemented yet: replace
			// not implemented yet: replace_with_range
			// not implemented yet: substr
			// not implemented yet: copy

			constexpr auto resize(size_type new_size) noexcept -> void {
				EVO_DEBUG_ASSERT(new_size <= CAPACITY); // New string size is larger than the capacity
				this->_remaining_capacity = CAPACITY - new_size;
			};

			template<typename std::enable_if<std::is_same_v<size_t, size_type>> = false>
			constexpr auto resize(size_t new_size) noexcept -> void {				
				this->resize(static_cast<size_type>(new_size));
			};


			constexpr auto resize_to_c_str() noexcept -> void {
				auto chars_length = strnlen_s(this->data(), CAPACITY);
				this->resize(chars_length);
			};



			// not implemented yet: swap



			//////////////////////////////////////////////////////////////////////
			// Operations


			//////////////////////////////////////////////////////////////////////
			// search

		private:
			 EVO_NODISCARD constexpr auto operator ==(const std::string_view str) const noexcept -> bool {
				return str == std::string_view{this->data(), this->size()};
			};
	
		private:
			std::array<char, CAPACITY> data_block{};
			size_type _remaining_capacity = CAPACITY;

			// NOTE: I use remaining capacity instead of size because when the data block is full, the 0 remaining capacity being right after the
			//       data block doubles as a null terminator
	};


};

