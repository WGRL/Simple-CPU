make_all:
	gcc -I./simulator/headers simulator/src/*.c -o simulator
	gcc Assembler/main.c -g -o assembler