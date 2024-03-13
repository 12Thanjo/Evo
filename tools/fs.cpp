#include "Evo.h"
#include "fs.h"


#include <stdio.h>
#include <sys/stat.h>




namespace evo{
	namespace fs{


		auto exists(const std::string& path) noexcept -> bool {
			#if defined(EVO_PLATFORM_WINDOWS)
				struct _stat buffer;
				return _stat(path.c_str(), &buffer) == 0;
				
			#else
				struct stat buffer;
				return stat(path.c_str(), &buffer) == 0;
			#endif
		};


		//////////////////////////////////////////////////////////////////////
		// File

		
		File::~File(){
			#if defined(EVO_CONFIG_DEBUG)

				if(this->valid){
					logWarning("Didn't explicitly call evo::fs::File::close() - was done automatically (only because in debug build)");

					this->close();
				}

			#endif
		}



		auto File::open(const std::string& path, Flags<FileMode> mode) noexcept -> bool {
			EVO_DEBUG_ASSERT(this->valid == false);

			// if reading to the file, it must exist
			EVO_DEBUG_ASSERT((mode.has(FileMode::Read) == false) || fs::exists(path));
			


			const char* mode_str;

			bool read_mode = mode.has(FileMode::Read);
			bool write_mode = mode.has(FileMode::Write);

			     if(read_mode && write_mode){ mode_str = "w+"; }
			else if(read_mode              ){ mode_str = "r";  }
			else if(             write_mode){ mode_str = "w";  }
			else{
				EVO_DEBUG_ASSERT(false); // invalid file mode
				return false;
			}


			FILE* file;
			errno_t err = ::fopen_s(&file, path.c_str(), mode_str);
			if(err != 0){
				EVO_DEBUG_ASSERT(false); //error opening file
				return false;
			}

			this->handle = file;
			this->valid = true;

			return true;
		};


		auto File::close() noexcept -> void {
			EVO_DEBUG_ASSERT(this->valid);

			fclose(this->handle);

			this->handle = nullptr;
			this->valid = false;
		};


		auto File::readLine() const noexcept -> std::optional<std::string> {
			EVO_DEBUG_ASSERT(this->valid);

			auto buffer = std::string{};
			buffer.resize(32000);

			if(std::fgets(buffer.data(), 32000, this->handle) != 0){
				size_t length = ::strlen(buffer.data());
				buffer.resize(length);

				return buffer;
			}

			return std::nullopt;
		};

		auto File::writeLine(const std::string& text) noexcept -> bool {
			EVO_DEBUG_ASSERT(this->valid);

			i32 result = std::fputs(text.c_str(), this->handle);
			if(result != EOF){
				result = std::fputc('\n', this->handle);
			}

			std::fflush(this->handle);
			return result != EOF;
		};


		// TODO: simplify this by calling `read(this->size)`
		auto File::read() const noexcept -> std::optional<std::string> {
			EVO_DEBUG_ASSERT(this->valid);

			size_t size = this->size();

			auto output = std::string{};
			output.resize(size);

			size_t bytes_read = std::fread(output.data(), sizeof(char), size, this->handle);
			if(bytes_read == 0 && std::ferror(this->handle) != 0){
				return std::nullopt;
			}

			output.resize(bytes_read);

			return output;
		};

		auto File::read(size_t data_size) const noexcept -> std::optional<std::string> {
			EVO_DEBUG_ASSERT(this->valid);

			auto output = std::string{};
			output.resize(data_size);

			size_t bytes_read = std::fread(output.data(), sizeof(char), data_size, this->handle);
			if(bytes_read == 0 && std::ferror(this->handle) != 0){
				return std::nullopt;
			}

			output.resize(bytes_read);

			return output;
		};


		auto File::write(const std::string& data) noexcept -> bool {
			EVO_DEBUG_ASSERT(this->valid);

			auto bytes_written = std::fwrite(data.data(), sizeof(char), data.size(), this->handle);
			if(bytes_written != data.size()){
				return false;
			}

			std::fflush(this->handle);
			return true;
		};


		auto File::size() const noexcept -> size_t {
			EVO_DEBUG_ASSERT(this->valid);

			std::fseek(this->handle, 0, SEEK_END);
			size_t size = std::ftell(this->handle);
			std::rewind(this->handle);

			return size;
		};


		//////////////////////////////////////////////////////////////////////
		// binary file


		auto BinaryFile::open(const std::string& path, Flags<FileMode> mode) noexcept -> bool {
			EVO_DEBUG_ASSERT(this->valid == false);

			// if reading to the file, it must exist
			EVO_DEBUG_ASSERT((mode.has(FileMode::Read) == false) || fs::exists(path));


			const char* mode_str;

			bool read_mode = mode.has(FileMode::Read);
			bool write_mode = mode.has(FileMode::Write);

			     if(read_mode && write_mode){ mode_str = "w+b"; }
			else if(read_mode              ){ mode_str = "rb";  }
			else if(             write_mode){ mode_str = "wb";  }
			else{
				EVO_DEBUG_ASSERT(false); // invalid file mode
				return false;
			}


			FILE* file;
			errno_t err = ::fopen_s(&file, path.c_str(), mode_str);
			if(err != 0){
				EVO_DEBUG_ASSERT(false); //error opening file
				return false;
			}

			this->handle = file;
			this->valid = true;

			return true;
		};



		auto BinaryFile::read() const noexcept -> std::optional< std::vector<byte> > {
			EVO_DEBUG_ASSERT(this->valid);

			// file size
			std::fseek(this->handle, 0, SEEK_END);
			size_t size = std::ftell(this->handle);
			std::rewind(this->handle);

			auto output = std::vector<byte>{};
			output.resize(size);

			size_t bytes_read = std::fread(output.data(), sizeof(evo::byte), size, this->handle);
			if(bytes_read == 0 && std::ferror(this->handle) != 0){
				return std::nullopt;
			}

			output.resize(bytes_read);


			return output;
		};

		auto BinaryFile::read(size_t data_size) const noexcept -> std::optional< std::vector<byte> > {
			EVO_DEBUG_ASSERT(this->valid);

			auto output = std::vector<byte>{};
			output.resize(data_size);

			size_t bytes_read = std::fread(output.data(), sizeof(evo::byte), data_size, this->handle);
			if(bytes_read == 0 && std::ferror(this->handle) != 0){
				return std::nullopt;
			}

			output.resize(bytes_read);

			return output;
		};


		auto BinaryFile::write(const std::vector<byte>& data) noexcept -> bool {
			EVO_DEBUG_ASSERT(this->valid);

			auto bytes_written = std::fwrite(data.data(), sizeof(evo::byte), data.size(), this->handle);
			if(bytes_written != data.size()){
				return false;
			}

			std::fflush(this->handle);
			return true;
		};



	};
};