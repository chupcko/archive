CFLAGS = -O2 -pedantic
OBJ =\
  setof.o\
  aprcom.o\
  regexp.o\
  lexana.o\
  impfp.o\
  semdom.o\
  semfje.o\
  semana.o\
  azot.o

all: azot

azot: $(OBJ)
	cc $(CFLAGS) $(OBJ) -lm -o azot
	strip azot
	cp azot ..

clean:
	rm -f core
	rm -f *.o
	rm -f azot
