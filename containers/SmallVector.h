#pragma once


#include <variant>

namespace evo{

	template<typename T>
	constexpr auto optimal_small_vector_size() noexcept -> size_t {
		return std::max<size_t>(sizeof(std::vector<T>) / sizeof(T), 1);
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



			//////////////////////////////////////////////////////////////////////
			// constructors / destructors

			EVO_NODISCARD SmallVector() noexcept {};


			~SmallVector() noexcept = default;


			///////////////////////////////////
			// copy

			EVO_NODISCARD SmallVector(const SmallVector<T, SMALL_CAPACITY>& rhs) noexcept {
				this->data_block = rhs.data_block;
			};


			auto operator=(const SmallVector<T, SMALL_CAPACITY>& rhs) noexcept -> SmallVector<T, SMALL_CAPACITY>& {
				this->data_block = rhs.data_block;

				return *this;
			};


			///////////////////////////////////
			// move

			EVO_NODISCARD SmallVector(SmallVector<T, SMALL_CAPACITY>&& rhs) noexcept {
				this->data_block = std::move(rhs.data_block);
			};


			auto operator=(SmallVector<T, SMALL_CAPACITY>&& rhs) noexcept -> SmallVector<T, SMALL_CAPACITY>& {
				this->data_block = std::move(rhs.data_block);

				return *this;
			};


			///////////////////////////////////
			// deleted special member functions

			SmallVector(const SmallVector<T, SMALL_CAPACITY>&&) = delete;
			SmallVector<T, SMALL_CAPACITY>& operator=(const SmallVector<T, SMALL_CAPACITY>&&) = delete;


			///////////////////////////////////
			// construct from initializer list

			EVO_NODISCARD SmallVector(std::initializer_list<T> init_list) noexcept {
				this->clear();

				if(init_list.size() <= SMALL_CAPACITY){
					this->emplace_data<StaticVector<T, SMALL_CAPACITY>>(init_list);
				}else{
					this->emplace_data<std::vector<T>>(init_list);
				}
			};

			auto operator=(std::initializer_list<T> init_list) noexcept -> SmallVector<T, SMALL_CAPACITY>& {
				this->clear();

				if(init_list.size() <= SMALL_CAPACITY){
					this->emplace_data<StaticVector<T, SMALL_CAPACITY>>(init_list);
				}else{
					this->emplace_data<std::vector<T>>(init_list);
				}

				return *this;
			};


			///////////////////////////////////
			// construct from iterators

			template<class InputIt>
			EVO_NODISCARD constexpr SmallVector(InputIt first, InputIt last) noexcept {
				this->reserve(std::distance(first, last));
				for(auto i = first; i != last; ++i){
					this->emplace_back(*i);
				}
			};





			//////////////////////////////////////////////////////////////////////
			// element access

			///////////////////////////////////
			// at

			EVO_NODISCARD auto at(size_t index) noexcept -> T& {
				EVO_DEBUG_ASSERT(index < this->size());

				if(this->is_small()){
					return this->get_small()[index];
				}else{
					return this->get_big()[index];
				}
			};

			EVO_NODISCARD auto at(size_t index) const noexcept -> const T& {
				EVO_DEBUG_ASSERT(index < this->size());

				if(this->is_small()){
					return this->get_small()[index];
				}else{
					return this->get_big()[index];
				}
			};


			template<std::enable_if<std::is_same_v<size_type, size_t>> = false>
			EVO_NODISCARD auto at(size_type index) noexcept -> T& { return this->at(size_t(index)); };

			template<std::enable_if<std::is_same_v<size_type, size_t>> = false>
			EVO_NODISCARD auto at(size_type index) const noexcept -> const T& { return this->at(size_t(index)); };



			///////////////////////////////////
			// operator[]

			EVO_NODISCARD auto operator[](size_t index)       noexcept ->       T& { return this->at(index); };
			EVO_NODISCARD auto operator[](size_t index) const noexcept -> const T& { return this->at(index); };

			template<std::enable_if<std::is_same_v<size_type, size_t>> = false>
			EVO_NODISCARD auto operator[](size_type index)       noexcept ->       T& { return this->at(index); };

			template<std::enable_if<std::is_same_v<size_type, size_t>> = false>
			EVO_NODISCARD auto operator[](size_type index) const noexcept -> const T& { return this->at(index); };


			///////////////////////////////////
			// front

			EVO_NODISCARD auto front() noexcept -> T& {
				if(this->is_small()){
					return this->get_small().front();
				}else{
					return this->get_big().front();
				}
			};

			EVO_NODISCARD auto front() const noexcept -> const T& {
				if(this->is_small()){
					return this->get_small().front();
				}else{
					return this->get_big().front();
				}
			};


			///////////////////////////////////
			// back

			EVO_NODISCARD auto back() noexcept -> T& {
				if(this->is_small()){
					return this->get_small().back();
				}else{
					return this->get_big().back();
				}
			};

			EVO_NODISCARD auto back() const noexcept -> const T& {
				if(this->is_small()){
					return this->get_small().back();
				}else{
					return this->get_big().back();
				}
			};


			///////////////////////////////////
			// data

			EVO_NODISCARD auto data() noexcept -> T* {
				if(this->is_small()){
					return this->get_small().data();
				}else{
					return this->get_big().data();
				}
			};

			EVO_NODISCARD auto data() const noexcept -> const T* {
				if(this->is_small()){
					return this->get_small().data();
				}else{
					return this->get_big().data();
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


			EVO_NODISCARD auto rbegin()        noexcept -> reverse_iterator       { return reverse_iterator{&this->data()[this->size()-1]};      };
			EVO_NODISCARD auto rbegin()  const noexcept -> const_reverse_iterator { return const_reverse_iterator{&this->data()[this->size()-1]};};
			EVO_NODISCARD auto crbegin() const noexcept -> const_reverse_iterator { return const_reverse_iterator{&this->data()[this->size()-1]};};

			EVO_NODISCARD auto rend()        noexcept -> reverse_iterator       { return reverse_iterator{this->data()-1};       };
			EVO_NODISCARD auto rend()  const noexcept -> const_reverse_iterator { return const_reverse_iterator{this->data()-1}; };
			EVO_NODISCARD auto crend() const noexcept -> const_reverse_iterator { return const_reverse_iterator{this->data()-1}; };



			//////////////////////////////////////////////////////////////////////
			// capacity

			EVO_NODISCARD auto empty() const noexcept -> bool {
				if(this->is_small()){
					return this->get_small().empty();
				}else{
					return this->get_big().empty();
				}
			};

			EVO_NODISCARD auto size() const noexcept -> size_t {
				if(this->is_small()){
					return this->get_small().size();
				}else{
					return this->get_big().size();
				}
			};

			EVO_NODISCARD constexpr static auto max_size() noexcept -> size_t {
				return size_t(std::numeric_limits<difference_type>::max() / sizeof(T));
			};

			EVO_NODISCARD auto capacity() const noexcept -> size_t {
				if(this->is_small()){
					return this->get_small().capactity();
				}else{
					return this->get_big().capactity();
				}
			};


			EVO_NODISCARD constexpr static auto small_capacity() noexcept -> size_t {
				return SMALL_CAPACITY;
			};


			//////////////////////////////////////////////////////////////////////
			// modify

			///////////////////////////////////
			// clear

			auto clear() noexcept -> void {
				this->emplace_data<StaticVector<T, SMALL_CAPACITY>>();
			};

			///////////////////////////////////
			// reserve

			auto reserve(size_t new_cap) noexcept -> void {
				if(this->is_big()){
					this->get_big().reserve(new_cap);

				}else if(new_cap > SMALL_CAPACITY){
					this->copy_to_big();
					this->get_big().reserve(new_cap);
				}
			};



			///////////////////////////////////
			// insert

			auto insert(const_iterator pos, const T& value) noexcept -> iterator {
				return this->emplace(pos, value);
			};


			auto insert(const_iterator pos, T&& value) noexcept -> iterator {
				return this->emplace(pos, std::move(value));
			};


			// not implemented yet: auto insert(const_iterator pos, size_type count, const T& value) noexcept -> iterator
			// not implemented yet: template<class InputIt> auto insert(const_iterator pos, InputIt first, InputIt last) noexcept -> iterator
			// not implemented yet: auto insert(const_iterator pos, std::initializer_list<T> ilist) noexcept -> void;


			// not implemented yet: insert_range


			///////////////////////////////////
			// emplace

			auto emplace(const_iterator pos, auto&&... args) noexcept -> iterator {
				size_t index = (size_t(&*pos) - size_t(this->data())) / sizeof(T);

				if(this->is_small() && this->size() == SMALL_CAPACITY){
					this->copy_to_big();
				}
				this->emplace_back(std::forward<decltype(args)>(args)...);

				pos = const_iterator(this->data() + index);

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

			// not implemented yet: auto erase(const_iterator first, const_iterator last) noexcept -> iterator


			///////////////////////////////////
			// push_back

			auto push_back(const T& value) noexcept -> void {
				if(this->is_small()){
					if(this->size() == SMALL_CAPACITY){
						this->copy_to_big();
						return this->get_big().push_back(value);
					}else{
						return this->get_small().push_back(value);
					}
				}else{
					return this->get_big().push_back(value);
				}
			};

			auto push_back(T&& value) noexcept -> void {
				if(this->is_small()){
					if(this->size() == SMALL_CAPACITY){
						this->copy_to_big();
						return this->get_big().push_back(value);
					}else{
						return this->get_small().push_back(value);
					}
				}else{
					return this->get_big().push_back(value);
				}
			};


			///////////////////////////////////
			// emplace_back

			auto emplace_back(auto&&... args) noexcept -> T& {
				if(this->is_small()){
					if(this->size() == SMALL_CAPACITY){
						this->copy_to_big();
						return this->get_big().emplace_back(std::forward<decltype(args)>(args)...);
					}else{
						return this->get_small().emplace_back(std::forward<decltype(args)>(args)...);
					}
				}else{
					return this->get_big().emplace_back(std::forward<decltype(args)>(args)...);
				}
			};


			// not implemented yet: append_range

			///////////////////////////////////
			// pop_back

			auto pop_back() noexcept -> void {
				EVO_DEBUG_ASSERT(this->size() > 0);

				if(this->is_small()){
					return this->get_small().pop_back();
				}else{
					return this->get_big().pop_back();
				}
			};


			///////////////////////////////////
			// resize

			template<std::enable_if<std::is_same_v<size_type, size_t>> = false>
			auto resize(size_type new_size) noexcept -> void {
				this->resize(size_t(new_size));
			};

			auto resize(size_t new_size) noexcept -> void {
				if(this->is_small()){
					if(new_size >= SMALL_CAPACITY){
						this->copy_to_big();
						return this->get_big().resize(new_size);
					}else{
						return this->get_small().resize(new_size);
					}
				}else{
					return this->get_big().resize(new_size);
				}
			};


			// not implemented yet: swap



		private:
			EVO_NODISCARD auto is_small() const noexcept -> bool {
				return std::holds_alternative<StaticVector<T,  SMALL_CAPACITY>>(this->data_block);
			};

			EVO_NODISCARD auto is_big() const noexcept -> bool {
				return std::holds_alternative<std::vector<T>>(this->data_block);
			};


			EVO_NODISCARD auto get_small() noexcept -> StaticVector<T, SMALL_CAPACITY>& {
				EVO_DEBUG_ASSERT(this->is_small());
				return std::get<StaticVector<T, SMALL_CAPACITY>>(this->data_block);
			};

			EVO_NODISCARD auto get_small() const noexcept -> const StaticVector<T, SMALL_CAPACITY>& {
				EVO_DEBUG_ASSERT(this->is_small());
				return std::get<StaticVector<T, SMALL_CAPACITY>>(this->data_block);
			};


			EVO_NODISCARD auto get_big() noexcept -> std::vector<T>& {
				EVO_DEBUG_ASSERT(this->is_big());
				return std::get<std::vector<T>>(this->data_block);
			};

			EVO_NODISCARD auto get_big() const noexcept -> const std::vector<T>& {
				EVO_DEBUG_ASSERT(this->is_big());
				return std::get<std::vector<T>>(this->data_block);
			};



			template<typename U>
			auto emplace_data(auto&&... args) noexcept -> void {
				// I have absolutely no idea why I need to write it this way, but it won't compile otherwise
				this->data_block.template emplace<U>(std::forward<decltype(args)>(args)...);
			};


			auto copy_to_big() noexcept -> void {
				auto temp_holder = std::vector<T>();

				if constexpr(std::is_trivially_move_constructible_v<T> && std::is_trivially_constructible_v<T>){
					temp_holder.resize(this->size());
					std::memcpy(temp_holder.data(), this->get_small().data(), this->get_small().size() * sizeof(T));
				}else{
					temp_holder.reserve(this->size());
					for(T& elem : this->get_small()){
						temp_holder.emplace_back(std::move(elem));
					}
				}

				this->get_small().clear();

				this->emplace_data<std::vector<T>>(std::move(temp_holder));
			};

	
		private:
			std::variant<StaticVector<T, SMALL_CAPACITY>, std::vector<T>> data_block;
			
	};


};


