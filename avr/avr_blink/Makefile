TARGET := blink

SOURCES := $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)

PATH += :/home/chupcko/app/avr/bin

COMPILER := avr-gcc
LINKER := avr-gcc
OBJCOPY := avr-objcopy
AVRDUDE := avrdude

COMPILER_FLAGS := -mmcu=atmega328 -DF_CPU=16000000UL -Os
LINKER_FLAGS :=
OBJCOPY_FLAGS := -j .text -O ihex
AVRDUDE_FLAGS := -pm328p -cstk500v1 -P /dev/ttyUSB0 -D -b 57600

.DEFAULT_GOAL := all
all: $(TARGET).hex

$(TARGET).hex: $(TARGET).out
	$(OBJCOPY) $(OBJCOPY_FLAGS) $< $@

$(TARGET).out: $(OBJECTS)
	$(LINKER) $(LINKER_FLAGS) -o $@ $^

%.o: %.c
	$(COMPILER) $(COMPILER_FLAGS) -c $<

.PHONY: clean
clean:
	rm -rf $(OBJECTS) $(TARGET).out $(TARGET).hex

.PHONY: install
install: $(TARGET).hex
	$(AVRDUDE) $(AVRDUDE_FLAGS) -U flash:w:$<
