TARGET = sk

INCLUDE_DIR = ../include

PROTOTYPE = $(INCLUDE_DIR)/prototype.h

INCLUDES =                        \
	$(INCLUDE_DIR)/main.h     \
	$(INCLUDE_DIR)/result.h   \
	$(INCLUDE_DIR)/result.x   \
	$(INCLUDE_DIR)/type.h     \
	$(INCLUDE_DIR)/constant.h \
	$(PROTOTYPE)              \

SOURCES =                                        \
	expression_add_item.c                    \
	expression_add_name.c                    \
	expression_check.c                       \
	expression_compare_name.c                \
	expression_copy.c                        \
	expression_delete.c                      \
	expression_delete_item.c                 \
	expression_dump.c                        \
	expression_init.c                        \
	expression_length.c                      \
	expression_load.c                        \
	expression_post_walk.c                   \
	expression_pre_walk.c                    \
	expression_print.c                       \
	expression_reduction.c                   \
	expression_reduction_associative.c       \
	expression_reduction_combinator_b.c      \
	expression_reduction_combinator_c.c      \
	expression_reduction_combinator_f.c      \
	expression_reduction_combinator_helper.c \
	expression_reduction_combinator_i.c      \
	expression_reduction_combinator_j.c      \
	expression_reduction_combinator_k.c      \
	expression_reduction_combinator_m.c      \
	expression_reduction_combinator_s.c      \
	expression_reduction_combinator_w.c      \
	expression_reduction_lazy.c              \
	expression_reduction_single.c            \
	main.c                                   \
	result_text.c                            \

COMPILER = gcc
COMPILER_FLAGS = -c -I. -I$(INCLUDE_DIR)
LINKER = gcc
LINKER_FLAGS =

OBJECTS = $(patsubst %.c, %.o, $(SOURCES))

.PHONY: all debug clean

all: $(TARGET)

debug: override COMPILER_FLAGS += -g
debug: clean all

clean:
	rm -f $(PROTOTYPE) $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(LINKER) $(LINKER_FLAGS) -o $@ $(OBJECTS)

$(PROTOTYPE): $(SOURCES)
	../tool/make_prototype

%.o: %.c $(INCLUDES)
	$(COMPILER) $(COMPILER_FLAGS) -o $@ $<
