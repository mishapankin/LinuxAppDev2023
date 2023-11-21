TARGETS=lab0 lab1 lab2 lab3

.PHONY: all clean run

all: $(TARGETS)

lab%: main%.c
	gcc -o $@ $^

main1.c: main0.c
	patch -o $@ $^ 1.patch

main2.c: main1.c
	patch -o $@ $^ 2.patch

main3.c: main2.c
	patch -o $@ $^ 3.patch

run: $(TARGETS)
	./lab0
	./lab1 9
	./lab2 " #" 7
	./lab3 1 " #" 5

clean:
	rm -f $(TARGETS) main1.c main2.c main3.c