#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

typedef struct
{
    SDL_Surface *bg_principale;
    SDL_Surface *bquiz[2];
    SDL_Surface *bpuzzle[2];
    SDL_Surface *logo;
    SDL_Surface *Return[2];
    SDL_Rect posr;
    SDL_Rect posl;
    SDL_Rect posquiz;
    SDL_Rect pospuzzle;
    SDL_Rect posquiz2;
    SDL_Rect pospuzzle2;
    int poscursor;

} menu;
typedef struct
{
    SDL_Surface *bg_principale;
    SDL_Surface *Return[2];
    SDL_Rect posr;
    int poscursor;

} quiz;
void init_menu(menu *);
void afficher_menu(menu, SDL_Surface *ecran);
int cursor(SDL_Rect);
void update(menu *);
void afficher_quiz(quiz, SDL_Surface *ecran);
void init_quiz(quiz *);
void cleanup(menu *m, quiz *q);
void menu_quiz(SDL_Surface *ecran);
#endif