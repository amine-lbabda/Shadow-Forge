prog:main.o
	gcc main.o -g -o prog
main.o:main.c
	gcc -c main.c -g
