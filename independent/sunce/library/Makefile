TARGET_DIR := ../out
TARGET_A = $(TARGET_DIR)/libsunce.a
TARGET_H = $(TARGET_DIR)/sunce.h

SOURCES_GENERATED := json_lexical.c json_syntax.c xml_lexical.c xml_syntax.c
SOURCES_FILES := $(filter-out $(SOURCES_GENERATED), $(wildcard *.c))
SOURCES = $(SOURCES_FILES) $(SOURCES_GENERATED)
OBJECTS = $(SOURCES:.c=.o)
GENERATED_PROTOTYPE := generated_prototype.h
INCLUDES_GENERATED := $(GENERATED_PROTOTYPE) json_lexical.h json_syntax.h xml_lexical.h xml_syntax.h
INCLUDES_FILES := $(filter-out $(INCLUDES_GENERATED), $(wildcard *.h))
INCLUDES = $(INCLUDES_FILES) $(INCLUDES_GENERATED)

LEX := flex
YACC := bison
COMPILER := gcc
COMPILER_FLAGS := -I.
ARCHIVER := ar
ARCHIVER_FLAGS := csr

.DEFAULT_GOAL := all
.PHONY: all
all: $(TARGET_DIR) $(TARGET_A) $(TARGET_H)

.PHONY: debug
debug: COMPILER_FLAGS += -g -DSUNCE_DEBUG
debug: all

.PHONY: clean
clean:
	rm -f $(SOURCES_GENERATED) $(INCLUDES_GENERATED) $(GENERATED_PROTOTYPE) $(OBJECTS)

%.h: %.l
	$(LEX) --header-file=$@ -o $(@:.h=.c) $<

%.c: %.l
	$(LEX) --header-file=$(@:.c=.h) -o $@ $<

%.h: %.y
	$(YACC) -o $(@:.h=.c) $<

%.c: %.y
	$(YACC) -o $@ $<

%.o: %.c $(INCLUDES)
	$(COMPILER) $(COMPILER_FLAGS) -c -o $@ $<

$(GENERATED_PROTOTYPE): $(SOURCES_FILES)
	echo '#ifndef __GENERATED_PROTOTYPE__H__' > $@
	echo '#define __GENERATED_PROTOTYPE__H__' >> $@
	cat $^ | sed -e '/_FUNCTION_DECLARATION_BEGIN_/{s/.*_FUNCTION_DECLARATION_BEGIN_//;:l;/_FUNCTION_DECLARATION_END_/{s/_FUNCTION_DECLARATION_END_.*/;/;b};n;bl};d' >> $@
	cat $^ | sed -e '/_LIBRARY_DECLARATION_BEGIN_/{s/.*_LIBRARY_DECLARATION_BEGIN_//;:l;/_LIBRARY_DECLARATION_END_/{s/_LIBRARY_DECLARATION_END_.*/;/;b};n;bl};d' >> $@
	echo >> $@
	echo '#endif' >> $@

$(TARGET_DIR):
	mkdir -p $@

$(TARGET_A): $(SOURCES) $(INCLUDES) $(OBJECTS)
	$(ARCHIVER) $(ARCHIVER_FLAGS) $@ $^

$(TARGET_H): $(SOURCES_FILES) $(INCLUDES_FILES)
	echo '#ifndef __JSON__H__' > $@
	echo '#define __JSON__H__' >> $@
	cat $(INCLUDES_FILES) | sed -e '/^_LIBRARY_INCLUDE_BEGIN/{s/_LIBRARY_INCLUDE_BEGIN_//;:l;/^_LIBRARY_INCLUDE_END/{s/_LIBRARY_INCLUDE_END_//;b};n;bl};d' >> $@
	cat $(SOURCES_FILES) | sed -e '/_LIBRARY_DECLARATION_BEGIN_/{s/.*_LIBRARY_DECLARATION_BEGIN_//;:l;/_LIBRARY_DECLARATION_END_/{s/_LIBRARY_DECLARATION_END_.*/;/;b};n;bl};d' >> $@
	echo >> $@
	echo '#endif' >> $@
