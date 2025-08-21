#pragma once

#include <iterator>

#include "../defines.h"




namespace evo{


	template<class ITER>
	class IterRange{
		public:
			using iterator = ITER;

			EVO_NODISCARD constexpr IterRange(const ITER& begin_iter, const ITER& end_iter) noexcept : _begin(begin_iter), _end(end_iter) {};
			EVO_NODISCARD constexpr IterRange(ITER&& begin_iter, const ITER& end_iter) noexcept : _begin(std::move(begin_iter)), _end(end_iter) {};
			EVO_NODISCARD constexpr IterRange(const ITER& begin_iter, ITER&& end_iter) noexcept : _begin(begin_iter), _end(std::move(end_iter)) {};
			EVO_NODISCARD constexpr IterRange(ITER&& begin_iter, ITER&& end_iter) noexcept : _begin(std::move(begin_iter)), _end(std::move(end_iter)) {};

			~IterRange() noexcept = default;
		
			EVO_NODISCARD constexpr auto begin() const noexcept -> const ITER& { return this->_begin; };
			EVO_NODISCARD constexpr auto end() const noexcept -> const ITER& { return this->_end; };

			EVO_NODISCARD constexpr auto size() const noexcept -> size_t { return std::distance(this->_begin, this->_end); };
			EVO_NODISCARD constexpr auto empty() const noexcept -> bool { return this->size() == 0; };

		private:
			ITER _begin;
			ITER _end;
	};
	

};