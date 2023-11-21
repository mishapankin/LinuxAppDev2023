TARGET=lab

.PHONY: all clean

all: $(TARGET)

$(TARGET): main.c
	gcc -o $@ $^

clean:
	rm -f $(TARGET)