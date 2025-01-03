# Alternative GNU Make project makefile autogenerated by Premake

ifndef config
  config=debug_windows
endif

ifndef verbose
  SILENT = @
endif

.PHONY: clean prebuild

ifeq ($(config),debug_windows)
TARGETDIR = bin/Windows/Debug
TARGET = $(TARGETDIR)/lldb
  define BUILDCMDS
	@echo Running build commands
	 lldb "./build/Windows/Debug/bin//testing.exe" 
  endef
  define CLEANCMDS
  endef

else ifeq ($(config),debug_linux)
TARGETDIR = bin/Linux/Debug
TARGET = $(TARGETDIR)/lldb
  define BUILDCMDS
	@echo Running build commands
	 lldb "./build/Linux/Debug/bin//testing.exe" 
  endef
  define CLEANCMDS
  endef

else ifeq ($(config),release_windows)
TARGETDIR = bin/Windows/Release
TARGET = $(TARGETDIR)/lldb
  define BUILDCMDS
	@echo Running build commands
	 lldb "./build/Windows/Release/bin//testing.exe" 
  endef
  define CLEANCMDS
  endef

else ifeq ($(config),release_linux)
TARGETDIR = bin/Linux/Release
TARGET = $(TARGETDIR)/lldb
  define BUILDCMDS
	@echo Running build commands
	 lldb "./build/Linux/Release/bin//testing.exe" 
  endef
  define CLEANCMDS
  endef

else
  $(error "invalid configuration $(config)")
endif

$(TARGET):
	$(BUILDCMDS)

clean:
	$(CLEANCMDS)
