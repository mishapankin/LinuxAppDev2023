CFLAGS=-Wall -std=c99

OK='\e[1;32m[ Ok ]\e[0m'
FAIL=\e[1;31m[ Fail ]\e[0m

all: esub

esub: main.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f esub

test: esub
	@do_test() { \
		if [ $$(./esub $$1 $$2 $$3) = $$(echo $$3 | sed -E "s/$$1/$$2/") ]; then echo $(OK); else echo $(FAIL); fi \
	}; \
	do_test "regexp" "substitution" "string"; \
	do_test "regexp" "substitution" "regexp"; \

.PHONY: all clean test