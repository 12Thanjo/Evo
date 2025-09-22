#pragma once


#include "./SmallVector.h"

namespace evo{


	// picks either the size of a cache-line or 4 elements (whichever makes more sense for the size of the type)
	template<class T>
	EVO_NODISCARD consteval auto get_optimal_start_pow_of_2_for_step_vector() noexcept -> size_t {
		const size_t num_bits = std::bit_ceil(std::hardware_destructive_interference_size / sizeof(T));
		return std::max(size_t(2), size_t(std::countr_zero(num_bits)));
	}


	template<class T, size_t STARTING_POW_OF_2 = get_optimal_start_pow_of_2_for_step_vector<T>()>
	class StepVector{
		public:
			constexpr StepVector() noexcept = default;
			constexpr ~StepVector() noexcept {
				if(this->buffers.empty()){ return; }

				if(this->buffers.size() > 1){
					for(size_t i = 0; i < this->buffers.size() - 1; i+=1){
						std::destroy_n(this->buffers[i], size_t(1) << (i + STARTING_POW_OF_2));
						std::free(this->buffers[i]);
					}
				}

				std::destroy_n(this->buffers.back(), this->current_end_of_buffer);
				std::free(this->buffers.back());
			};


			constexpr StepVector(const StepVector<T, STARTING_POW_OF_2>& rhs) noexcept {
				this->buffers.reserve(rhs.size());
				for(const T& elem : rhs){
					this->emplace_back(elem);
				}
			}

			constexpr StepVector(StepVector<T, STARTING_POW_OF_2>&& rhs) noexcept
				: buffers(std::move(rhs.buffers)), current_end_of_buffer(std::move(rhs.current_end_of_buffer)) {}



			constexpr auto operator=(const StepVector<T, STARTING_POW_OF_2>& rhs) noexcept -> StepVector<T, STARTING_POW_OF_2>& {
				std::destroy_at(this);
				std::construct_at(this, rhs);
				return *this;
			}

			constexpr auto operator=(StepVector<T, STARTING_POW_OF_2>&& rhs) noexcept -> StepVector<T, STARTING_POW_OF_2>& {
				std::destroy_at(this);
				std::construct_at(this, std::move(rhs));
				return *this;
			}




			constexpr auto emplace_back(auto&&... args) noexcept -> T& {
				if(this->need_to_create_new_buffer()){ this->create_new_buffer(); }

				T* new_elem_ptr = &this->buffers.back()[this->current_end_of_buffer];

				// using placement new to allow for construction of type that have private constructors but are friends
				::new (static_cast<void*>(new_elem_ptr)) T(std::forward<decltype(args)>(args)...);

				EVO_DEFER([&](){ this->current_end_of_buffer += 1; });

				return *new_elem_ptr;
			}


			constexpr auto push_back(const T& value) noexcept -> void {
				this->emplace_back(value);
			}

			constexpr auto push_back(T&& value) noexcept -> void {
				this->emplace_back(value);
			}



			constexpr auto pop_back() noexcept -> void {
				std::destroy_at(&this->back());

				this->current_end_of_buffer -= 1;

				if(this->current_end_of_buffer == 0){
					std::free(this->buffers.back());
					this->buffers.pop_back();
				}
			}


			constexpr auto resize(size_t new_size) noexcept -> void {
				const size_t current_size = this->size();

				if(new_size > current_size){
					for(size_t i = 0; i < new_size - current_size; i+=1){
						this->emplace_back();
					}

				}else{
					for(size_t i = 0; i < current_size - new_size; i+=1){
						this->pop_back();
					}
				}
			}


			
			EVO_NODISCARD constexpr auto operator[](size_t index) const noexcept -> const T& {
				const BufferAndElemIndex indices = this->get_buffer_and_elem_index(index);
				return this->buffers[indices.buffer_index][indices.elem_index];
			}

			EVO_NODISCARD constexpr auto operator[](size_t index) noexcept -> T& {
				const BufferAndElemIndex indices = this->get_buffer_and_elem_index(index);
				return this->buffers[indices.buffer_index][indices.elem_index];
			}


