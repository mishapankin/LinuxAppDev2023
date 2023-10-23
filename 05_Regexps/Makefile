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
		echo -n "Testing \"$$1\" \"$$2\" \"$$3\"... "; \
		if [ $$(./esub $$1 $$2 $$3 -nc) = $$(echo $$3 | sed -E "s/$$1/$$2/") ]; then echo $(OK); else echo $(FAIL); fi \
	}; \
	do_test "regexp" "substitution" "string"; \
	do_test "regexp" "substitution" "regexp"; \
	do_test "a(bc)d" "x\\1y" "_abcd_"; \
	do_test "a(b*)d" "x\\1y" "_ad_"; \
	do_test "a(b*)d" "x\\1y" "_abbbbbbbbbbbbbbbbbbbbbb_"; \

.PHONY: all clean test