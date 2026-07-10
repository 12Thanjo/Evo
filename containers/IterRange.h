#pragma once

#include <iterator>

#include "../defines.h"




namespace evo{


	template<class ITER>
	class IterRange{
		public:
			using iterator = ITER;

			[[nodiscard]] constexpr IterRange(const ITER& begin_iter, const ITER& end_iter) noexcept : _begin(begin_iter), _end(end_iter) {};
			[[nodiscard]] constexpr IterRange(ITER&& begin_iter, const ITER& end_iter) noexcept : _begin(std::move(begin_iter)), _end(end_iter) {};
			[[nodiscard]] constexpr IterRange(const ITER& begin_iter, ITER&& end_iter) noexcept : _begin(begin_iter), _end(std::move(end_iter)) {};
			[[nodiscard]] constexpr IterRange(ITER&& begin_iter, ITER&& end_iter) noexcept : _begin(std::move(begin_iter)), _end(std::move(end_iter)) {};

			~IterRange() noexcept = default;
		
			[[nodiscard]] constexpr auto begin() const noexcept -> const ITER& { return this->_begin; };
			[[nodiscard]] constexpr auto end() const noexcept -> const ITER& { return this->_end; };

			[[nodiscard]] constexpr auto size() const noexcept -> size_t { return std::distance(this->_begin, this->_end); };
			[[nodiscard]] constexpr auto empty() const noexcept -> bool { return this->size() == 0; };

		private:
			ITER _begin;
			ITER _end;
	};
	

};