#!/bin/sh

make
./show_mac
export LD_PRELOAD=`pwd`/mac_interposer.so
./show_mac
