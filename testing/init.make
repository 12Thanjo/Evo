# Alternative GNU Make project makefile autogenerated by Premake

ifndef config
  config=debug
endif

ifndef verbose
  SILENT = @
endif

.PHONY: clean prebuild

ifeq ($(config),debug)
TARGETDIR = bin/Debug
TARGET = $(TARGETDIR)/init
  define BUILDCMDS
	@echo Running build commands
	mkdir -p ./obj/Debug
	mkdir -p ./obj/Release
	mkdir -p ./bin/Debug
	mkdir -p ./bin/Release
  endef
  define CLEANCMDS
	@echo Running clean commands
	rm -rf ./obj/
	rm -rf ./bin/
	@echo "Clean testing will have an error - don't worry, its fine (it seems to be a bug in the genation from premake5)"
	@echo
  endef

else ifeq ($(config),release)
TARGETDIR = bin/Release
TARGET = $(TARGETDIR)/init
  define BUILDCMDS
	@echo Running build commands
	mkdir -p ./obj/Debug
	mkdir -p ./obj/Release
	mkdir -p ./bin/Debug
	mkdir -p ./bin/Release
  endef
  define CLEANCMDS
	@echo Running clean commands
	rm -rf ./obj/
	rm -rf ./bin/
	@echo "Clean testing will have an error - don't worry, its fine (it seems to be a bug in the genation from premake5)"
	@echo
  endef

else
  $(error "invalid configuration $(config)")
endif

$(TARGET):
	$(BUILDCMDS)

clean:
	$(CLEANCMDS)
