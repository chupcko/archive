SUNCE_DIR := ../out
SUNCE_INCLUDE = $(SUNCE_DIR)/sunce.h
SUNCE_LIBRARY = $(SUNCE_DIR)/libsunce.a

SOURCES := $(wildcard *.c)
PROGRAMS := $(SOURCES:.c=.t)

COMPILER := gcc
COMPILER_FLAGS = -I$(SUNCE_DIR)
LIBRARIES = $(SUNCE_LIBRARY)

.DEFAULT_GOAL := all
.PHONY: all
all: $(PROGRAMS)

.PHONY: debug
debug: COMPILER_FLAGS += -g
debug: all

.PHONY: clean
clean:
	rm -f $(PROGRAMS)

%.t: %.c $(SUNCE_INCLUDE) $(SUNCE_LIBRARY)
	$(COMPILER) $(COMPILER_FLAGS) -o $@ $< $(LIBRARIES)
