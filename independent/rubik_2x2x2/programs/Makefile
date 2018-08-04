R2_DIR         := ../library
R2_INCLUDE_DIR := $(R2_DIR)
R2_INCLUDE     := $(R2_INCLUDE_DIR)/r2.h
R2_LIBRARY_DIR := $(R2_DIR)
R2_LIBRARY     := $(R2_LIBRARY_DIR)/r2.a

TARGETS :=         \
	r2_solve   \
	r2_shuffle \

TARGETS_SOURCES = $(TARGETS:=.c)

SOURCES = $(filter-out $(TARGETS_SOURCES), $(wildcard *.c))
OBJECTS = $(SOURCES:.c=.o)

INCLUDE := $(wildcard *.h)

COMPILER := gcc
COMPILER_FLAGS := -I$(R2_INCLUDE_DIR) -I.

.DEFAULT_GOAL := all
.PHONY: all
all: $(TARGETS)

.PHONY: debug
debug: COMPILER_FLAGS += -g -D_DEBUG_
debug: clean $(TARGETS)

.PHONY: clean
clean:
	rm -rf $(TARGETS) $(OBJECTS)

%.o: %.c $(INCLUDE)
	$(COMPILER) $(COMPILER_FLAGS) -c -o $@ $<

%: %.c $(OBJECTS) $(INCLUDE) $(R2_INCLUDE) $(R2_LIBRARY)
	$(COMPILER) $(COMPILER_FLAGS) -o $@ $< $(OBJECTS) $(R2_LIBRARY)

$(TARGETS): $(OBJECTS)
