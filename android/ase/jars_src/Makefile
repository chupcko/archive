DIRS_FOUND := $(sort $(dir $(wildcard */Makefile)))
DIRS := $(DIRS_FOUND:/=)

.DEFAULT_GOAL := all
.PHONY: all
all: MY_GOAL := all
all: jars $(DIRS)

jars:
	mkdir $@

.PHONY: clean
clean: MY_GOAL := clean
clean: $(DIRS)
	rm -rf jars

.PHONY: $(DIRS)
$(DIRS):
	$(MAKE) -C $@ $(MY_GOAL)
