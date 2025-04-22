#include "enigme2.h"

void initEnigme(Enigme *e) {
    e->dragged_image = NULL;
    e->dragged_pos = NULL;
    SDL_Surface *temp;

    // Load clean background
    temp = IMG_Load("bground.png");
    if (temp != NULL) {
        e->image_clean_background = SDL_DisplayFormat(temp);
        SDL_FreeSurface(temp);
    } else {
        printf("Failed to load bground.png: %s\n", IMG_GetError());
        e->image_clean_background = NULL;
    }

    // Load success image
    temp = IMG_Load("win.png");
    if (temp != NULL) {
        e->image_success = SDL_DisplayFormatAlpha(temp);
        SDL_FreeSurface(temp);
    } else {
        printf("Failed to load win.png: %s\n", IMG_GetError());
        e->image_success = NULL;
    }
    temp = IMG_Load("lose.png");
if (temp != NULL) {
    e->image_fail = SDL_DisplayFormatAlpha(temp);
    SDL_FreeSurface(temp);
} else {
    printf("Failed to load lose.png: %s\n", IMG_GetError());

}

    // Other puzzle elements
    e->image_background = IMG_Load("puzzle.png");
    e->image_piece = IMG_Load("final_correct_piece.png");
    e->image_decoy1 = IMG_Load("decoy_piece_1.png");
    e->image_decoy2 = IMG_Load("decoy_piece_2.png");



    e->is_dragging = 0;
    e->etat = 0;

    e->pos_target.x = 120;
    e->pos_target.y = 120;

    e->pos_piece.x = 1600;
    e->pos_piece.y = 200;

    e->pos_decoy1.x = 1200;
    e->pos_decoy1.y = 0;

    e->pos_decoy2.x = 1200;
    e->pos_decoy2.y = 400;
}


void afficherEnigme(Enigme *e, SDL_Surface *screen) {
SDL_BlitSurface(e->image_clean_background, NULL, screen, NULL); // clean redraw
SDL_BlitSurface(e->image_background, NULL, screen, NULL); // puzzle area
    SDL_BlitSurface(e->image_piece, NULL, screen, &e->pos_piece);
    SDL_BlitSurface(e->image_decoy1, NULL, screen, &e->pos_decoy1);
    SDL_BlitSurface(e->image_decoy2, NULL, screen, &e->pos_decoy2);

    if (e->etat == 1 && e->image_success != NULL) {
        SDL_Rect pos_success;
        pos_success.x = 0;  // Adjust to fit your layout
        pos_success.y = 0;
        SDL_BlitSurface(e->image_success, NULL, screen, &pos_success);
    }
    
    else if (e->etat == -1 && e->image_fail != NULL) {
        SDL_Rect pos_fail;
        pos_fail.x = 0; // Adjust as needed
        pos_fail.y = 0;
        SDL_BlitSurface(e->image_fail, NULL, screen, &pos_fail);
    }
    
}

int checkSuccess(Enigme *e) {
    if (e->dragged_pos == NULL)
        return 0;

    if (abs(e->dragged_pos->x - e->pos_target.x) < 30 &&
        abs(e->dragged_pos->y - e->pos_target.y) < 30)
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
    SDL_FreeSurface(e->image_clean_background);

};
