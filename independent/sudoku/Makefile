CC = gcc
CCFLAGS = -I./include

NAME = main

OBJECTS = \
	character_set.o \
	find.o \
	main.o \
	postscript_debug.o \
	postscript_flags.o \
	postscript_print.o \
	postscript_template.o \
	shape.o \
	solve.o \
	table_debug.o \
	table_fixate.o\
	table_init.o \
	table_print.o \
	table_read.o \

$(NAME): $(OBJECTS) postscript_template.c
	$(CC) $(OBJECTS) -o $(NAME)

postscript_template.c:
	cat postscript_template.c.head > postscript_template.c
	echo "static char *SDK_postscript_head_string =" >> postscript_template.c
	cat postscript/template_head.ps | sed 's/.*/  "&\\n"/' | sed '$$s/.*/&;/' >> postscript_template.c
	echo >> postscript_template.c
	echo "static char *SDK_postscript_tail_string =" >> postscript_template.c
	cat postscript/template_tail.ps | sed 's/.*/  "&\\n"/' | sed '$$s/.*/&;/' >> postscript_template.c
	cat postscript_template.c.tail >> postscript_template.c

.SUFFIXES: .c .o
.c.o:
	$(CC) -c $(CCFLAGS) $<

all: $(NAME)

clean:
	$(RM) postscript_template.c *.o $(NAME)

debug: override CCFLAGS += -g
debug: clean all
