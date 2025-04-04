mymenu: main.o menu.o chargement.o save.o menu_mode.o source_menu.o source_score.o score.o options.o source_options.o quiz.o source_quiz.o source_menu_principale.o
	gcc $^ -o ./mymenu -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf  -g

main.o: source/main.c
	gcc -c source/main.c -g

menu.o: source/menu.c
	gcc -c source/menu.c -g

chargement.o: source/chargement.c
	gcc -c source/chargement.c -g

save.o: source/save.c
	gcc -c source/save.c -g

menu_mode.o: source/menu_mode.c
	gcc -c source/menu_mode.c -g

source_menu.o: source/source_menu.c
	gcc -c source/source_menu.c -g

source_score.o: source/source_score.c
	gcc -c source/source_score.c -g

score.o: source/score.c
	gcc -c source/score.c -g

options.o: source/options.c
	gcc -c source/options.c -g

source_options.o: source/source_options.c
	gcc -c source/source_options.c -g

quiz.o: source/quiz.c
	gcc -c source/quiz.c -g

source_quiz.o: source/source_quiz.c
	gcc -c source/source_quiz.c -g

source_menu_principale.o:source/source_menu_principale.c
	gcc -c source/source_menu_principale.c -g

clean:
	rm -f *.o

cleanall:
	rm -f *.o mymenu