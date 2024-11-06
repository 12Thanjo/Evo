
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

			constexpr TestingType(const TestingType& rhs) noexcept : initialized(true), is_copy(true) {};

			constexpr TestingType& operator=(const TestingType& rhs) {
				this->is_copy = true;
				return *this;
			};


			///////////////////////////////////
			// move

			constexpr TestingType(TestingType&& rhs) noexcept : initialized(true) { this->operator=(std::move(rhs)); };

			constexpr TestingType& operator=(TestingType&& rhs) {
				rhs.initialized = false;
				rhs.moved_from = true;
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



	static size_t num_verbose_created = 0;
	auto get_verbose_index() -> size_t {
		EVO_DEFER([&](){num_verbose_created += 1;});
		return num_verbose_created;
	}

	class Verbose{
		public:
			//////////////////////////////////////////////////////////////////////
			// special member functions

			EVO_NODISCARD Verbose() : generation(get_verbose_index()), life(0) {
				evo::println("Verbose() => {}", this->print());
			}
			~Verbose(){ evo::println("~Verbose() => {}", this->print()); }

			EVO_NODISCARD Verbose(const Verbose& rhs) : generation(rhs.generation), life(rhs.life + 1) {
				evo::println("Verbose(const Verbose& {}) => {}", rhs.print(), this->print());
			}

			auto operator=(const Verbose& rhs){
				evo::println("operator=(const Verbose& {}) => {} => {{{}.{}}}",  rhs.print(), this->print(), rhs.generation, rhs.life + 1);

				this->generation = rhs.generation;
				this->life = rhs.life + 1;
			}

			EVO_NODISCARD Verbose(Verbose&& rhs) : generation(rhs.generation), life(rhs.life + 1) {
				evo::println("Verbose(Verbose&& {}) => {}", rhs.print(), this->print());
			}


			EVO_NODISCARD auto getGeneration() const -> size_t { return this->generation; }
			EVO_NODISCARD auto getLife() const -> size_t { return this->life; }

			EVO_NODISCARD auto print() const -> std::string {
				return std::format("{{{}.{}}}", this->generation, this->life);
			}

		private:
			size_t generation;
			size_t life;
	};

}


template<>
struct std::formatter<tests::Verbose> : std::formatter<std::string> {
    auto format(const tests::Verbose& verbose, std::format_context& ctx) const -> std::format_context::iterator {
        return std::formatter<std::string>::format(verbose.print(), ctx);
    };
};


namespace tests{
	
