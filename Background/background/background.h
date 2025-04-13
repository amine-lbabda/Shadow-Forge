#pragma once
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#define LARGEURFENETRE 1920
#define HAUTEURFENETRE 1080
#define ECRAN 1
#define dx 20
#define dy 20
typedef struct background
{
	SDL_Surface *image;
	SDL_Rect posimage;
	SDL_Rect poscamera;
	int direction;
	// Mix_Chunk *perdre_vie;
	// Mix_Chunk *gain_vie;
	// Mix_Chunk *augmentation;
	// Mix_Chunk *record;
	// Mix_Music *musique;
	// Mix_Chunk *echoue;
	// Mix_Chunk *succes;
	// Mix_Chunk *victoire;
	// Mix_Chunk *mort;
	// Mix_Chunk *blessure;
	// Mix_Chunk *passe_niveau;
} background;

typedef struct joueur
{
	SDL_Surface *image;
	SDL_Rect posjoueur;
} joueur;
// typedef struct obstacle
// {
// 	SDL_Surface *obs;
// 	SDL_Rect posimg;
// 	int type;
// } obstacle;
// typedef struct temps
// {
// 	SDL_Surface *text;
// 	char text_input[50];
// 	TTF_Font *font;
// 	int size;
// } temps;
void init_background(background *b, SDL_Surface *e);
void posbackground(background *b, int x, int y, int w, int h);
void poscam(background *b, int x, int y, int w, int h);
void scrolling(background *b, SDL_Surface *e);
// void init_obstacle(obstacle *o);
// void init_temps();
// void afficher(SDL_Surface *image, SDL_Rect *posimg, SDL_Surface *ecran, SDL_Rect *posimg_finale);
// void changer_pos_background(SDL_Rect *posimg, int dx);
// SDL_Surface *calcul_temps();
// void free_surfaces(SDL_Surface *background);
// void background_loop();
