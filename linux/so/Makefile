all: libmylib.so example

libmylib.so: mylib.c
	gcc -shared -o libmylib.so mylib.c -fPIC

example: example.c libmylib.so
	gcc -o example example.c -Wl,-rpath,'$$ORIGIN' -L. -lmylib

clean:
	rm -f libmylib.so example