			EVO_NODISCARD constexpr auto at(size_t index) const noexcept -> const T& {
				return this->operator[](index);
			}

			EVO_NODISCARD constexpr auto at(size_t index) noexcept -> T& {
				return this->operator[](index);
			}


			EVO_NODISCARD constexpr auto size() const noexcept -> size_t {
				if(this->buffers.empty()){ return 0; }
				return this->size_when_not_fully_deallocated();
			}

			EVO_NODISCARD constexpr auto empty() const noexcept -> bool { return this->size() == 0; }



			constexpr auto clear() noexcept -> void {
				std::destroy_at(this);
				std::construct_at(this);
			}



			EVO_NODISCARD constexpr auto front() const noexcept -> const T& { return this->buffers[0][0]; }
			EVO_NODISCARD constexpr auto front()       noexcept ->       T& { return this->buffers[0][0]; }

			EVO_NODISCARD constexpr auto back() const noexcept -> const T& { return this->buffers.back()[this->current_end_of_buffer-1]; }
			EVO_NODISCARD constexpr auto back()       noexcept ->       T& { return this->buffers.back()[this->current_end_of_buffer-1]; }



			//////////////////////////////////////////////////////////////////////
			// iterators

			class Iter{
			    public:
			    	using difference_type   = std::ptrdiff_t;
			    	using value_type        = T;
			    	using pointer           = const T*;
			    	using reference         = const T&;

			        Iter() : index(), parent(nullptr) {};
			        Iter(size_t _index, StepVector& _parent) : index(_index), parent(&_parent) {};
			        ~Iter() = default;

			        Iter(const Iter&) = default;
			        constexpr auto operator=(const Iter& rhs) noexcept -> Iter& {
			        	std::construct_at(this, rhs);
			        	return *this;
			        };
			        Iter(Iter&&) = default;
			        constexpr auto operator=(Iter&& rhs) noexcept -> Iter& {
			        	std::construct_at(this, std::move(rhs));
			        	return *this;
			        };


			        constexpr auto operator++() noexcept -> Iter& {
			            this->index += 1;
			            return *this;
			        }

			        constexpr auto operator++(int) noexcept -> Iter {
			            Iter iterator = *this;
			            ++(*this);
			            return iterator;
			        }

			        constexpr auto operator--() noexcept -> Iter& {
			            this->index -= 1;
			            return *this;
			        }

			        constexpr auto operator--(int) noexcept -> Iter {
			            Iter iterator = *this;
			            --(*this);
			            return iterator;
			        }


			        EVO_NODISCARD constexpr auto operator*() const noexcept -> T& { return this->parent->operator[](this->index); }
			        EVO_NODISCARD constexpr auto operator->() const noexcept -> T* { return &this->parent->operator[](this->index); }

			        EVO_NODISCARD constexpr auto operator==(const Iter& rhs) const noexcept -> bool {
			        	return this->index == rhs.index;
			        }
			        EVO_NODISCARD constexpr auto operator!=(const Iter& rhs) const noexcept -> bool {
			        	return this->index != rhs.index;
			        }

			    private:
			    	size_t index;
			        StepVector* parent;
			};


			class ConstIter{
			    public:
			    	using difference_type   = std::ptrdiff_t;
			    	using value_type        = T;
			    	using pointer           = const T*;
			    	using reference         = const T&;

			        ConstIter() : index(), parent(nullptr) {};
			        ConstIter(size_t _index, const StepVector& _parent) : index(_index), parent(&_parent) {};
			        ~ConstIter() = default;

			        ConstIter(const ConstIter&) = default;
			        constexpr auto operator=(const ConstIter& rhs) noexcept -> ConstIter& {
			        	std::construct_at(this, rhs);
			        	return *this;
			        };
			        ConstIter(ConstIter&&) = default;
			        constexpr auto operator=(ConstIter&& rhs) noexcept -> ConstIter& {
			        	std::construct_at(this, std::move(rhs));
			        	return *this;
			        };


			        constexpr auto operator++() noexcept -> ConstIter& {
						this->index += 1;
			            return *this;
			        }

