#pragma once

#include <functional>

#define EVO_DEFER(callback) ::evo::Defer _evo_defer_num ## __COUNTER__ = ::evo::Defer(callback)

namespace evo{

	class Defer{
		public:
			EVO_NODISCARD Defer(const std::function<void()>& defer_callback) noexcept : callback(defer_callback) {};
			EVO_NODISCARD Defer(std::function<void()>&& defer_callback) noexcept : callback(std::move(defer_callback)) {};

			~Defer() noexcept {
				callback();
			};


			Defer(const Defer&) = delete;
			Defer(Defer&&) = delete;
	
		private:
			std::function<void()> callback;
	};
	


};