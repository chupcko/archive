.PHONY: all
all: sleep_test strace_filter_minute

.PHONE: clean
clean:
	rm -f sleep_test strace_filter_minute out-*

.PHONE: test
test: all
	strace -o '|`pwd`/strace_filter_minute out' ./sleep_test
