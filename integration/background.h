#pragma once
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#define LARGEURFENETRE 1920
#define HAUTEURFENETRE 1080
#define ECRAN 1
typedef struct perso perso;
typedef struct background
{
    SDL_Surface *image;
    SDL_Rect posimage;
    SDL_Rect poscamera;
    int direction;
    Mix_Music *musique;
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
void init_background(background *b, SDL_Surface *e, char nom_fichier[]);
void posbackground(background *b, int x, int y, int w, int h);
void poscam(background *b, int x, int y, int w, int h);
void animate_leaves(SDL_Surface *leaves, SDL_Rect leaves_pos, int world_x, int *bounce_y, int *direction,
                    int bounce_min, int bounce_max, int bounce_speed, int camX, SDL_Surface *screen);
