#pragma once


#include "../defines.h"

#include "./StaticVector.h"

namespace evo{

	constexpr size_t _BimapMaxBucketSize = 4;

	template<
		class LeftT, class RightT,
		class LHash = std::hash<LeftT>, class RHash = std::hash<RightT>,
		class LEqual = std::equal_to<LeftT>, class REqual = std::equal_to<RightT>,
		class DataAllocator = std::allocator<std::pair<LeftT, RightT>>, class BucketAllocator = std::allocator<StaticVector<size_t, _BimapMaxBucketSize>>
	>
	class Bimap{
		public:
			using left_type = LeftT;
			using right_type = RightT;
			using value_type = std::pair<LeftT, RightT>;
			using size_type = std::size_t;
			using difference_type = std::ptrdiff_t;
			using left_hasher = LHash;
			using right_hasher = RHash;
			using left_key_equal = LEqual;
			using right_key_equal = REqual;
			using data_allocator_type = DataAllocator;
			using bucket_allocator_type = BucketAllocator;
			using reference = value_type&;
			using const_reference = const value_type&;
			using pointer = value_type*;
			using const_pointer = const value_type*;
			using iterator = Iterator<value_type>;
			using const_iterator = ConstIterator<value_type>;
			using local_iterator = StaticVector<size_t, _BimapMaxBucketSize>::iterator;
			using const_local_iterator = StaticVector<size_t, _BimapMaxBucketSize>::const_iterator;



			//////////////////////////////////////////////////////////////////////
			// constructors and destructors

			EVO_NODISCARD constexpr Bimap(
				size_t bucket_count = 16,
				const LHash& left_hasher = LHash(), const RHash& right_hasher = RHash(),
				const LEqual& left_equal_to = LEqual(), const REqual& right_equal_to = REqual(),
				const DataAllocator& data_alloc = DataAllocator(),
				const BucketAllocator& left_bucket_alloc = BucketAllocator(), const BucketAllocator& right_bucket_alloc = BucketAllocator()
			) noexcept : 
				data_vec(data_alloc), left_map(left_bucket_alloc), right_map(right_bucket_alloc),
				left_hash(left_hasher), right_hash(right_hasher), left_equal(left_equal_to), right_equal(right_equal_to)
			{
				this->rehash(bucket_count);
			}


			//////////////////////////////////////////////////////////////////////
			// iterators

			EVO_NODISCARD constexpr auto begin()        noexcept ->       iterator { return       iterator(this->data_vec.data()); };
			EVO_NODISCARD constexpr auto begin()  const noexcept -> const_iterator { return const_iterator(this->data_vec.data()); };
			EVO_NODISCARD constexpr auto cbegin() const noexcept -> const_iterator { return const_iterator(this->data_vec.data()); };

			EVO_NODISCARD constexpr auto end()        noexcept ->       iterator { return       iterator(this->data_vec.data() + this->data_vec.size()); };
			EVO_NODISCARD constexpr auto end()  const noexcept -> const_iterator { return const_iterator(this->data_vec.data() + this->data_vec.size()); };
			EVO_NODISCARD constexpr auto cend() const noexcept -> const_iterator { return const_iterator(this->data_vec.data() + this->data_vec.size()); };


			//////////////////////////////////////////////////////////////////////
			// capacity

			EVO_NODISCARD constexpr auto empty() const noexcept -> bool { return this->data_vec.empty(); };
			EVO_NODISCARD constexpr auto size() const noexcept -> size_t { return this->data_vec.size(); };
			EVO_NODISCARD constexpr auto max_size() const noexcept -> size_t { return this->data_vec.max_size(); };
			EVO_NODISCARD constexpr auto capactity() const noexcept -> size_t { return this->data_vec.capactity(); };


			//////////////////////////////////////////////////////////////////////
			// modifiers

			///////////////////////////////////
			// clear

			constexpr auto clear() noexcept -> void {
				this->data_vec.clear();
				this->left_map.clear();
				this->right_map.clear();	
			};


			///////////////////////////////////
			// insert

			constexpr auto insert(const value_type& value) noexcept -> iterator {
				size_t left_bucket_index = this->left_bucket(value.first);
				size_t right_bucket_index = this->right_bucket(value.second);

				while(
					this->size() / this->bucket_count() > 1.0f
					|| this->left_bucket_size(left_bucket_index) == this->max_bucket_size()
					|| this->right_bucket_size(right_bucket_index) == this->max_bucket_size()
				){
					this->rehash(this->bucket_count() * 2);

					left_bucket_index = this->left_bucket(value.first);
					right_bucket_index = this->right_bucket(value.second);
				}


				// check if key exists left
				for(auto i = this->left_begin(left_bucket_index); i != this->left_end(left_bucket_index); ++i){
					if(this->left_equal(value.first, this->data_vec[*i].first)){
						return this->end();
					}
				}

				// check if key exists right
				for(auto i = this->right_begin(right_bucket_index); i != this->right_end(right_bucket_index); ++i){
					if(this->right_equal(value.second, this->data_vec[*i].second)){
						return this->end();
					}
				}


				const size_t insert_index = this->data_vec.size();
				this->data_vec.emplace_back(value);

				this->left_map[left_bucket_index].emplace_back(insert_index);
				this->right_map[right_bucket_index].emplace_back(insert_index);
				

				return iterator(this->data_vec.data() + insert_index);
			};


