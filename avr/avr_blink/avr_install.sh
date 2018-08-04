#!/bin/sh

DIR=/home/chupcko/app/avr

BINUTILS_VERSION=2.24
GCC_VERSION=4.9.0
AVRLIBC_VERSION=1.8.0
AVRDUDE_VERSION=6.1

HOME=$(pwd)

mkdir -p ${DIR}/bin
PATH=$PATH:${DIR}/bin

if [ ! -f binutils-${BINUTILS_VERSION}.tar.bz2 ]
then
  wget -c http://ftp.gnu.org/gnu/binutils/binutils-${BINUTILS_VERSION}.tar.bz2
fi
if [ ! -f gcc-${GCC_VERSION}.tar.bz2 ]
then
  wget -c http://ftp.gnu.org/gnu/gcc/gcc-${GCC_VERSION}/gcc-${GCC_VERSION}.tar.bz2
fi
if [ ! -f avr-libc-${AVRLIBC_VERSION}.tar.bz2 ]
then
  wget -c http://download.savannah.gnu.org/releases/avr-libc/avr-libc-${AVRLIBC_VERSION}.tar.bz2
fi
if [ ! -f avrdude-${AVRDUDE_VERSION}.tar.gz ]
then
  wget -c http://download.savannah.gnu.org/releases/avrdude/avrdude-${AVRDUDE_VERSION}.tar.gz
fi

cd ${HOME}
tar xjvvf binutils-${BINUTILS_VERSION}.tar.bz2
cd binutils-${BINUTILS_VERSION}
./configure --target=avr --prefix=${DIR} --program-prefix=avr-
make
make install

cd ${HOME}
tar xjvvf gcc-${GCC_VERSION}.tar.bz2
cd gcc-${GCC_VERSION}
mkdir obj
cd obj
../configure --target=avr --prefix=${DIR} --program-prefix=avr- --enable-language=c
make
make install

cd ${HOME}
tar xjvvf avr-libc-${AVRLIBC_VERSION}.tar.bz2
cd avr-libc-${AVRLIBC_VERSION}
./configure --build=$(./config.guess) --host=avr --prefix=${DIR}
make
make install

cd ${HOME}
tar xzvvf avrdude-${AVRDUDE_VERSION}.tar.gz
cd avrdude-${AVRDUDE_VERSION}
./configure --prefix=${DIR}
make
make install
