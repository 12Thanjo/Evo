#pragma once

#include <functional>

#define EVO_DEFER(callback) ::evo::Defer EVO_CONCAT(_evo_defer_num, __COUNTER__) = ::evo::Defer(callback)

namespace evo{

	class Defer{
		public:
			[[nodiscard]] Defer(const std::function<void()>& defer_callback) noexcept : callback(defer_callback) {};
			[[nodiscard]] Defer(std::function<void()>&& defer_callback) noexcept : callback(std::move(defer_callback)) {};

			~Defer() noexcept {
				callback();
			};


			Defer(const Defer&) = delete;
			Defer(Defer&&) = delete;
	
		private:
			std::function<void()> callback;
	};
	


};