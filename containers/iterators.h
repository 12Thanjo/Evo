#pragma once

#include "../defines.h"

#include <iterator>

namespace evo{



    template<typename T>
    class ConstIterator{
        public:
            using difference_type   = std::ptrdiff_t;
            using value_type        = T;
            using pointer           = const T*;
            using reference         = const T&;

            constexpr ConstIterator() noexcept : iter(nullptr) {};
            constexpr ConstIterator(const T* ptr) noexcept : iter(ptr) {};
            constexpr ~ConstIterator() = default;

            constexpr ConstIterator(const ConstIterator&) = default;
            constexpr auto operator=(const ConstIterator& rhs) -> ConstIterator& {
                std::construct_at(this, rhs);
                return *this;
            };

            constexpr ConstIterator(ConstIterator&&) = default;
            constexpr auto operator=(ConstIterator&& rhs) -> ConstIterator& {
                std::construct_at(this, std::move(rhs));
                return *this;
            };


            constexpr auto operator++() noexcept -> ConstIterator<T>& {
                this->iter++;
                return *this;
            };

            constexpr auto operator++(int) noexcept -> ConstIterator<T> {
                ConstIterator<T> iterator = *this;
                ++(*this);
                return iterator;
            };


            constexpr auto operator--() noexcept -> ConstIterator<T>& {
                this->iter--;
                return *this;
            };

            constexpr auto operator--(int) noexcept -> ConstIterator<T> {
                ConstIterator<T> iterator = *this;
                --(*this);
                return iterator;
            };


            EVO_NODISCARD constexpr auto inBounds(const ConstIterator& begin, const ConstIterator& end) const -> bool {
                return this->iter >= begin.iter && this->iter <= end.iter;
            };


            EVO_NODISCARD constexpr auto operator*() const noexcept -> const T& { return *this->iter; };
            EVO_NODISCARD constexpr auto operator->() const noexcept -> const T* { return this->iter; };
            EVO_NODISCARD constexpr auto operator==(const ConstIterator<T>& rhs) const noexcept -> bool { return this->iter == rhs.iter; };
            EVO_NODISCARD constexpr auto operator!=(const ConstIterator<T>& rhs) const noexcept -> bool { return this->iter != rhs.iter; };
            EVO_NODISCARD constexpr auto operator<(const ConstIterator<T>& rhs)  const noexcept -> bool { return this->iter < rhs.iter; };
            EVO_NODISCARD constexpr auto operator<=(const ConstIterator<T>& rhs) const noexcept -> bool { return this->iter <= rhs.iter; };
            EVO_NODISCARD constexpr auto operator>(const ConstIterator<T>& rhs)  const noexcept -> bool { return this->iter > rhs.iter; };
            EVO_NODISCARD constexpr auto operator>=(const ConstIterator<T>& rhs) const noexcept -> bool { return this->iter >= rhs.iter; };


            constexpr auto operator+=(difference_type n) noexcept -> ConstIterator<T>& {
                this->iter += n;
                return *this; 
            }

            EVO_NODISCARD constexpr auto operator+(difference_type n) const noexcept -> ConstIterator<T> {
                ConstIterator<T> self_copy = *this;
                self_copy += n;
                return self_copy;
            }

            constexpr auto operator-=(difference_type n) noexcept -> ConstIterator<T>& {
                this->iter -= n;
                return *this;
            }

            EVO_NODISCARD constexpr auto operator-(difference_type n) const noexcept -> ConstIterator<T> {
                ConstIterator<T> self_copy = *this;
                self_copy -= n;
                return self_copy;
            }

            EVO_NODISCARD constexpr auto operator-(const ConstIterator<T>& rhs) const noexcept -> difference_type {
                return this->iter - rhs.iter;
            }

            EVO_NODISCARD constexpr auto operator[](difference_type n) const noexcept -> const T& { return *(this->iter + n); }

    
        private:
            const T* iter;
    };

    template<class T>
    constexpr auto operator+(ptrdiff_t n, const ConstIterator<T>& iter) noexcept -> ConstIterator<T> {
        ConstIterator<T> iter_copy = iter;
        return iter_copy += n;
    }



