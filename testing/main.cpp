
#include "../Evo.h"


//////////////////////////////////////////////////////////////////////
// 																	//
//  NOTE: this file - while it does do some testing, does not fully //
//		  nor rigorously test the evo library						//
// 																	//
//////////////////////////////////////////////////////////////////////





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
		static_vector.insert(std::next(static_vector.begin()), 3);
		static_vector.emplace(static_vector.cbegin(), 1);


		if(static_vector[0] != 1 || static_vector.at(1) != 2 || static_vector[2] != 3){
			evo::printlnRed("evo::StaticVector::insert / evo::StaticVector::emplace test failed");
			return false;
		}


		static_vector = std::initializer_list{0, 1, 2, 3};

		for(size_t i = 0; i < static_vector.size(); i+=1){
			if(static_vector[i] != int(i)){
				evo::printlnRed("evo::StaticVector::operator=(std::initializer_list) test failed");
				return false;
			}
		}


		evo::printlnGreen("StaticVector tests passed");
		return true;
	};




	EVO_NODISCARD auto c_str_proxy_test() noexcept -> bool {		
		auto str = std::string{"hello"};

		auto str_proxy = evo::CStrProxy(str);

		if(str_proxy.data() != str.data()){
			evo::printlnRed("evo::CStrProxy test failed");
			return false;
		}


		return true;
	};




	EVO_NODISCARD auto bimap_test() noexcept -> bool {
		auto bimap = evo::Bimap<std::string, int>();

		auto data_vec = std::vector<std::pair<std::string, int>>();

		constexpr int num_elems = 50'000;

		// check inserting
		for(int i = 0; i < num_elems; i+=1){
			const std::string str = std::format("{:x}", i);

			data_vec.emplace_back(str, i);
			bimap.emplace(str, i);
		}

		// check iteration
		{
			int total = 0;
			for(auto& pair : bimap){
				total += pair.second;
			}

			for(int i = 0; i < num_elems; i+=1){
				total -= i;
			}

			if(total != 0){
				return false;
			}
		}

		// find all values
		for(const std::pair<std::string, int>& pair : data_vec){
			if(const auto& get = bimap.at_left(pair.first); get.first != pair.first || get.second != pair.second){ return false; }
			if(const auto& get = bimap.at_right(pair.second); get.first != pair.first || get.second != pair.second){ return false; }

			if(bimap.get_left(pair.second) != pair.first){ return false; }
			if(bimap.get_right(pair.first) != pair.second){ return false; }


			if(bimap.find_left(pair.first) == bimap.end()){ return false; }
			if(bimap.find_right(pair.second) == bimap.end()){ return false; }

			if(bimap.contains_left(pair.first) == false){ return false; }
			if(bimap.contains_right(pair.second) == false){ return false; }			
		}

		// doesn't find incorrect values
		if(bimap.find_left("asdf") != bimap.end()){ return false; }
		if(bimap.find_right(num_elems + 10) != bimap.end()){ return false; }

		if(bimap.contains_left("asdf")){ return false; }
		if(bimap.contains_right(num_elems + 10)){ return false; }


		// erase values
		bool should_erase = false;
		auto iter = data_vec.begin();

		while(iter != data_vec.end()){
			if(should_erase){
				bimap.erase_left(iter->first);
				data_vec.erase(iter);
			}else{
				iter++;
			}
		};

		if(bimap.size() != data_vec.size()){ return false; }

		// check what's left
		{
			int total = 0;
			for(auto& pair : bimap){
				total += pair.second;
			}

			for(int i = 0; i < num_elems; i+=1){
				total -= i;
			}

			if(total != 0){
				return false;
			}
		}




		evo::printlnGreen("Bimap tests passed");
		return true;
	};




	auto random_test() noexcept -> bool {

		for(uint64_t i = 0; i < 1000; i+=1){
			const uint64_t random_num = evo::random(10, 15);

			if(random_num > 15 || random_num < 10){
				return false;
			}
		}


		evo::printlnGreen("Random tests passed");
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

	// evo::log::setDefaultCallback();
	// evo::printlnWhite("hello from evo (white)");
	// evo::printlnGray("hello from evo (gray)");
	// evo::printlnBlack("hello from evo (black)");
	// evo::printlnRed("hello from evo (red)");
	// evo::printlnYellow("hello from evo (yellow)");
	// evo::printlnGreen("hello from evo (green)");
	// evo::printlnCyan("hello from evo (cyan)");
	// evo::printlnBlue("hello from evo (blue)");
	// evo::printlnMagenta("hello from evo (magenta)");


	evo::log::trace("logging test (Trace)");
	evo::log::debug("logging test (Debug)");
	evo::log::success("logging test (Success)");
	evo::log::info("logging test (Info)");
	evo::log::warning("logging test (Warning)");
	evo::log::error("logging test (Error)");
	evo::log::fatal("logging test (Fatal)");


	auto flags = evo::Flags<FlagsTest>{FlagsTest::A, FlagsTest::C};
	auto static_string = evo::StaticString<5>{"hello"};


	if(tests::static_vector_test() == false){ num_failed += 1; }
	if(tests::c_str_proxy_test() == false){ num_failed += 1; }
	if(tests::bimap_test() == false){ num_failed += 1; }
	if(tests::random_test() == false){ num_failed += 1; }



	if(false){
		evo::unreachable();
	}


	evo::println();


	if(num_failed == 0){
		evo::printlnGreen("All tests passed!");
	}else{
		evo::printlnRed(std::format("Tests failed: {}", num_failed));
	}

	return 0;
};