#pragma once

#include "../defines.h"


namespace evo{
	namespace fs{

		EVO_NODISCARD auto exists(const std::string& path) noexcept -> bool;




		enum class FileMode : ui8 {
			Read,
			Write,

			_max,
		};

		
		class File{
			public:
				EVO_NODISCARD File() noexcept = default;
				~File();

				EVO_NODISCARD auto open(const std::string& path, Flags<FileMode> mode) noexcept -> bool;
				auto close() noexcept -> void;
				EVO_NODISCARD inline auto getHandle() const noexcept -> ::FILE* { return this->handle; };


				EVO_NODISCARD auto readLine() const noexcept -> std::optional<std::string>;

				EVO_NODISCARD auto writeLine(const std::string& text) noexcept -> bool;



				EVO_NODISCARD auto read() const noexcept -> std::optional<std::string>; // reads all
				EVO_NODISCARD auto read(size_t data_size) const noexcept -> std::optional<std::string>;


				EVO_NODISCARD auto write(const std::string& data) noexcept -> bool;


				EVO_NODISCARD auto size() const noexcept -> size_t;

				
				EVO_NODISCARD constexpr auto isValid() const noexcept -> bool { return this->valid; };

			protected:
				::FILE* handle = nullptr;
				bool valid = false;
		};



		// TODO: rewrite this to not inherit from File
		class BinaryFile : public File {
			public:
				EVO_NODISCARD auto open(const std::string& path, Flags<FileMode> mode) noexcept -> bool;

				EVO_NODISCARD auto read() const noexcept -> std::optional< std::vector<byte> >; // reads all
				EVO_NODISCARD auto read(size_t data_size) const noexcept -> std::optional< std::vector<byte> >;

				EVO_NODISCARD auto write(const std::vector<byte>& data) noexcept -> bool;

		};



	};
};
