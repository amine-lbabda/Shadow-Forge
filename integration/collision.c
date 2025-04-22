#include "collision.h"

int boundingBoxCollision(SDL_Rect player, SDL_Rect platform) {
    if (player.x + player.w < platform.x) return 0;
    if (player.x > platform.x + platform.w) return 0;
    if (player.y + player.h < platform.y) return 0;
    if (player.y > platform.y + platform.h) return 0;
    return 1;
}
SDL_Color GetPixel(SDL_Surface *pSurface, int x, int y) {
    SDL_Color color;
    Uint32 col = 0;

    char* pPosition = (char*) pSurface->pixels;
    pPosition += (pSurface->pitch * y);
    pPosition += (pSurface->format->BytesPerPixel * x);

    memcpy(&col, pPosition, pSurface->format->BytesPerPixel);
    SDL_GetRGB(col, pSurface->format, &color.r, &color.g, &color.b);

    return color;
}

int perfectPixelCollision(SDL_Surface *mask, SDL_Rect posPlayer) {
    SDL_Color color;
    int x = posPlayer.x;
    int y = posPlayer.y;
    int w = posPlayer.w;
    int h = posPlayer.h;

    int points[8][2] = {
        {x, y},                    
        {x + w / 2, y},             
        {x + w, y},                 
        {x, y + h / 2},             
        {x, y + h},                 
        {x + w / 2, y + h},         
        {x + w, y + h},             
        {x + w, y + h / 2}          
    };

    for (int i = 0; i < 8; i++) {
        int px = points[i][0];
        int py = points[i][1];

        // Vérifie que le point est dans les limites de l'image
        if (px >= 0 && px < mask->w && py >= 0 && py < mask->h) {
            SDL_Color c = GetPixel(mask, px, py);
            // Vérifie collision avec pixel noir (obstacle)
            if (c.r == 0 && c.g == 0 && c.b == 0) {
                return 1; // Collision détectée
            }
        }
    }

    return 0; // Pas de collision
}

void animateBackground(SDL_Surface *background, int *toggle) {
    
    if (*toggle) {
        SDL_FillRect(background, NULL, SDL_MapRGB(background->format, 255, 0, 0)); 
    } else {
        SDL_FillRect(background, NULL, SDL_MapRGB(background->format, 0, 0, 0)); 
    }
    *toggle = !(*toggle);
}
