# Alternative GNU Make workspace makefile autogenerated by Premake

ifndef config
  config=release
endif

ifndef verbose
  SILENT = @
endif

ifeq ($(config),release)
  lima_config = release

else ifeq ($(config),debug)
  lima_config = debug

else
  $(error "invalid configuration $(config)")
endif

PROJECTS := lima

.PHONY: all clean help $(PROJECTS) 

all: $(PROJECTS)

lima:
ifneq (,$(lima_config))
	@echo "==== Building lima ($(lima_config)) ===="
	@${MAKE} --no-print-directory -C . -f lima.make config=$(lima_config)
endif

clean:
	@${MAKE} --no-print-directory -C . -f lima.make clean

help:
	@echo "Usage: make [config=name] [target]"
	@echo ""
	@echo "CONFIGURATIONS:"
	@echo "  release"
	@echo "  debug"
	@echo ""
	@echo "TARGETS:"
	@echo "   all (default)"
	@echo "   clean"
	@echo "   lima"
	@echo ""
	@echo "For more information, see https://github.com/premake/premake-core/wiki"