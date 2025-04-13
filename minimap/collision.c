#include "collision.h"

int boundingBoxCollision(SDL_Rect player, SDL_Rect platform) {
    if (player.x + player.w < platform.x) return 0;
    if (player.x > platform.x + platform.w) return 0;
    if (player.y + player.h < platform.y) return 0;
    if (player.y > platform.y + platform.h) return 0;
    return 1;
}

int perfectPixelCollision(SDL_Surface *player, SDL_Surface *platform, SDL_Rect posPlayer, SDL_Rect posPlatform) {
    int x, y;

    int x1 = posPlayer.x > posPlatform.x ? posPlayer.x : posPlatform.x;
    int y1 = posPlayer.y > posPlatform.y ? posPlayer.y : posPlatform.y;
    int x2 = (posPlayer.x + player->w) < (posPlatform.x + platform->w) ? (posPlayer.x + player->w) : (posPlatform.x + platform->w);
    int y2 = (posPlayer.y + player->h) < (posPlatform.y + platform->h) ? (posPlayer.y + player->h) : (posPlatform.y + platform->h);

    Uint32 *pixelsPlayer = (Uint32 *)player->pixels;
    Uint32 *pixelsPlatform = (Uint32 *)platform->pixels;

    for (y = y1; y < y2; y++) {
        for (x = x1; x < x2; x++) {
            int offsetPlayer = (y - posPlayer.y) * player->w + (x - posPlayer.x);
            int offsetPlatform = (y - posPlatform.y) * platform->w + (x - posPlatform.x);

            Uint32 pColor = pixelsPlayer[offsetPlayer];
            Uint32 platColor = pixelsPlatform[offsetPlatform];

            if ((pColor & 0xFFFFFF) != 0 && (platColor & 0xFFFFFF) != 0) {
                return 1; 
            }
        }
    }

    return 0;
}

void animateBackground(SDL_Surface *background, int *toggle) {
    
    if (*toggle) {
        SDL_FillRect(background, NULL, SDL_MapRGB(background->format, 255, 0, 0)); 
    } else {
        SDL_FillRect(background, NULL, SDL_MapRGB(background->format, 0, 0, 0)); 
    }
    *toggle = !(*toggle);
}
