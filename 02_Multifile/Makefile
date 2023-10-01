SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)
GENERATES = prog prog-a prog-so README
TRASH = *.o *.a *.so test_*

CFLAGS=-fPIC

.PHONY: all clean distclean

all: README prog prog-a prog-so test

prog: $(OBJECTS)

prog-a: prog.o liboutput_static.a
	$(CC) -L. $< -loutput_static -o $@

prog-so: prog.o liboutput.so
	$(CC) -L. $< -loutput -o $@

prog.o: outlib.h
fun.o: outlib.h

liboutput_static.a: fun.o const.o
	ar -rcs $@ $^

liboutput.so: fun.o const.o
	$(CC) -shared $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

README: prog
	./$< 2> $@

test: prog prog-a prog-so
	bash -c "exec -a prog ./prog 2> test_0"
	bash -c "exec -a prog ./prog-a 2> test_a_0"
	bash -c "LD_LIBRARY_PATH=. exec -a prog ./prog-so 2> test_so_0"

	./prog hello > test_1
	./prog-a hello > test_a_1
	LD_LIBRARY_PATH=. ./prog-so hello > test_so_1

	./prog hello linux world > test_3
	./prog-a hello linux world > test_a_3

	LD_LIBRARY_PATH=. ./prog-so hello linux world > test_so_3

	@echo "\ntest0:"
	cmp test_0 test_a_0 && cmp test_0 test_so_0

	@echo "\ntest1:"
	cmp test_1 test_a_1 && cmp test_1 test_so_1

	@echo "\ntest3:"
	cmp test_3 test_a_3 && cmp test_3 test_so_3

	@echo "\n\033[0;32mTESTS PASSED\033[0m"


clean:
	rm -f $(TRASH)

distclean: clean
	rm -rf $(GENERATES)