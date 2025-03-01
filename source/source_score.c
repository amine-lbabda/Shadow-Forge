#include "score.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <stdio.h>

SDL_Surface *affichage(char nom[], SDL_Rect *pos)
{
	SDL_Surface *image;
	image = IMG_Load(nom);
	pos->x = 0;
	pos->y = 0;
	pos->w = image->w;
	pos->h = image->h;
	return image;
}
SDL_Surface *affichageb(char nom[], SDL_Rect *pos)
{
	SDL_Surface *image;
	image = IMG_Load(nom);
	pos->x = 660;
	pos->y = 540;
	pos->w = image->w;
	pos->h = image->h;
	return image;
}
SDL_Surface *affichageb2(char nom[], SDL_Rect *pos)
{
	SDL_Surface *image;
	image = IMG_Load(nom);
	pos->x = 560;
	pos->y = 150;
	pos->w = image->w;
	pos->h = image->h;
	return image;
}

TTF_Font *affichage_text2(char nom[])
{
	return TTF_OpenFont(nom, 50);
}
TTF_Font *affichage_score(char nom[])
{
	return TTF_OpenFont(nom, 150);
}
TTF_Font *affichage_name(char nom[])
{
	return TTF_OpenFont(nom, 110);
}
void afficher_ecran(SDL_Surface *image, SDL_Rect *pos, SDL_Surface *ecran)
{
	SDL_BlitSurface(image, NULL, ecran, pos);
}
int mousehover(SDL_Rect pos)
{
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	return (mouseX >= pos.x && mouseX <= pos.x + pos.w &&
			mouseY >= pos.y && mouseY <= pos.y + pos.h);
}
void liberer2(SDL_Surface *image, TTF_Font *font, Mix_Chunk *tick, int run)
{
	Mix_FreeChunk(tick);
	SDL_FreeSurface(image);
	if (run != 0)
	{
		TTF_CloseFont(font);
	}
}
