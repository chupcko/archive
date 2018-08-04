all: crct.h md5.o crc.o info.o main.o
	cc md5.o crc.o info.o main.o -o CHPchk
	strip CHPchk

crct.h: crct
	crct > crct.h

clean:
	rm -f crct crct.h CHPchk *.o