    template<typename T>
    class Iterator{
        public:
            using difference_type   = std::ptrdiff_t;
            using value_type        = T;
            using pointer           = T*;
            using reference         = T&;


            constexpr Iterator() noexcept : iter(nullptr) {};
            constexpr Iterator(T* ptr) noexcept : iter(ptr) {};
            constexpr ~Iterator() = default;

            constexpr Iterator(const Iterator&) = default;
            constexpr auto operator=(const Iterator& rhs) -> Iterator& {
                std::construct_at(this, rhs);
                return *this;
            };

            constexpr Iterator(Iterator&&) = default;
            constexpr auto operator=(Iterator&& rhs) -> Iterator& {
                std::construct_at(this, std::move(rhs));
                return *this;
            };



            constexpr auto operator++() noexcept -> Iterator<T>& {
                this->iter++;
                return *this;
            };

            constexpr auto operator++(int) noexcept -> Iterator<T> {
                Iterator<T> iterator = *this;
                ++(*this);
                return iterator;
            };


            constexpr auto operator--() noexcept -> Iterator<T>& {
                this->iter--;
                return *this;
            };

            constexpr auto operator--(int) noexcept -> Iterator<T> {
                Iterator<T> iterator = *this;
                --(*this);
                return iterator;
            };


            EVO_NODISCARD constexpr auto inBounds(const Iterator& begin, const Iterator& end) const -> bool {
                return this->iter >= begin.iter && this->iter <= end.iter;
            };


            EVO_NODISCARD constexpr auto operator*() const noexcept -> T& { return *this->iter; };
            EVO_NODISCARD constexpr auto operator->() const noexcept -> T* { return this->iter; };
            EVO_NODISCARD constexpr auto operator==(const Iterator<T>& rhs) const noexcept -> bool { return this->iter == rhs.iter; };
            EVO_NODISCARD constexpr auto operator!=(const Iterator<T>& rhs) const noexcept -> bool { return this->iter != rhs.iter; };
            EVO_NODISCARD constexpr auto operator<(const Iterator<T>& rhs)  const noexcept -> bool { return this->iter < rhs.iter; };
            EVO_NODISCARD constexpr auto operator<=(const Iterator<T>& rhs) const noexcept -> bool { return this->iter <= rhs.iter; };
            EVO_NODISCARD constexpr auto operator>(const Iterator<T>& rhs)  const noexcept -> bool { return this->iter > rhs.iter; };
            EVO_NODISCARD constexpr auto operator>=(const Iterator<T>& rhs) const noexcept -> bool { return this->iter >= rhs.iter; };


            constexpr auto operator+=(difference_type n) noexcept -> Iterator<T>& {
                this->iter += n;
                return *this; 
            }

            EVO_NODISCARD constexpr auto operator+(difference_type n) const noexcept -> Iterator<T> {
                Iterator<T> self_copy = *this;
                self_copy += n;
                return self_copy;
            }

            constexpr auto operator-=(difference_type n) noexcept -> Iterator<T>& {
                this->iter -= n;
                return *this;
            }

            EVO_NODISCARD constexpr auto operator-(difference_type n) const noexcept -> Iterator<T> {
                Iterator<T> self_copy = *this;
                self_copy -= n;
                return self_copy;
            }

            EVO_NODISCARD constexpr auto operator-(const Iterator<T>& rhs) const noexcept -> difference_type {
                return this->iter - rhs.iter;
            }

            EVO_NODISCARD constexpr auto operator[](difference_type n) const noexcept -> T& { return *(this->iter + n); }



            EVO_NODISCARD operator ConstIterator<T>() noexcept {
                return ConstIterator<T>(static_cast<const T*>(this->iter));
            };

    
        private:
            T* iter;
    };


    template<class T>
    constexpr auto operator+(ptrdiff_t n, const Iterator<T>& iter) noexcept -> Iterator<T> {
        Iterator<T> iter_copy = iter;
        return iter_copy += n;
    }




    template<typename T>
    class ConstReverseIterator{
        public:
            using difference_type   = std::ptrdiff_t;
            using value_type        = T;
            using pointer           = const T*;
            using reference         = const T&;


            constexpr ConstReverseIterator() noexcept : iter(nullptr) {};
            constexpr ConstReverseIterator(const T* ptr) noexcept : iter(ptr) {};
            constexpr ~ConstReverseIterator() = default;

