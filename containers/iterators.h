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


            constexpr ConstIterator(const T* ptr) noexcept : iter(ptr) {};
            constexpr ~ConstIterator() = default;


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
    
        private:
            const T* iter;
    };



    template<typename T>
    class Iterator{
        public:
            using difference_type   = std::ptrdiff_t;
            using value_type        = T;
            using pointer           = T*;
            using reference         = T&;

            constexpr Iterator(T* ptr) noexcept : iter(ptr) {};
            constexpr ~Iterator() = default;


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


            EVO_NODISCARD operator ConstIterator<T>() noexcept {
                return ConstIterator<T>(static_cast<const T*>(this->iter));
            };
    
        private:
            T* iter;
    };







    template<typename T>
    class ConstReverseIterator{
        public:
            using difference_type   = std::ptrdiff_t;
            using value_type        = T;
            using pointer           = const T*;
            using reference         = const T&;


            constexpr ConstReverseIterator(const T* ptr) noexcept : iter(ptr) {};
            constexpr ~ConstReverseIterator() = default;


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
    
        private:
            const T* iter;
    };



    template<typename T>
    class ReverseIterator{
        public:
            using difference_type   = std::ptrdiff_t;
            using value_type        = T;
            using pointer           = T*;
            using reference         = T&;

            constexpr ReverseIterator(T* ptr) noexcept : iter(ptr) {};
            constexpr ~ReverseIterator() = default;


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


            EVO_NODISCARD operator ConstReverseIterator<T>() noexcept {
                return ConstReverseIterator<T>(static_cast<const T*>(this->iter));
            };
    
        private:
            T* iter;
    };




    
};



//////////////////////////////////////////////////////////////////////
// integration with std functions


///////////////////////////////////
// iterator

namespace std{
    


    template<typename T>
    constexpr auto advance(evo::Iterator<T>& it, std::ptrdiff_t n) noexcept -> void {
        while(n > 0){
            ++it;
            --n; 
        };

        while(n < 0){
            --it;
            ++n; 
        };
    };


    template<typename T>
    EVO_NODISCARD constexpr auto next(evo::Iterator<T> it, std::ptrdiff_t n) noexcept -> evo::Iterator<T> {
        while(n > 0){
            ++it;
            --n; 
        };
        return it;
    };
    template<typename T>
    EVO_NODISCARD constexpr auto next(evo::Iterator<T> it) noexcept -> evo::Iterator<T> {
        return ++it;
    };


    template<typename T>
    EVO_NODISCARD constexpr auto prev(evo::Iterator<T> it, std::ptrdiff_t n) noexcept -> evo::Iterator<T> {
        while(n < 0){
            --it;
            ++n; 
        };
        return it;
    };
    template<typename T>
    EVO_NODISCARD constexpr auto prev(evo::Iterator<T> it) noexcept -> evo::Iterator<T> {
        return --it;
    };



    template<typename T>
    EVO_NODISCARD constexpr auto distance(evo::Iterator<T> first, evo::Iterator<T> last) noexcept -> size_t {
        size_t count = 0;
        while(last != first){
            first = next(first);
            count += 1;
        };
        return 0;
    };




    ///////////////////////////////////
    // const iterator

    template<typename T>
    constexpr auto advance(evo::ConstIterator<T>& it, std::ptrdiff_t n) noexcept -> void {
        while(n > 0){
            ++it;
            --n; 
        };

        while(n < 0){
            --it;
            ++n; 
        };
    };


    template<typename T>
    EVO_NODISCARD constexpr auto next(evo::ConstIterator<T> it, std::ptrdiff_t n) noexcept -> evo::ConstIterator<T> {
        while(n > 0){
            ++it;
            --n; 
        };
        return it;
    };
    template<typename T>
    EVO_NODISCARD constexpr auto next(evo::ConstIterator<T> it) noexcept -> evo::ConstIterator<T> {
        return ++it;
    };


    template<typename T>
    EVO_NODISCARD constexpr auto prev(evo::ConstIterator<T> it, std::ptrdiff_t n) noexcept -> evo::ConstIterator<T> {
        while(n < 0){
            --it;
            ++n; 
        };
        return it;
    };
    template<typename T>
    EVO_NODISCARD constexpr auto prev(evo::ConstIterator<T> it) noexcept -> evo::ConstIterator<T> {
        return --it;
    };



    template<typename T>
    EVO_NODISCARD constexpr auto distance(evo::ConstIterator<T> first, evo::ConstIterator<T> last) noexcept -> size_t {
        size_t count = 0;
        while(last != first){
            first = next(first);
            count += 1;
        };
        return 0;
    };


    ///////////////////////////////////
    // reverse iterator

    template<typename T>
    constexpr auto advance(evo::ReverseIterator<T>& it, std::ptrdiff_t n) noexcept -> void {
        while(n > 0){
            ++it;
            --n; 
        };

        while(n < 0){
            --it;
            ++n; 
        };
    };


    template<typename T>
    EVO_NODISCARD constexpr auto next(evo::ReverseIterator<T> it, std::ptrdiff_t n) noexcept -> evo::ReverseIterator<T> {
        while(n > 0){
            ++it;
            --n; 
        };
        return it;
    };
    template<typename T>
    EVO_NODISCARD constexpr auto next(evo::ReverseIterator<T> it) noexcept -> evo::ReverseIterator<T> {
        return ++it;
    };


    template<typename T>
    EVO_NODISCARD constexpr auto prev(evo::ReverseIterator<T> it, std::ptrdiff_t n) noexcept -> evo::ReverseIterator<T> {
        while(n < 0){
            --it;
            ++n; 
        };
        return it;
    };
    template<typename T>
    EVO_NODISCARD constexpr auto prev(evo::ReverseIterator<T> it) noexcept -> evo::ReverseIterator<T> {
        return --it;
    };



    template<typename T>
    EVO_NODISCARD constexpr auto distance(evo::ReverseIterator<T> first, evo::ReverseIterator<T> last) noexcept -> size_t {
        size_t count = 0;
        while(last != first){
            first = next(first);
            count += 1;
        };
        return 0;
    };


    ///////////////////////////////////
    // const reverse iterator

    template<typename T>
    constexpr auto advance(evo::ConstReverseIterator<T>& it, std::ptrdiff_t n) noexcept -> void {
        while(n > 0){
            ++it;
            --n; 
        };

        while(n < 0){
            --it;
            ++n; 
        };
    };


    template<typename T>
    EVO_NODISCARD constexpr auto next(evo::ConstReverseIterator<T> it, std::ptrdiff_t n) noexcept -> evo::ConstReverseIterator<T> {
        while(n > 0){
            ++it;
            --n; 
        };
        return it;
    };
    template<typename T>
    EVO_NODISCARD constexpr auto next(evo::ConstReverseIterator<T> it) noexcept -> evo::ConstReverseIterator<T> {
        return ++it;
    };


    template<typename T>
    EVO_NODISCARD constexpr auto prev(evo::ConstReverseIterator<T> it, std::ptrdiff_t n) noexcept -> evo::ConstReverseIterator<T> {
        while(n < 0){
            --it;
            ++n; 
        };
        return it;
    };
    template<typename T>
    EVO_NODISCARD constexpr auto prev(evo::ConstReverseIterator<T> it) noexcept -> evo::ConstReverseIterator<T> {
        return --it;
    };



    template<typename T>
    EVO_NODISCARD constexpr auto distance(evo::ConstReverseIterator<T> first, evo::ConstReverseIterator<T> last) noexcept -> size_t {
        size_t count = 0;
        while(last != first){
            first = next(first);
            count += 1;
        };
        return 0;
    };

};
