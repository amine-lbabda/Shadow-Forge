#ifndef ENEMY_H
#define ENEMY_H

#include <SDL/SDL.h>

typedef struct {
    SDL_Surface *sprite;
    SDL_Surface *sprite_phase2;

    SDL_Rect pos;
    SDL_Rect posscreen;
    SDL_Rect possprite;

    int direction;
    double vitesse;

    int comportement;

    int etat_anim;
    int current_frame;
    int max_frames;
    Uint32 time_now;
    Uint32 last_frame_time;
    Uint32 frame_interval;
    Uint32 last_target_time;
    Uint32 last_hit_time;
    int current_target;
    int hp;
    int etat_hp;
    int phase;
    int damage;
    int has_phase2;

    int collided;

} Enemy;

void init_enemy(Enemy *e, SDL_Surface *sprite, SDL_Surface *sprite_phase2, int has_phase2);
void update_enemy(Enemy *e,SDL_Rect pos_joueur); 
void animate_enemy(Enemy *e);
void liberer_enemy(Enemy *e);
int check_collision(SDL_Rect a, SDL_Rect b);
void interaction(Enemy *e, SDL_Rect pos_joueur);
int heal(SDL_Rect player, SDL_Rect *pack, int *visible, int *player_hp);


#endif
