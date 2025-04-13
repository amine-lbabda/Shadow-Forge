#include <SDL/SDL.h>
#include "minimap.h"
#include "collision.h"

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Surface *screen = SDL_SetVideoMode(800, 600, 32, SDL_SWSURFACE);
    if (!screen) {
        printf("Failed to set video mode: %s\n", SDL_GetError());
        return 1;
    }

    
    MiniMap m;
    initMiniMap(&m, 1);

    
    SDL_Rect player = {100, 200, 50, 50};  
    SDL_Rect camera = {0, 0, 800, 600};    

    
    SDL_Rect platform = {300, 200, 100, 50}; 
    int toggle = 0; 

    int running = 1;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = 0;
        }

       
        Uint8 *keys = SDL_GetKeyState(NULL);
        if (keys[SDLK_RIGHT]) player.x += 5;
        if (keys[SDLK_LEFT])  player.x -= 5;
        if (keys[SDLK_UP])    player.y -= 5;
        if (keys[SDLK_DOWN])  player.y += 5;

        
        updateMiniMap(&m, player, camera);

        
        int isColliding = boundingBoxCollision(player, platform);
        if (isColliding) {
            animateBackground(screen, &toggle);
        } else {
            SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
        }

        
        SDL_FillRect(screen, &platform, SDL_MapRGB(screen->format, 255, 255, 255));
        
        SDL_FillRect(screen, &player, SDL_MapRGB(screen->format, 255, 0, 0));
        
        displayMiniMap(m, screen);

        SDL_Flip(screen);
        SDL_Delay(16);
    }

    freeMiniMap(&m);
    SDL_Quit();
    return 0;
}
