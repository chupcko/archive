all: show_mac mac_interposer

show_mac:
	gcc -o show_mac show_mac.c

mac_interposer:
	gcc -shared -o mac_interposer.so mac_interposer.c -fPIC -ldl

clean:
	rm -f show_mac mac_interposer.so
