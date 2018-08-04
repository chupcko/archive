OBJS = main.o


CFLAGS    = -O3 -Wall
LDFLAGS   = -s
STRIP     = strip --strip-debug

.SUFFIXES: .c .o .s .so

.c.o:
	$(CC) $(CFLAGS) -c $<

.c.s:
	$(CC) $(CFLAGS) -S $<

.c.so:
	$(CC) -shared $(CFLAGS) -o $*.so $<


CFLAGS += -rdynamic
LDFLAGS += -rdynamic
LIBS = -ldl




all:  main.o moduo.so
	$(CC) $(LDFLAGS) -o dina $(OBJS) $(LIBS)

clean:
	rm -f dina *.o *.so

