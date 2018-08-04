all: source

source:
	cd src && make

document:
	cd doc && make

clean:
	rm -f core
	rm -f azot
	cd src && make clean
	cd doc && make clean

archive: clean
	rm -f azot.tgz
	tar czf azot.tgz *
