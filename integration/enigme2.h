#ifndef ENIGME2_H
#define ENIGME2_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

typedef struct
{
    SDL_Surface *image_background;
    SDL_Surface *image_piece;
    SDL_Surface *image_decoy1;
    SDL_Surface *image_decoy2;
    SDL_Surface *image_success;
    SDL_Surface *image_fail;
    SDL_Surface *dragged_image;
    SDL_Rect *dragged_pos;

    SDL_Rect pos_target;
    SDL_Rect pos_piece;
    SDL_Rect pos_decoy1;
    SDL_Rect pos_decoy2;
    SDL_Surface *image_clean_background;

    int is_dragging;
    int etat;
} Enigme;

void initEnigme(Enigme *e);
void afficherEnigme(Enigme *e, SDL_Surface *screen);
int checkSuccess(Enigme *e);
void liberer(Enigme *e);
void enigme_2(SDL_Surface *screen, int *quitter);
#endif
