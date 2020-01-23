all: hw1

hw1: main.c hw1
	gcc main.c -o hw1

check:
	clang-check *.c --

test:
	./hw1 -f file
	./hw1 -i 122222 -f face  comment
	./hw1 comment
	./hw1 I love NEU
	./hw1 A student at -i 19
	./hw1 -i No_Value -f 123 break
	./hw1 -f -i
	./hw1 -i -1 is invalid
	./hw1 unimportant test -f -i
	./hw1 -f /
	./hw1 -f / -i 2020
	./hw1 -f / -i 1 10 / 2020
	./hw1 -f Score -i 100 Please orz

clean:
	rm -f hw1

.PHONY: all clean

