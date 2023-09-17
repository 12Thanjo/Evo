#pragma once


namespace evo{


	template<typename T>
	constexpr auto bit_flag(T flag) noexcept -> T {
		return static_cast<T>(1) << flag;
	};


	template<typename T, typename UnderlyingT>
	constexpr auto create_flag_mask(std::initializer_list<T> list) noexcept -> UnderlyingT {
		UnderlyingT flags = 0;
		for(auto flag : list){
			flags |= bit_flag( static_cast<UnderlyingT>(flag) );
		}
		return flags;
	};


	/*
		Example corret enum for use in Flags:
			
		enum class Colors : ui8 {
			Red,
			Orange,
			Yellow,
			Green,
			Blue,
			Purple,

			_max,
		};


		Notes;
			do not have a "None",
			must end with "_max"
			
	*/



	template<typename Enum, typename UnderlyingT = ui8>
	class Flags{
		static_assert(
			((sizeof(UnderlyingT) * 8) - 1) >= static_cast<UnderlyingT>(Enum::_max),
			"Flags must have a larger underlying type"
		);

		public:
			//////////////////////////////////////////////////////////////////////
			// constructors / destructors

			constexpr Flags() noexcept
				: internal_data(0) {};
			
			constexpr Flags(Enum flag) noexcept
				: internal_data( bit_flag(static_cast<UnderlyingT>(flag)) ) {};

			constexpr Flags(std::initializer_list<Enum> flags) noexcept
				: internal_data( create_flag_mask<Enum, UnderlyingT>(flags) ) {};
				

			constexpr ~Flags() noexcept = default;

			//////////////////////////////////////////////////////////////////////
			// modifiers

			// set
			constexpr auto set(Enum flag_value) noexcept -> void {
				EVO_DEBUG_ASSERT( static_cast<UnderlyingT>(Enum::_max) > static_cast<UnderlyingT>(flag_value) );

				this->internal_data |= bit_flag( static_cast<UnderlyingT>(flag_value) );
			};

			constexpr auto set(std::initializer_list<Enum> flag_values) noexcept -> void {
				this->internal_data |= create_flag_mask<Enum, UnderlyingT>(flag_values);
			};


			// unset
			constexpr auto unset(Enum flag_value) noexcept -> void {
				EVO_DEBUG_ASSERT( static_cast<UnderlyingT>(Enum::_max) > static_cast<UnderlyingT>(flag_value) );

				this->internal_data &= ~( bit_flag(static_cast<UnderlyingT>(flag_value)) );
			};

			constexpr auto unset(std::initializer_list<Enum> flag_values) noexcept -> void {
				this->internal_data &= ~create_flag_mask<Enum, UnderlyingT>(flag_values);
			};

			// resets to all false (0)
			constexpr auto clear() noexcept -> void {
				this->internal_data = 0;
			};			



			// toggle
			constexpr auto toggle(Enum flag_value) noexcept -> void {
				EVO_DEBUG_ASSERT( static_cast<UnderlyingT>(Enum::_max) > static_cast<UnderlyingT>(flag_value) );

				this->internal_data ^= bit_flag( static_cast<UnderlyingT>(flag_value) );
			};

			constexpr auto toggle(std::initializer_list<Enum> flag_values) noexcept -> void {
				this->internal_data ^= create_flag_mask<Enum, UnderlyingT>(flag_values);
			};






			//////////////////////////////////////////////////////////////////////
			// lookup


			
			EVO_NODISCARD constexpr auto has(Enum flag_value) const noexcept -> bool {
				EVO_DEBUG_ASSERT( static_cast<UnderlyingT>(Enum::_max) > static_cast<UnderlyingT>(flag_value) );

				return (this->internal_data & bit_flag(static_cast<UnderlyingT>(flag_value))) != 0;
			};

			
			EVO_NODISCARD constexpr auto has(std::initializer_list<Enum> flag_values) const noexcept -> bool {

				auto mask = create_flag_mask<Enum, UnderlyingT>(flag_values);
				return this->has(static_cast<Enum>(mask));
			};

			
			EVO_NODISCARD constexpr auto hasNone() const noexcept -> bool {
				return this->internal_data == 0;
			};



			//////////////////////////////////////////////////////////////////////
			// operators

			
			EVO_NODISCARD constexpr auto operator | (Enum flag_value) const noexcept -> Flags<Enum> {
				EVO_DEBUG_ASSERT( static_cast<UnderlyingT>(Enum::_max) > static_cast<UnderlyingT>(flag_value) );

				auto output = Flags<Enum>{};
				output.internal_data = this->internal_data | bit_flag(static_cast<UnderlyingT>(flag_value));
				return output;
			}

			
			EVO_NODISCARD constexpr auto operator & (Enum flag_value) const noexcept -> Flags<Enum> {
				EVO_DEBUG_ASSERT( static_cast<UnderlyingT>(Enum::_max) > static_cast<UnderlyingT>(flag_value) );

				auto output = Flags<Enum>{};
				output.internal_data = this->internal_data & bit_flag(static_cast<UnderlyingT>(flag_value));
				return output;
			}


			
			constexpr auto operator |= (Enum flag_value) noexcept -> void {
				EVO_DEBUG_ASSERT( static_cast<UnderlyingT>(Enum::_max) > static_cast<UnderlyingT>(flag_value) );

				// this->internal_data |= static_cast<UnderlyingT>(flag_value);
				this->set(flag_value);
			}

			
			constexpr auto operator &= (Enum flag_value) noexcept -> void {
				EVO_DEBUG_ASSERT( static_cast<UnderlyingT>(Enum::_max) > static_cast<UnderlyingT>(flag_value) );

				this->internal_data &= bit_flag(static_cast<UnderlyingT>(flag_value));
			}


			//////////////////////////////////////////////////////////////////////
			// underlying

			using underlying_t = UnderlyingT;

			
			EVO_NODISCARD constexpr auto value() const noexcept -> UnderlyingT {
				return this->internal_data;
			};

		private:
			UnderlyingT internal_data;
	};





};