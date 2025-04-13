#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "enigme2.h"

int main() {
    SDL_Surface *screen;
    SDL_Event event;
    int running = 1;

    SDL_Init(SDL_INIT_VIDEO);
    screen = SDL_SetVideoMode(1920, 1200, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Enigme Puzzle", NULL);

    Enigme e;
    initEnigme(&e);

    while (running) {
        afficherEnigme(&e, screen);
        SDL_Flip(screen);

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = 0;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        if (event.button.x >= e.pos_piece.x &&
                            event.button.x <= e.pos_piece.x + e.image_piece->w &&
                            event.button.y >= e.pos_piece.y &&
                            event.button.y <= e.pos_piece.y + e.image_piece->h) {
                            e.is_dragging = 1;
                        }
                    }
                    break;

                case SDL_MOUSEBUTTONUP:
                    if (event.button.button == SDL_BUTTON_LEFT && e.is_dragging) {
                        e.is_dragging = 0;
                        if (checkSuccess(&e))
                            e.etat = 1;
                        else
                            e.etat = -1;
                    }
                    break;

                case SDL_MOUSEMOTION:
                    if (e.is_dragging) {
                        e.pos_piece.x = event.motion.x;
                        e.pos_piece.y = event.motion.y;
                    }
                    break;
            }
        }
    }

    liberer(&e);
    SDL_Quit();
    return 0;
}

