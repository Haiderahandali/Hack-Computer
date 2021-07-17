CFLAGS = -g -O0 -Wall -Wextra -Wconversion -pedantic
SOURCES = $(wildcard *.c)

run: compile
	./a.out test.asm

compile:
	cc ${SOURCES} ${CFLAGS}
