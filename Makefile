CC = cc
CFLAGS = -O2

TARGET = 86asm
SRC = src/main.c src/lexer.c

$(TARGET): $(SRC)
	mkdir -p build
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf build 86asm

.PHONY: all clean