			constexpr auto insert(value_type&& value) noexcept -> iterator {
				size_t left_bucket_index = this->left_bucket(value.first);
				size_t right_bucket_index = this->right_bucket(value.second);

				while(
					this->size() / this->bucket_count() > 1.0f
					|| this->left_bucket_size(left_bucket_index) == this->max_bucket_size()
					|| this->right_bucket_size(right_bucket_index) == this->max_bucket_size()
				){
					this->rehash(this->bucket_count() * 2);

					left_bucket_index = this->left_bucket(value.first);
					right_bucket_index = this->right_bucket(value.second);
				}


				// check if key exists left
				for(auto i = this->left_begin(left_bucket_index); i != this->left_end(left_bucket_index); ++i){
					if(this->left_equal(value.first, this->data_vec[*i].first)){
						return this->end();
					}
				}

				// check if key exists right
				for(auto i = this->right_begin(right_bucket_index); i != this->right_end(right_bucket_index); ++i){
					if(this->right_equal(value.second, this->data_vec[*i].second)){
						return this->end();
					}
				}


				const size_t insert_index = this->data_vec.size();
				this->data_vec.emplace_back(std::move(value));

				this->left_map[left_bucket_index].emplace_back(insert_index);
				this->right_map[right_bucket_index].emplace_back(insert_index);
				

				return iterator(this->data_vec.data() + insert_index);
			};


			///////////////////////////////////
			// insert_range

			///////////////////////////////////
			// insert_or_assign

			///////////////////////////////////
			// emplace

			template<class... Args>
			constexpr auto emplace(Args&&... args) noexcept -> iterator {
				return this->insert(value_type(std::forward<Args>(args)...));
			};


			///////////////////////////////////
			// emplace_hint

			///////////////////////////////////
			// try_emplace

			///////////////////////////////////
			// erase

			constexpr auto erase_left(const LeftT& left) noexcept -> size_t {
				iterator iter = this->find_left(left);
				if(iter == this->end()){ return 0; }

				const size_t index = &*iter - this->data_vec.data();

				// remove from left map
				const size_t left_bucket_index = this->left_bucket(left);
				for(auto i = this->left_begin(left_bucket_index); i != this->left_end(left_bucket_index); ++i){
					if(*i == index){
						this->left_map[left_bucket_index].erase(i);
						break;
					}
				}

				// remove from right map
				const size_t right_bucket_index = this->right_bucket(iter->second);
				for(auto i = this->right_begin(right_bucket_index); i != this->right_end(right_bucket_index); ++i){
					if(*i == index){
						this->right_map[right_bucket_index].erase(i);
						break;
					}
				}

				// remove from data
				using DataVecIterator = std::vector<value_type, DataAllocator>::iterator;
				this->data_vec.erase(DataVecIterator(this->data_vec.begin() + index));

				this->rehash(this->bucket_count());
				return 1;
			};


			constexpr auto erase_right(const RightT& right) noexcept -> size_t {
				iterator iter = this->find_right(right);
				if(iter == this->end()){ return 0; }

				const size_t index = &*iter - this->data_vec.data();

				// remove from right map
				const size_t right_bucket_index = this->right_bucket(right);
				for(auto i = this->right_begin(right_bucket_index); i != this->right_end(right_bucket_index); ++i){
					if(*i == index){
						this->right_map[right_bucket_index].erase(i);
						break;
					}
				}

				// remove from left map
				const size_t left_bucket_index = this->left_bucket(iter->first);
				for(auto i = this->left_begin(left_bucket_index); i != this->left_end(left_bucket_index); ++i){
					if(*i == index){
						this->left_map[left_bucket_index].erase(i);
						break;
					}
				}

				// remove from data
				using DataVecIterator = std::vector<value_type, DataAllocator>::iterator;
				this->data_vec.erase(DataVecIterator(this->data_vec.begin() + index));

				this->rehash(this->bucket_count());
				return 1;
			};



			//////////////////////////////////////////////////////////////////////
			// lookup

			///////////////////////////////////
			// at

