prog: main.o enigme2.o
	gcc main.o enigme2.o -o prog -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf -g

main.o: main.c enigme2.h
	gcc -c main.c -g

source.o: enigme2.c enigme2.h
	gcc -c enigme2.c -g

