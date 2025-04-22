#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "enigme2.h"

void enigme_2(SDL_Surface *screen, int *quitter)
{
    SDL_Event event;


    Enigme e;
    initEnigme(&e);

    while (*quitter == 1)
    {
        afficherEnigme(&e, screen);
        SDL_Flip(screen);

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                *quitter = 0;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    *quitter = 0;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    int x = event.button.x;
                    int y = event.button.y;

                    if (x >= e.pos_piece.x && x <= e.pos_piece.x + e.image_piece->w &&
                        y >= e.pos_piece.y && y <= e.pos_piece.y + e.image_piece->h)
                    {
                        e.is_dragging = 1;
                        e.dragged_image = e.image_piece;
                        e.dragged_pos = &e.pos_piece;
                    }
                    else if (x >= e.pos_decoy1.x && x <= e.pos_decoy1.x + e.image_decoy1->w &&
                             y >= e.pos_decoy1.y && y <= e.pos_decoy1.y + e.image_decoy1->h)
                    {
                        e.is_dragging = 1;
                        e.dragged_image = e.image_decoy1;
                        e.dragged_pos = &e.pos_decoy1;
                    }
                    else if (x >= e.pos_decoy2.x && x <= e.pos_decoy2.x + e.image_decoy2->w &&
                             y >= e.pos_decoy2.y && y <= e.pos_decoy2.y + e.image_decoy2->h)
                    {
                        e.is_dragging = 1;
                        e.dragged_image = e.image_decoy2;
                        e.dragged_pos = &e.pos_decoy2;
                    }
                }
                break;

            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT && e.is_dragging)
                {
                    e.is_dragging = 0;

                    if (checkSuccess(&e))
                    {
                        // Snap any piece to the correct place
                        e.dragged_pos->x = 120;
                        e.dragged_pos->y = 120;

                        if (e.dragged_image == e.image_piece)
                            e.etat = 1; // win
                        else
                            e.etat = -1; // decoy placed, lose
                    }
                    else
                    {
                        e.etat = 0; // not placed near target
                    }

                    e.dragged_image = NULL;
                    e.dragged_pos = NULL;
                }
                break;

            case SDL_MOUSEMOTION:
                if (e.is_dragging && e.dragged_pos != NULL)
                {
                    e.dragged_pos->x = event.motion.x;
                    e.dragged_pos->y = event.motion.y;
                }
                break;
            }
        }
    }

    liberer(&e);
    SDL_Quit();
}