            constexpr ConstReverseIterator(const ConstReverseIterator&) = default;
            constexpr auto operator=(const ConstReverseIterator& rhs) -> ConstReverseIterator& {
                std::construct_at(this, rhs);
                return *this;
            };

            constexpr ConstReverseIterator(ConstReverseIterator&&) = default;
            constexpr auto operator=(ConstReverseIterator&& rhs) -> ConstReverseIterator& {
                std::construct_at(this, std::move(rhs));
                return *this;
            };



            constexpr auto operator++() noexcept -> ConstReverseIterator<T>& {
                this->iter--;
                return *this;
            };

            constexpr auto operator++(int) noexcept -> ConstReverseIterator<T> {
                ConstReverseIterator<T> iterator = *this;
                --(*this);
                return iterator;
            };


            constexpr auto operator--() noexcept -> ConstReverseIterator<T>& {
                this->iter++;
                return *this;
            };

            constexpr auto operator--(int) noexcept -> ConstReverseIterator<T> {
                ConstReverseIterator<T> iterator = *this;
                ++(*this);
                return iterator;
            };


            EVO_NODISCARD constexpr auto inBounds(const ConstReverseIterator& begin, const ConstReverseIterator& end) const -> bool {
                return this->iter >= begin.iter && this->iter <= end.iter;
            };


            EVO_NODISCARD constexpr auto operator*() const noexcept -> const T& { return *this->iter; };
            EVO_NODISCARD constexpr auto operator->() const noexcept -> const T* { return this->iter; };
            EVO_NODISCARD constexpr auto operator==(const ConstReverseIterator<T>& rhs) const noexcept -> bool { return this->iter == rhs.iter; };
            EVO_NODISCARD constexpr auto operator!=(const ConstReverseIterator<T>& rhs) const noexcept -> bool { return this->iter != rhs.iter; };
            EVO_NODISCARD constexpr auto operator<(const ConstReverseIterator<T>& rhs)  const noexcept -> bool { return this->iter < rhs.iter; };
            EVO_NODISCARD constexpr auto operator<=(const ConstReverseIterator<T>& rhs) const noexcept -> bool { return this->iter <= rhs.iter; };
            EVO_NODISCARD constexpr auto operator>(const ConstReverseIterator<T>& rhs)  const noexcept -> bool { return this->iter > rhs.iter; };
            EVO_NODISCARD constexpr auto operator>=(const ConstReverseIterator<T>& rhs) const noexcept -> bool { return this->iter >= rhs.iter; };


            constexpr auto operator+=(difference_type n) noexcept -> ConstReverseIterator<T>& {
                this->iter -= n;
                return *this; 
            }

            EVO_NODISCARD constexpr auto operator+(difference_type n) const noexcept -> ConstReverseIterator<T> {
                ConstReverseIterator<T> self_copy = *this;
                self_copy -= n;
                return self_copy;
            }

            constexpr auto operator-=(difference_type n) noexcept -> ConstReverseIterator<T>& {
                this->iter += n;
                return *this;
            }

            EVO_NODISCARD constexpr auto operator-(difference_type n) const noexcept -> ConstReverseIterator<T> {
                ConstReverseIterator<T> self_copy = *this;
                self_copy += n;
                return self_copy;
            }

            EVO_NODISCARD constexpr auto operator-(const ConstReverseIterator<T>& rhs) const noexcept -> difference_type {
                return this->iter - rhs.iter;
            }

            EVO_NODISCARD constexpr auto operator[](difference_type n) const noexcept -> const T& { return *(this->iter - n); }
    
        private:
            const T* iter;
    };

    template<class T>
    constexpr auto operator+(ptrdiff_t n, const ConstReverseIterator<T>& iter) noexcept -> ConstReverseIterator<T> {
        ConstReverseIterator<T> iter_copy = iter;
        return iter_copy -= n;
    }



    template<typename T>
    class ReverseIterator{
        public:
            using difference_type   = std::ptrdiff_t;
            using value_type        = T;
            using pointer           = T*;
            using reference         = T&;


            constexpr ReverseIterator() noexcept : iter(nullptr) {};
            constexpr ReverseIterator(T* ptr) noexcept : iter(ptr) {};
            constexpr ~ReverseIterator() = default;

