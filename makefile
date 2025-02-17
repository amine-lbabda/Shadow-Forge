prog:main.o
	gcc main.o source.o -g -o prog
main.o:main.c
	gcc -c main.c -g
source.o:source.c
	gcc -c source.c -g
