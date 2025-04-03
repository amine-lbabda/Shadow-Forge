mymenu: main.o menu.o chargement.o save.o menu_mode.o source_menu.o source_score.o score.o options.o source_options.o quiz.o source_quiz.o source_menu_principale.o
	gcc $^ -o ./mymenu -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf  -g

main.o: main.c
	gcc -c main.c -g

menu.o: menu.c
	gcc -c menu.c -g

chargement.o: chargement.c
	gcc -c chargement.c -g

save.o: save.c
	gcc -c save.c -g

menu_mode.o: menu_mode.c
	gcc -c menu_mode.c -g

source_menu.o: source_menu.c
	gcc -c source_menu.c -g

source_score.o: source_score.c
	gcc -c source_score.c -g

score.o: score.c
	gcc -c score.c -g

options.o: options.c
	gcc -c options.c -g

source_options.o: source_options.c
	gcc -c source_options.c -g

quiz.o: quiz.c
	gcc -c quiz.c -g

source_quiz.o: source_quiz.c
	gcc -c source_quiz.c -g

source_menu_principale.o:source_menu_principale.c
	gcc -c source_menu_principale.c -g

clean:
	rm -f *.o

cleanall:
	rm -f *.o mymenu