	EVO_NODISCARD auto static_vector_test() noexcept -> bool {
		auto static_vector = evo::StaticVector<int, 6>{};

		static_vector.insert(static_vector.cbegin(), 2);
		static_vector.insert(std::next(static_vector.begin()), 3);
		static_vector.emplace(static_vector.cbegin(), 1);

		const auto static_vector_copy = evo::StaticVector<int, 3>(static_vector.begin(), static_vector.end());

		if(static_vector[0] != 1 || static_vector.at(1) != 2 || static_vector[2] != 3){
			evo::printlnRed("evo::StaticVector::insert / evo::StaticVector::emplace test failed");
			return false;
		}


		static_vector = std::initializer_list<int>{0, 1, 2, 3};

		for(int i = 0; int elem : static_vector){
			if(elem != i){
				evo::printlnRed("evo::StaticVector::operator=(std::initializer_list) test failed");
				return false;
			}
		
			i += 1;
		}

		{
			int counter = 3;
			for(auto i = static_vector.rbegin(); i != static_vector.rend(); ++i){
				if(*i != counter){
					evo::printlnRed("evo::StaticVector reverse iteration test failed");
					return false;
				}
				counter -= 1;
			}

			if(counter != -1){
				evo::printlnRed("evo::StaticVector reverse iteration test failed (didn't go far enough)");
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




	EVO_NODISCARD auto random_test() noexcept -> bool {

		for(uint64_t i = 0; i < 1000; i+=1){
			const uint64_t random_num = evo::random(10, 15);

			if(random_num > 15 || random_num < 10){
				return false;
			}
		}


		evo::printlnGreen("Random tests passed");
		return true;
	};



	EVO_NODISCARD auto small_vector_test() noexcept -> bool {
		auto small_vec = evo::SmallVector<int, 8>{1, 2, 3};
		auto small_vec2 = evo::SmallVector<int, 8>{4, 5, 6};

		small_vec = small_vec2;
		small_vec = std::move(small_vec2);

		const auto small_vec_copy = evo::SmallVector<int, 3>(small_vec.begin(), small_vec.end());


		if(small_vec[0] != 4 || small_vec[1] != 5 || small_vec[2] != 6){
			evo::printlnRed("SmallVector test 1 failed");
			return false;
		}

		small_vec.clear();

		for(size_t i = 0; i < 12; i+=1){
			small_vec.emplace_back(i);

			for(size_t j = 0; j < i; j+=1){
				if(small_vec[j] != int(j)){
					evo::printlnRed("SmallVector test 2 failed");
					return false;
				}
			}
		}


		evo::printlnGreen("SmallVector tests passed");
		return true;
	};


	EVO_NODISCARD auto variant_test() noexcept -> bool {
		auto variant = evo::Variant<int, double, std::array<evo::byte, 11>>();

		variant.emplace<double>(12.4);

		if(variant.is<double>() == false){
			evo::printlnRed("Variant test 1 failed");
			return false;
		}

		if(variant.as<double>() != 12.4){
			evo::printlnRed("Variant test 2 failed");
			return false;	
		}

		evo::printlnGreen("Variant tests passed");
		return true;
	};

	EVO_NODISCARD auto defer_test() noexcept -> bool {
		int value = 1;

		{
			EVO_DEFER([&]() noexcept -> void {
				value += 1;
			});

			EVO_DEFER([&]() noexcept -> void {
				value *= 2;
			});

			value += 3;
		}


		if(value != 9){
			evo::printlnRed("Defer tests failed");
		}

		evo::printlnGreen("Defer tests passed");
		return true;
	};


	EVO_NODISCARD auto unmovable_vector_test() noexcept -> bool {
		///////////////////////////////////
		// small

		static constexpr size_t SMALL_SIZE = 4;
		auto small_vec = evo::UnmovableVector<uint16_t>(SMALL_SIZE);
		if(small_vec.capacity() != SMALL_SIZE || small_vec.size() != 0){
			evo::printlnRed("UnmovableVector test 1 failed");
			return false;
		}

		for(size_t i = 0; i < SMALL_SIZE; i+=1){
			small_vec.emplace_back(i);
		}

		if(small_vec.capacity() != SMALL_SIZE || small_vec.size() != SMALL_SIZE){
			evo::printlnRed("UnmovableVector test 2 failed");
			return false;
		}

		for(size_t i = 0; const uint16_t& num : small_vec){
			if(num != i){
				evo::printlnRed("UnmovableVector test 3 failed");
				return false;	
			}

			i += 1;
		}


		///////////////////////////////////
		// big

		static constexpr size_t BIG_SIZE = 20;
		auto big_vec = evo::UnmovableVector<uint32_t, false>(BIG_SIZE);

		if(big_vec.capacity() != BIG_SIZE || big_vec.size() != 0){
			evo::printlnRed("UnmovableVector test 4 failed");
			return false;
		}

		for(size_t i = 0; i < BIG_SIZE; i+=1){
			big_vec.emplace_back(i);
		}

		if(big_vec.capacity() != BIG_SIZE || big_vec.size() != BIG_SIZE){
			evo::printlnRed("UnmovableVector test 5 failed");
			return false;
		}

		for(size_t i = 0; const uint32_t& num : big_vec){
			if(num != i){
				evo::printlnRed("UnmovableVector test 6 failed");
				return false;	
			}

			i += 1;
		}


		///////////////////////////////////
		// done

		evo::printlnGreen("UnmovableVector tests passed");
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

	// evo::log::trace("logging test (Trace)");
	// evo::log::debug("logging test (Debug)");
	// evo::log::success("logging test (Success)");
	// evo::log::info("logging test (Info)");
	// evo::log::warning("logging test (Warning)");
	// evo::log::error("logging test (Error)");
	// evo::log::fatal("logging test (Fatal)");


	[[maybe_unused]] auto flags = evo::Flags<FlagsTest>{FlagsTest::A, FlagsTest::C};
	[[maybe_unused]] auto static_string = evo::StaticString<5>{"hello"};


	if(tests::static_vector_test() == false){ num_failed += 1; }
	if(tests::c_str_proxy_test() == false){ num_failed += 1; }
	if(tests::bimap_test() == false){ num_failed += 1; }
	if(tests::random_test() == false){ num_failed += 1; }
	if(tests::small_vector_test() == false){ num_failed += 1; }
	if(tests::variant_test() == false){ num_failed += 1; }
	if(tests::defer_test() == false){ num_failed += 1; }
	if(tests::unmovable_vector_test() == false){ num_failed += 1; }


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