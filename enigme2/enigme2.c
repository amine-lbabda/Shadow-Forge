#include "enigme2.h"

void initEnigme(Enigme *e) {
    e->image_background = IMG_Load("puzzle.png");
    e->image_piece = IMG_Load("final_correct_piece.png");
    e->image_decoy1 = IMG_Load("decoy_piece_1.png");
    e->image_decoy2 = IMG_Load("decoy_piece_2.png");

    e->image_success = NULL;
    e->image_fail = NULL;

    e->is_dragging = 0;
    e->etat = 0;

    e->pos_target.x = 300;
    e->pos_target.y = 150;

    int base_x = 1200;
    e->pos_piece.x = base_x;
    e->pos_piece.y = 0;

    e->pos_decoy1.x = 1200;
    e->pos_decoy1.y = 0;

    e->pos_decoy2.x = 1200;
    e->pos_decoy2.y = 200;
}

void afficherEnigme(Enigme *e, SDL_Surface *screen) {
    SDL_BlitSurface(e->image_background, NULL, screen, NULL);
    SDL_BlitSurface(e->image_piece, NULL, screen, &e->pos_piece);
    SDL_BlitSurface(e->image_decoy1, NULL, screen, &e->pos_decoy1);
    SDL_BlitSurface(e->image_decoy2, NULL, screen, &e->pos_decoy2);

    if (e->etat == 1)
        SDL_BlitSurface(e->image_success, NULL, screen, NULL);
    else if (e->etat == -1)
        SDL_BlitSurface(e->image_fail, NULL, screen, NULL);
}

int checkSuccess(Enigme *e) {
    if (abs(e->pos_piece.x - e->pos_target.x) < 30 &&
        abs(e->pos_piece.y - e->pos_target.y) < 30)
        return 1;
    return 0;
}

void liberer(Enigme *e) {
    SDL_FreeSurface(e->image_background);
    SDL_FreeSurface(e->image_piece);
    SDL_FreeSurface(e->image_decoy1);
    SDL_FreeSurface(e->image_decoy2);
    SDL_FreeSurface(e->image_success);
    SDL_FreeSurface(e->image_fail);
};
