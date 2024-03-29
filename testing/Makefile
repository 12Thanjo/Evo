# Alternative GNU Make workspace makefile autogenerated by Premake

ifndef config
  config=debug
endif

ifndef verbose
  SILENT = @
endif

ifeq ($(config),debug)
  init_config = debug
  testing_config = debug
  run_config = debug
  test_config = debug
  gdb_config = debug

else ifeq ($(config),release)
  init_config = release
  testing_config = release
  run_config = release
  test_config = release
  gdb_config = release

else
  $(error "invalid configuration $(config)")
endif

PROJECTS := init testing run test gdb

.PHONY: all clean help $(PROJECTS) 

all: $(PROJECTS)

init:
ifneq (,$(init_config))
	@echo "==== Building init ($(init_config)) ===="
	@${MAKE} --no-print-directory -C . -f init.make config=$(init_config)
endif

testing:
ifneq (,$(testing_config))
	@echo "==== Building testing ($(testing_config)) ===="
	@${MAKE} --no-print-directory -C . -f testing.make config=$(testing_config)
endif

run:
ifneq (,$(run_config))
	@echo "==== Building run ($(run_config)) ===="
	@${MAKE} --no-print-directory -C . -f run.make config=$(run_config)
endif

test: init testing run
ifneq (,$(test_config))
	@echo "==== Building test ($(test_config)) ===="
	@${MAKE} --no-print-directory -C . -f test.make config=$(test_config)
endif

gdb: init testing
ifneq (,$(gdb_config))
	@echo "==== Building gdb ($(gdb_config)) ===="
	@${MAKE} --no-print-directory -C . -f gdb.make config=$(gdb_config)
endif

clean:
	@${MAKE} --no-print-directory -C . -f init.make clean
	@${MAKE} --no-print-directory -C . -f testing.make clean
	@${MAKE} --no-print-directory -C . -f run.make clean
	@${MAKE} --no-print-directory -C . -f test.make clean
	@${MAKE} --no-print-directory -C . -f gdb.make clean

help:
	@echo "Usage: make [config=name] [target]"
	@echo ""
	@echo "CONFIGURATIONS:"
	@echo "  debug"
	@echo "  release"
	@echo ""
	@echo "TARGETS:"
	@echo "   all (default)"
	@echo "   clean"
	@echo "   init"
	@echo "   testing"
	@echo "   run"
	@echo "   test"
	@echo "   gdb"
	@echo ""
	@echo "For more information, see https://github.com/premake/premake-core/wiki"