			EVO_NODISCARD constexpr auto at_left(const LeftT& left) noexcept -> value_type& {
				const size_t bucket_index = this->left_bucket(left);

				for(auto i = this->left_begin(bucket_index); i != this->left_end(bucket_index); ++i){
					value_type& pair = this->data_vec[*i];

					if(this->left_equal(left, pair.first)){
						return pair;
					}
				}

				// attempted to get value that doesn't exist
				breakpoint();
				unreachable();
			};

			EVO_NODISCARD constexpr auto at_left(const LeftT& left) const noexcept -> const value_type& {
				const size_t bucket_index = this->left_bucket(left);

				for(auto i = this->left_begin(bucket_index); i != this->left_end(bucket_index); ++i){
					const value_type& pair = this->data_vec[*i];

					if(this->left_equal(left, pair.first)){
						return pair;
					}
				}

				// attempted to get value that doesn't exist
				breakpoint();
				unreachable();
			};



			EVO_NODISCARD constexpr auto at_right(const RightT& right) noexcept -> value_type& {
				const size_t bucket_index = this->right_bucket(right);

				for(auto i = this->right_begin(bucket_index); i != this->right_end(bucket_index); ++i){
					value_type& pair = this->data_vec[*i];

					if(this->right_equal(right, pair.second)){
						return pair;
					}
				}

				// attempted to get value that doesn't exist
				breakpoint();
				unreachable();
			};

			EVO_NODISCARD constexpr auto at_right(const RightT& right) const noexcept -> const value_type& {
				const size_t bucket_index = this->right_bucket(right);

				for(auto i = this->right_begin(bucket_index); i != this->right_end(bucket_index); ++i){
					const value_type& pair = this->data_vec[*i];

					if(this->right_equal(right, pair.second)){
						return pair;
					}
				}

				// attempted to get value that doesn't exist
				breakpoint();
				unreachable();
			};


			///////////////////////////////////
			// get

			EVO_NODISCARD constexpr auto get_left(const RightT& right) const noexcept -> const LeftT& { return this->at_right(right).first; };
			EVO_NODISCARD constexpr auto get_left(const RightT& right) noexcept -> LeftT& { return this->at_right(right).first; };

			EVO_NODISCARD constexpr auto get_right(const LeftT& left) const noexcept -> const RightT& { return this->at_left(left).second; };
			EVO_NODISCARD constexpr auto get_right(const LeftT& left) noexcept -> RightT& { return this->at_left(left).second; };



			///////////////////////////////////
			// count


			///////////////////////////////////
			// find

			EVO_NODISCARD constexpr auto find_left(const LeftT& left) noexcept -> iterator {
				const size_t bucket_index = this->left_bucket(left);

				for(auto i = this->left_begin(bucket_index); i != this->left_end(bucket_index); ++i){
					value_type& pair = this->data_vec[*i];

					if(this->left_equal(left, pair.first)){
						return iterator(&this->data_vec[*i]);
					}
				}

				return this->end();
			};

			EVO_NODISCARD constexpr auto find_left(const LeftT& left) const noexcept -> const_iterator {
				const size_t bucket_index = this->left_bucket(left);

				for(auto i = this->left_begin(bucket_index); i != this->left_end(bucket_index); ++i){
					const value_type& pair = this->data_vec[*i];

					if(this->left_equal(left, pair.first)){
						return iterator(&this->data_vec[*i]);
					}
				}

				return this->end();
			};



			EVO_NODISCARD constexpr auto find_right(const RightT& right) noexcept -> iterator {
				const size_t bucket_index = this->right_bucket(right);

				for(auto i = this->right_begin(bucket_index); i != this->right_end(bucket_index); ++i){
					value_type& pair = this->data_vec[*i];

					if(this->right_equal(right, pair.second)){
						return iterator(&this->data_vec[*i]);
					}
				}

				return this->end();
			};

			EVO_NODISCARD constexpr auto find_right(const RightT& right) const noexcept -> const_iterator {
				const size_t bucket_index = this->right_bucket(right);

				for(auto i = this->right_begin(bucket_index); i != this->right_end(bucket_index); ++i){
					const value_type& pair = this->data_vec[*i];

					if(this->right_equal(right, pair.second)){
						return iterator(&this->data_vec[*i]);
					}
				}

				return this->end();
			};



			///////////////////////////////////
			// contains

			EVO_NODISCARD constexpr auto contains_left(const LeftT& left) const noexcept -> bool {
				const size_t bucket_index = this->left_bucket(left);

				for(auto i = this->left_begin(bucket_index); i != this->left_end(bucket_index); ++i){
					const value_type& pair = this->data_vec[*i];

					if(this->left_equal(left, pair.first)){
						return true;
					}
				}

				return false;
			};


