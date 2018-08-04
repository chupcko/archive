CC = gcc
LD = gcc
CCFLAGS = -I./include
LDFLAGS = -lusb

NAME = uhl

OBJECTS = \
	checksum.o \
	hex.o \
	hex_line.o \
	main.o \
	memory.o \
	processor.o \
	usb.o \
	usb_begin.o \
	usb_configuration.o \
	usb_end.o \
	usb_epprom.o \
	usb_erase.o \
	usb_flash.o \
	usb_id.o \

$(NAME): $(OBJECTS)
	$(LD) -o $(NAME) $(LDFLAGS) $(OBJECTS)

.SUFFIXES: .c .o
.c.o:
	$(CC) -c $(CCFLAGS) $<

all: $(NAME)

clean:
	$(RM) *.o $(NAME)

debug: override CCFLAGS += -g
debug: clean all
