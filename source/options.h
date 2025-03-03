#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
typedef struct image
{
    SDL_Surface *image;
    SDL_Rect rect;
} image;
typedef struct text
{
    TTF_Font *font;
    SDL_Surface *text;
    SDL_Rect rectx;
} text;
int verif_collision_2(SDL_Event e, image button);
void menu_options(SDL_Surface *window, Mix_Music *music_chunk, int *currentVolume, int *run, int *initial_menu);
