.PHONY: all

CFLAGS=-g -O0 -Wall -std=c99

all: range

test: range
	gdb -x script1.py -ex r -ex q --args range 1 12 > /dev/null
	gdb -x script2.py -ex r -ex q --args range -100 100 3 > /dev/null

	@cmp range1_expected.txt range1.txt && echo "\e[1;32mTest 1 passed\e[0m" || echo "\e[1;31mTest 1 failed\e[0m"
	@cmp range2_expected.txt range2.txt && echo "\e[1;32mTest 2 passed\e[0m" || echo "\e[1;31mTest 2 failed\e[0m"

clean:
	rm -f range range1.txt range2.txt