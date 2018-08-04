INCLUDE_DIR := ../include

TARGET_LIBRARY := r2.a
TARGET_INCLUDE := r2.h

TARGET :=                 \
	$(TARGET_LIBRARY) \
	$(TARGET_INCLUDE) \

PROTOTYPE := prototype.h

INCLUDES = $(filter-out $(PROTOTYPE), $(wildcard $(INCLUDE_DIR)/*.h)) $(wildcard $(INCLUDE_DIR)/*.x) $(PROTOTYPE)
SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)

COMPILER := gcc
COMPILER_FLAGS := -I$(INCLUDE_DIR) -I.
ARCHIVER := ar
ARCHIVER_FLAGS := csr

.DEFAULT_GOAL := all
.PHONY: all
all: $(TARGET)

.PHONY: debug
debug: COMPILER_FLAGS += -g -D_DEBUG_
debug: clean $(TARGET)

.PHONY: clean
clean:
	rm -rf $(TARGET) $(OBJECTS) $(PROTOTYPE)

$(PROTOTYPE): $(SOURCES)
	echo '#ifndef __PROTOTYPE_H__' > $@
	echo '#define __PROTOTYPE_H__' >> $@
	echo >> $@
	cat $^ | sed -e '/__FUNCTION_BEGIN__/{s/.*__FUNCTION_BEGIN__/extern /;:l;/__FUNCTION_END__/{s/__FUNCTION_END__.*/;/;b};n;bl};d' >> $@
	echo >> $@
	echo '#endif' >> $@

%.o: %.c $(INCLUDES)
	$(COMPILER) $(COMPILER_FLAGS) -c -o $@ $<

$(TARGET_LIBRARY): $(OBJECTS)
	$(ARCHIVER) $(ARCHIVER_FLAGS) $@ $^

$(TARGET_INCLUDE): $(INCLUDES) $(SOURCES)
	echo '#ifndef __R2_H__' > $@
	echo '#define __R2_H__' >> $@
	echo >> $@
	cat $(INCLUDE_DIR)/main.h | sed -e '/^__INCLUDE_BEGIN__$$/{s/^__INCLUDE_BEGIN__$$//;:l;/^__INCLUDE_END__$$/{s/^__INCLUDE_END__$$//;b};n;bl};d' >> $@
	cat $(INCLUDE_DIR)/configuration.h | sed -e '/^__INCLUDE_BEGIN__$$/{s/^__INCLUDE_BEGIN__$$//;:l;/^__INCLUDE_END__$$/{s/^__INCLUDE_END__$$//;b};n;bl};d' >> $@
	cat $(INCLUDE_DIR)/type.h | sed -e '/^__INCLUDE_BEGIN__$$/{s/^__INCLUDE_BEGIN__$$//;:l;/^__INCLUDE_END__$$/{s/^__INCLUDE_END__$$//;b};n;bl};d' >> $@
	$(COMPILER) -I$(INCLUDE_DIR) -E $(INCLUDE_DIR)/type_move.h | grep -v '^#' >> $@
	cat $(INCLUDE_DIR)/type_cube.h | sed -e '/^__INCLUDE_BEGIN__$$/{s/^__INCLUDE_BEGIN__$$//;:l;/^__INCLUDE_END__$$/{s/^__INCLUDE_END__$$//;b};n;bl};d' >> $@
	cat $(SOURCES) | sed -e '/__FUNCTION_BEGIN__/{s/.*__FUNCTION_BEGIN__/extern /;:l;/__FUNCTION_END__/{s/__FUNCTION_END__.*/;/;b};n;bl};d' >> $@
	echo >> $@
	echo '#endif' >> $@
	