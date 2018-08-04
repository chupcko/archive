.DEFAULT_GOAL := all
.PHONY: all
all:
	$(MAKE) -C library
	$(MAKE) -C test

.PHONY: debug
debug:
	$(MAKE) -C library debug
	$(MAKE) -C test debug

.PHONY: clean
clean:
	rm -rf out
	$(MAKE) -C library clean
	$(MAKE) -C test clean
