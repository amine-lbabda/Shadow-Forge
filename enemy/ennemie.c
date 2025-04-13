#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include "enemy.h"

int main(int argc, char *argv[]) {
    int quitter=1;
    Enemy sengo,ghost;
    SDL_Event event;
    SDL_Surface *screen;
    SDL_Surface *mob_sprite = IMG_Load("sengo.png");
    SDL_Surface *boss_sprite = IMG_Load("sengo.png");
    SDL_Surface *boss_sprite2 = IMG_Load("sengo.png");

    SDL_Rect health_pack = {900, 500, 0, 0};
int pack_visible = 1;
int player_hp = 50;  

if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_TIMER)!=0){
    printf("erreur %s\n",SDL_GetError());
    return 1;
    } 
    screen=SDL_SetVideoMode(1920, 1080, 32, SDL_SWSURFACE | SDL_DOUBLEBUF);
if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
  printf("Audio init failed: %s\n", Mix_GetError());
    }
    Mix_Chunk *heal_sound = Mix_LoadWAV("heal.wav");
    if (!heal_sound) {
        printf("Failed to load heal.wav: %s\n", Mix_GetError());
    }
    

    sengo.pos.x = 500;
    sengo.pos.y = 500;

    init_enemy(&sengo, boss_sprite, boss_sprite2, 1);
sengo.posscreen.x = sengo.pos.x;
sengo.posscreen.y = sengo.pos.y;


SDL_Rect target = {1800, 500, 100, 100};
SDL_Rect fake_player = {1600, 500, 100, 100};
SDL_Surface *health_img = IMG_Load("health.png");
if (!health_img) {
    printf("Failed to load health.png: %s\n", IMG_GetError());
}
if (health_img) {
    health_pack.w = health_img->w;
    health_pack.h = health_img->h;
}


    while (quitter) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
            quitter = 0;
            }
        }
        update_enemy(&sengo, target);
        animate_enemy(&sengo);
    //   interaction(&sengo, fake_player);
    if(heal(sengo.pos, &health_pack, &pack_visible, &player_hp)){
        Mix_PlayChannel(-1, heal_sound, 0);
    };
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
    if (pack_visible) {
        SDL_BlitSurface(health_img, NULL, screen, &health_pack);
         }
   
    SDL_BlitSurface(sengo.sprite, &sengo.possprite, screen, &sengo.posscreen);
    SDL_Flip(screen);
}
    liberer_enemy(&sengo);
    SDL_FreeSurface(health_img);
    Mix_FreeChunk(heal_sound);
    Mix_CloseAudio();
    IMG_Quit();
    SDL_Quit();
    return 0;

}