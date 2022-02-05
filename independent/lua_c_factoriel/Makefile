factoriel.so: factoriel.c
	rm -f factoriel.so
	gcc -Wall -fPIC -shared -o factoriel.so -I /usr/include/lua5.1/ -llua5.1 factoriel.c
	lua test.lua
