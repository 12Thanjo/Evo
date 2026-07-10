#pragma once

#include "../defines.h"


namespace evo{
	namespace fs{

		[[nodiscard]] auto exists(const std::string& path) noexcept -> bool;

		[[nodiscard]] auto readFile(const std::string& path) noexcept -> Result<std::string>;
		[[nodiscard]] auto readBinaryFile(const std::string& path) noexcept -> Result<std::vector<byte>>;

		[[nodiscard]] auto writeFile(const std::string& path, const std::string& data) noexcept -> bool;
		[[nodiscard]] auto writeBinaryFile(const std::string& path, const std::vector<byte>& data) noexcept -> bool;



		enum class FileMode : ui8 {
			Read,
			Write,

			_max,
		};

		
		class File{
			public:
				[[nodiscard]] File() noexcept = default;
				~File();

				[[nodiscard]] auto open(const std::string& path, Flags<FileMode> mode) noexcept -> bool;
				auto close() noexcept -> void;
				[[nodiscard]] inline auto getHandle() const noexcept -> ::FILE* { return this->handle; };


				[[nodiscard]] auto readLine() const noexcept -> Result<std::string>;

				[[nodiscard]] auto writeLine(const std::string& text) noexcept -> bool;



				[[nodiscard]] auto read() const noexcept -> Result<std::string>; // reads all
				[[nodiscard]] auto read(size_t data_size) const noexcept -> Result<std::string>;


				[[nodiscard]] auto write(const std::string& data) noexcept -> bool;


				[[nodiscard]] auto size() const noexcept -> size_t;

				
				[[nodiscard]] constexpr auto isValid() const noexcept -> bool { return this->valid; };

			protected:
				::FILE* handle = nullptr;
				bool valid = false;
		};



		// TODO: rewrite this to not inherit from File
		class BinaryFile : public File {
			public:
				[[nodiscard]] auto open(const std::string& path, Flags<FileMode> mode) noexcept -> bool;

				[[nodiscard]] auto read() const noexcept -> Result< std::vector<byte> >; // reads all
				[[nodiscard]] auto read(size_t data_size) const noexcept -> Result< std::vector<byte> >;

				[[nodiscard]] auto write(const std::vector<byte>& data) noexcept -> bool;

		};



	};
};