            constexpr ReverseIterator(const ReverseIterator&) = default;
            constexpr auto operator=(const ReverseIterator& rhs) -> ReverseIterator& {
                std::construct_at(this, rhs);
                return *this;
            };

            constexpr ReverseIterator(ReverseIterator&&) = default;
            constexpr auto operator=(ReverseIterator&& rhs) -> ReverseIterator& {
                std::construct_at(this, std::move(rhs));
                return *this;
            };



            constexpr auto operator++() noexcept -> ReverseIterator<T>& {
                this->iter--;
                return *this;
            };

            constexpr auto operator++(int) noexcept -> ReverseIterator<T> {
                ReverseIterator<T> iterator = *this;
                --(*this);
                return iterator;
            };


            constexpr auto operator--() noexcept -> ReverseIterator<T>& {
                this->iter++;
                return *this;
            };

            constexpr auto operator--(int) noexcept -> ReverseIterator<T> {
                ReverseIterator<T> iterator = *this;
                ++(*this);
                return iterator;
            };


            EVO_NODISCARD constexpr auto inBounds(const ReverseIterator& begin, const ReverseIterator& end) const -> bool {
                return this->iter >= begin.iter && this->iter <= end.iter;
            };


            EVO_NODISCARD constexpr auto operator*() const noexcept -> T& { return *this->iter; };
            EVO_NODISCARD constexpr auto operator->() const noexcept -> T* { return this->iter; };
            EVO_NODISCARD constexpr auto operator==(const ReverseIterator<T>& rhs) const noexcept -> bool { return this->iter == rhs.iter; };
            EVO_NODISCARD constexpr auto operator!=(const ReverseIterator<T>& rhs) const noexcept -> bool { return this->iter != rhs.iter; };
            EVO_NODISCARD constexpr auto operator<(const ReverseIterator<T>& rhs)  const noexcept -> bool { return this->iter < rhs.iter; };
            EVO_NODISCARD constexpr auto operator<=(const ReverseIterator<T>& rhs) const noexcept -> bool { return this->iter <= rhs.iter; };
            EVO_NODISCARD constexpr auto operator>(const ReverseIterator<T>& rhs)  const noexcept -> bool { return this->iter > rhs.iter; };
            EVO_NODISCARD constexpr auto operator>=(const ReverseIterator<T>& rhs) const noexcept -> bool { return this->iter >= rhs.iter; };


            constexpr auto operator+=(difference_type n) noexcept -> ReverseIterator<T>& {
                this->iter -= n;
                return *this; 
            }

            EVO_NODISCARD constexpr auto operator+(difference_type n) const noexcept -> ReverseIterator<T> {
                ReverseIterator<T> self_copy = *this;
                self_copy -= n;
                return self_copy;
            }

            constexpr auto operator-=(difference_type n) noexcept -> ReverseIterator<T>& {
                this->iter += n;
                return *this;
            }

            EVO_NODISCARD constexpr auto operator-(difference_type n) const noexcept -> ReverseIterator<T> {
                ReverseIterator<T> self_copy = *this;
                self_copy += n;
                return self_copy;
            }

            EVO_NODISCARD constexpr auto operator-(const ReverseIterator<T>& rhs) const noexcept -> difference_type {
                return this->iter - rhs.iter;
            }

            EVO_NODISCARD constexpr auto operator[](difference_type n) const noexcept -> T& { return *(this->iter - n); }


            EVO_NODISCARD operator ConstReverseIterator<T>() noexcept {
                return ConstReverseIterator<T>(static_cast<const T*>(this->iter));
            };
    
        private:
            T* iter;
    };


    template<class T>
    constexpr auto operator+(ptrdiff_t n, const ReverseIterator<T>& iter) noexcept -> ReverseIterator<T> {
        ReverseIterator<T> iter_copy = iter;
        return iter_copy -= n;
    }




    static_assert(std::random_access_iterator<ConstIterator<int>>);
    static_assert(std::random_access_iterator<Iterator<int>>);
    static_assert(std::random_access_iterator<ConstReverseIterator<int>>);
    static_assert(std::random_access_iterator<ReverseIterator<int>>);


};