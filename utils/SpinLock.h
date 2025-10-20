#pragma once

#include "../defines.h"

#include <atomic>
#include <thread>


namespace evo{

	// adapted from: https://www.youtube.com/watch?v=rmGJc9PXpuE (Fedor Pikus)
	template<int INITIAL_WAIT_THRESHOLD = 8>
	class SpinLockCustom{
		public:
			SpinLockCustom() = default;
			~SpinLockCustom() = default;

			auto lock() noexcept -> void {
				int wait_threshold = INITIAL_WAIT_THRESHOLD;
				int wait_iter = 0;

				while(this->try_lock() == false){
					if(wait_iter == wait_threshold){
						std::this_thread::yield();

						wait_iter = 0;
						if(wait_threshold < 0){ wait_threshold -= 1; }
					}else{
						wait_iter += 1;
					}
				}
			}

			EVO_NODISCARD auto try_lock() noexcept -> bool {
				return this->flag.load(std::memory_order_relaxed) == 0
					&& this->flag.exchange(1, std::memory_order_acquire) == 0;
			}

			auto unlock() noexcept -> void {
				this->flag.store(0, std::memory_order_release);
			}

			auto lock_shared() noexcept -> void { this->lock(); }
			auto unlock_shared() noexcept -> void { this->unlock(); }
	
		private:
			std::atomic<uint32_t> flag = 0; // surprisingly, this was measured to be faster than uint64_t
	};


	using SpinLock = SpinLockCustom<>;


}