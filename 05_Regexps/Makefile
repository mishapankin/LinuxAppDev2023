CFLAGS=-Wall -std=c99 -g

OK='\e[1;32m[ Ok ]\e[0m'
FAIL=\e[1;31m[ Fail ]\e[0m

all: esub

esub: main.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f esub

test: esub
	@do_test() { \
		if [ $$(./esub $$1 $$2 $$3 -nc) = $$(echo $$3 | sed -E "s/$$1/$$2/") ]; then echo -n $(OK); else echo -n $(FAIL); fi;  \
		echo "\tTesting \"$$1\" \"$$2\" \"$$3\"... "; \
	}; \
	do_test "regexp" "substitution" "string"; \
	do_test "regexp" "substitution" "regexp"; \
	do_test "a(bc)d" "x\\1y" "_abcd_"; \
	do_test "a(b*)d" "x\\1y" "_ad_"; \
	do_test "a(b*)d" "x\\1y" "_abbbbbbbbbbbbbbbbbbbbbb_"; \
	do_test "a(b*)(bb)d" "x\\1y\\2" "_abbbd_"; \

.PHONY: all clean test