prog: main.o minimap.o collision.o
	gcc main.o minimap.o collision.o -o prog -lSDL -g -lSDL_image -lSDL_mixer -lSDL_ttf

main.o: main.c minimap.h collision.h
	gcc -c main.c -g

minimap.o: minimap.c minimap.h
	gcc -c minimap.c -g

collision.o: collision.c collision.h
	gcc -c collision.c -g
