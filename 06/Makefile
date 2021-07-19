CFLAGS = -g -Og -Wall -Wextra -Wconversion -pedantic
SOURCES = $(wildcard *.c)

run: compile
	./a.out test.asm

compile:
	cc ${SOURCES} ${CFLAGS}

