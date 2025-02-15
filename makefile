prog:main.o
	gcc main.o -g
main.o:main.c
	gcc -c main.c -g
