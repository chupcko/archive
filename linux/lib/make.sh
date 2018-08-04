rm -rf main ll_init.o ll_next.o ll.lib
gcc -c ll_init.c
gcc -c ll_next.c
ar cr ll.lib ll_init.o ll_next.o
gcc -o main main.c ll.lib
