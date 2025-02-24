#pragma once
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <string.h> 
void afficher_ecran(SDL_Surface *image,SDL_Rect *pos,SDL_Surface *ecran);
SDL_Surface* affichage(char nom[],SDL_Rect *pos);
SDL_Surface *affichageb(char nom[],SDL_Rect *pos);
SDL_Surface *affichageb2(char nom[],SDL_Rect *pos);
TTF_Font *affichage_text2(char nom[]);
TTF_Font *affichage_score(char nom[]);
TTF_Font *affichage_name(char nom[]);
int mousehover(SDL_Rect pos);
void score2(SDL_Surface *ecran);
void liberer2(SDL_Surface *image,Mix_Music *musique,TTF_Font *font,Mix_Chunk *tick);
