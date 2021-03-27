make

modinfo ./chupcko.ko

insmod ./chupcko.ko

dmesg

lsmod | grep chupcko

ls -la /proc/chupcko

cat /proc/chupcko

rmmod chupcko

dmesg

make clean
