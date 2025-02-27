#pragma once
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#define WIDTH_ECRAN 1920
#define HEIGHT_ECRAN 1080
typedef struct image
{
    SDL_Surface *image;
    SDL_Rect posimage;
} image;

typedef struct text
{
    TTF_Font *font;
    SDL_Surface *text;
    SDL_Color textcouleur;
    SDL_Rect postext;
} text;

SDL_Surface *load_image(char *name);
void afficher(SDL_Surface *image, SDL_Rect *posimage, SDL_Surface *ecran, SDL_Rect *pos);
void aficher_text(SDL_Surface *text, SDL_Rect *postext, SDL_Surface *ecran);
SDL_Surface *affichage_text(TTF_Font *font, char *text, SDL_Color color);
int verif_collision(SDL_Event e, image button);

void position_image(int x, int y, int w, int h, SDL_Rect *pos_image);

TTF_Font *load_font(char *name, int size);

void couleur_text(SDL_Color *color, int r, int g, int b);

void liberer(SDL_Surface *background, SDL_Surface *button_mono, SDL_Surface *button_multi, SDL_Surface *button_name_1, SDL_Surface *button_name_2, TTF_Font *font);
void menu_mode(SDL_Surface *ecran);