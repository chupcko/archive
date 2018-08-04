COMPILER = gcc
LINKER = gcc
ARCHIVER = ar

CFLAGS = -c

TARGET = falcom.lib
TARGET_TEST = test_falcom

all: $(TARGET) $(TARGET_TEST)

debug: override CFLAGS += -g
debug: clean all

clean:
	rm -rf *~ core* *.o $(TARGET) $(TARGET_TEST)

OBJS = falcom.o
OBJS_TEST = test_falcom.o

.c.o:
	$(COMPILER) $(CFLAGS) $<

$(TARGET): $(OBJS)
	$(ARCHIVER) cr $@ $(OBJS)
$(TARGET_TEST): $(OBJS_TEST)
	$(LINKER) -o $@ $(OBJS_TEST) $(TARGET)
