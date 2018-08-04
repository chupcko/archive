PROJECT = parjob

COMPILER       = gcc
COMPILER_FLAGS = -c -I.
LINKER         = gcc
LINKER_FLAGS   =
LINKER_LIBS    =

SOURCES  =                  \
	child_dead.c        \
	dump.c              \
	job_data_clean.c    \
	job_data_init.c     \
	main.c              \
	read_next_command.c \
	start_new_child.c   \
	wait_all_children.c \

INCLUDES =          \
	main.h      \
	variable.h  \
	prototype.h \

OBJECTS  = $(patsubst %.c, %.o, $(SOURCES))
TEST_IN  = test.job

.DEFAULT_GOAL = all
.PHONNY: all clean test

all: $(PROJECT)

clean:
	rm -rf $(OBJECTS) $(PROJECT) $(TEST_OUT)

test: $(PROJECT) $(TEST_OUT) $(TEST_IN)
	./$(PROJECT) -d -n 3 $(TEST_IN)

$(PROJECT): $(OBJECTS)
	$(LINKER) $(LINKER_FLAGS) -o $@ $(OBJECTS) $(LINKER_LIBS)

%.o: %.c $(SOURCES) $(INCLUDES)
	$(COMPILER) $(COMPILER_FLAGS) -o $@ $<

$(TEST_OUT):
	mkdir -p $(TEST_OUT)
