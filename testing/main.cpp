
#include "../Evo.h"


namespace tests{

	class TestingType{
		public:
			//////////////////////////////////////////////////////////////////////
			// special member functions

			constexpr TestingType() noexcept : initialized(true) {};


			///////////////////////////////////
			// copy

			constexpr TestingType(const TestingType& src) noexcept : initialized(true), is_copy(true) {};

			constexpr TestingType& operator=(const TestingType& src) {
				this->is_copy = true;
				return *this;
			};


			///////////////////////////////////
			// move

			constexpr TestingType(TestingType&& src) noexcept : initialized(true) { this->operator=(std::move(src)); };

			constexpr TestingType& operator=(TestingType&& src) {
				src.initialized = false;
				src.moved_from = true;
				return *this;
			};


			///////////////////////////////////
			// deleted constructors

			constexpr TestingType(const TestingType&&) = delete;
			constexpr TestingType& operator=(const TestingType&&) = delete;
			


			///////////////////////////////////
			// general functions

			EVO_NODISCARD constexpr auto isInitialized() const noexcept -> bool { return this->initialized; };
			EVO_NODISCARD constexpr auto isMovedFrom() const noexcept -> bool { return this->moved_from; };
			EVO_NODISCARD constexpr auto isCopy() const noexcept -> bool { return this->is_copy; };


		private:
			bool initialized = false;
			bool moved_from = false;
			bool is_copy = false;
	};




	EVO_NODISCARD auto static_vector_test() noexcept -> bool {
		auto static_vector = evo::StaticVector<int, 6>{};

		static_vector.insert(static_vector.cbegin(), 2);
		static_vector.insert(std::next(static_vector.cbegin()), 3);
		static_vector.emplace(static_vector.cbegin(), 1);

		if(static_vector[0] != 1 || static_vector.at(1) != 2 || static_vector[2] != 3){
			evo::logError("evo::StaticVector::insert test failed");
			return false;
		}

		evo::logInfo("StaticVector tests passed");
		return true;
	};


	
};












enum class FlagsTest{
	A,
	B,
	C,

	_max,
};

auto main() noexcept -> int {
	int num_failed = 0;


	// evo::logTrace("logging test (Trace)");
	// evo::logDebug("logging test (Debug)");
	// evo::logInfo("logging test (Info)");
	// evo::logWarning("logging test (Warning)");
	// evo::logError("logging test (Error)");
	// evo::logFatal("logging test (Fatal)");


	// auto flags         = evo::Flags<FlagsTest>();
	// auto static_string = evo::StaticString<5>{"hello"};
	if(tests::static_vector_test() == false){ num_failed += 1; }
	// auto static_vector = evo::StaticVector<int, 6>{};
	// auto array_proxy   = evo::ArrayProxy<int>{static_vector};



	// tests::TestingType foo = {};
	// tests::TestingType bar{std::move(foo)};
	// tests::TestingType meow{};
	// meow = std::move(bar);

	evo::log('\n');

	if(num_failed == 0){
		evo::logInfo("All tests passed!");
	}else{
		evo::logError(std::format("Tests failed: {}", num_failed));
	}

	return 0;
};