			        constexpr auto operator++(int) noexcept -> ConstIter {
			            ConstIter iterator = *this;
			            ++(*this);
			            return iterator;
			        }

			        constexpr auto operator--() noexcept -> ConstIter& {
			            this->index -= 1;
			            return *this;
			        }

			        constexpr auto operator--(int) noexcept -> ConstIter {
			            ConstIter iterator = *this;
			            --(*this);
			            return iterator;
			        }


			        EVO_NODISCARD constexpr auto operator*() const noexcept -> const T& { return this->parent->operator[](this->index); }
			        EVO_NODISCARD constexpr auto operator->() const noexcept -> const T* { return &this->parent->operator[](this->index); }

			        EVO_NODISCARD constexpr auto operator==(const ConstIter& rhs) const noexcept -> bool {
			        	return this->index == rhs.index;
			        }
			        EVO_NODISCARD constexpr auto operator!=(const ConstIter& rhs) const noexcept -> bool {
			        	return this->index != rhs.index;
			        }

			    private:
			    	size_t index;
			        const StepVector* parent;
			};


			using value_type             = T;
			using size_type              = size_t;
			using difference_type        = std::ptrdiff_t;
			using reference              = T&;
			using const_reference        = const T&;
			using pointer                = T*;
			using const_pointer          = const T*;
			using iterator               = Iter;
			using const_iterator         = ConstIter;
			// using reverse_iterator       = ReverseIter;
			// using const_reverse_iterator = ConstReverseIter;


			EVO_NODISCARD constexpr auto begin()        noexcept ->      Iter { return Iter(0, *this);      }
			EVO_NODISCARD constexpr auto begin()  const noexcept -> ConstIter { return ConstIter(0, *this); }
			EVO_NODISCARD constexpr auto cbegin() const noexcept -> ConstIter { return ConstIter(0, *this); }

			EVO_NODISCARD constexpr auto end()        noexcept ->      Iter { return Iter(this->size(), *this);      }
			EVO_NODISCARD constexpr auto end()  const noexcept -> ConstIter { return ConstIter(this->size(), *this); }
			EVO_NODISCARD constexpr auto cend() const noexcept -> ConstIter { return ConstIter(this->size(), *this); }


			// TODO(FUTURE): reverse iterators?


		private:
			EVO_NODISCARD constexpr auto size_when_not_fully_deallocated() const noexcept -> size_t {
				return (size_t(1) << (this->buffers.size() - 1 + STARTING_POW_OF_2)) - (1 << STARTING_POW_OF_2)
					+ this->current_end_of_buffer;
			}


			EVO_NODISCARD constexpr auto current_buffer_max_size() const noexcept -> size_t {
				evo::debugAssert(this->buffers.empty() == false, "no buffer to get max size of");
				return 1ull << (this->buffers.size() - 1 + STARTING_POW_OF_2);
			}

			EVO_NODISCARD constexpr auto need_to_create_new_buffer() const noexcept -> bool {
				if(this->buffers.empty()){ return true; }
				return this->current_end_of_buffer >= this->current_buffer_max_size();
			}

			constexpr auto create_new_buffer() noexcept -> void {
				const size_t size_of_new_buffer = size_t(1) << (this->buffers.size() + STARTING_POW_OF_2);

				this->buffers.emplace_back((T*)std::malloc(sizeof(T) * size_of_new_buffer));
				this->current_end_of_buffer = 0;
			}

			struct BufferAndElemIndex{
				size_t buffer_index;
				size_t elem_index;
			};
			EVO_NODISCARD constexpr auto get_buffer_and_elem_index(size_t index) const noexcept -> BufferAndElemIndex {
				const uint64_t converted_index = uint64_t(index) + (1 << STARTING_POW_OF_2);
				
				const uint64_t buffer_index = std::bit_width(converted_index) - 1;
				const uint64_t elem_index = converted_index & ~(1ull << buffer_index);

				return BufferAndElemIndex(size_t(buffer_index) - STARTING_POW_OF_2, size_t(elem_index));
			}

	
		private:
			SmallVector<T*> buffers{};
			uint32_t current_end_of_buffer = 0;
	};


}