			EVO_NODISCARD constexpr auto contains_right(const RightT& right) const noexcept -> bool {
				const size_t bucket_index = this->right_bucket(right);

				for(auto i = this->right_begin(bucket_index); i != this->right_end(bucket_index); ++i){
					const value_type& pair = this->data_vec[*i];

					if(this->right_equal(right, pair.second)){
						return true;
					}
				}

				return false;
			};




			//////////////////////////////////////////////////////////////////////
			// bucket interface


			///////////////////////////////////
			// bucket begin

			EVO_NODISCARD constexpr auto  left_begin(size_t n)       noexcept ->       local_iterator { return this->left_map[n].begin();  };
			EVO_NODISCARD constexpr auto  left_begin(size_t n) const noexcept -> const_local_iterator { return this->left_map[n].begin();  };
			EVO_NODISCARD constexpr auto left_cbegin(size_t n) const noexcept -> const_local_iterator { return this->left_map[n].cbegin(); };

			EVO_NODISCARD constexpr auto  right_begin(size_t n)       noexcept ->       local_iterator { return this->right_map[n].begin();  };
			EVO_NODISCARD constexpr auto  right_begin(size_t n) const noexcept -> const_local_iterator { return this->right_map[n].begin();  };
			EVO_NODISCARD constexpr auto right_cbegin(size_t n) const noexcept -> const_local_iterator { return this->right_map[n].cbegin(); };


			///////////////////////////////////
			// bucket end

			EVO_NODISCARD constexpr auto  left_end(size_t n)       noexcept ->       local_iterator { return this->left_map[n].end();  };
			EVO_NODISCARD constexpr auto  left_end(size_t n) const noexcept -> const_local_iterator { return this->left_map[n].end();  };
			EVO_NODISCARD constexpr auto left_cend(size_t n) const noexcept -> const_local_iterator { return this->left_map[n].cend(); };

			EVO_NODISCARD constexpr auto  right_end(size_t n)       noexcept ->       local_iterator { return this->right_map[n].end();  };
			EVO_NODISCARD constexpr auto  right_end(size_t n) const noexcept -> const_local_iterator { return this->right_map[n].end();  };
			EVO_NODISCARD constexpr auto right_cend(size_t n) const noexcept -> const_local_iterator { return this->right_map[n].cend(); };


			///////////////////////////////////
			// bucket_count

			EVO_NODISCARD constexpr auto bucket_count() const noexcept -> size_t {
				return this->left_map.size();
			};

			///////////////////////////////////
			// max_bucket_count

			EVO_NODISCARD constexpr auto max_bucket_count() const noexcept -> size_t {
				return this->left_map.max_size();
			};


			///////////////////////////////////
			// bucket_size

			EVO_NODISCARD constexpr auto left_bucket_size(size_t n) const noexcept -> size_t {
				return this->left_map[n].size();
			};

			EVO_NODISCARD constexpr auto right_bucket_size(size_t n) const noexcept -> size_t {
				return this->right_map[n].size();
			};

			///////////////////////////////////
			// bucket

			EVO_NODISCARD constexpr auto left_bucket(const LeftT& left) const noexcept -> size_t {
				return this->left_hash(left) % this->bucket_count();
			};

			EVO_NODISCARD constexpr auto right_bucket(const RightT& right) const noexcept -> size_t {
				return this->right_hash(right) % this->bucket_count();
			};




			//////////////////////////////////////////////////////////////////////
			// hash policy

			EVO_NODISCARD constexpr static auto max_bucket_size() noexcept -> size_t {
				return _BimapMaxBucketSize;
			};


			constexpr auto rehash(size_t count) noexcept -> void {
				this->left_map.clear();
				this->left_map.resize(count);

				this->right_map.clear();
				this->right_map.resize(count);

				for(size_t i = 0; i < this->data_vec.size(); i+=1){
					const value_type& pair = this->data_vec[i];

					this->left_map[this->left_bucket(pair.first)].emplace_back(i);
					this->right_map[this->right_bucket(pair.second)].emplace_back(i);
				}


				this->data_vec.reserve(count * Bimap::max_bucket_size());
			};


			constexpr auto reserve(size_t count) noexcept -> void {
				this->rehash(count / Bimap::max_bucket_size());
			};



			//////////////////////////////////////////////////////////////////////
			// observers




		private:
			std::vector<value_type, DataAllocator> data_vec;

			std::vector<StaticVector<size_t, _BimapMaxBucketSize>, BucketAllocator> left_map;
			std::vector<StaticVector<size_t, _BimapMaxBucketSize>, BucketAllocator> right_map;


			LHash left_hash;
			RHash right_hash;

			LEqual left_equal;
			REqual right_equal;
	};


};