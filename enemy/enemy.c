    #include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include "enemy.h"
void init_enemy(Enemy *e, SDL_Surface *sprite, SDL_Surface *sprite_phase2, int has_phase2) {
    e->sprite = sprite;
    e->sprite_phase2 = sprite_phase2;
    e->has_phase2 = has_phase2;
    e->etat_anim = 0;
    e->current_frame = 0;
    e->max_frames = 8;
    e->time_now = SDL_GetTicks();
    e->last_frame_time = e->time_now;
    e->frame_interval = 100;
    e->pos.x = 1200;
    e->pos.y = 400;
    e->pos.w = 267;  
    e->pos.h = 250;
    e->possprite.w = e->pos.w;
    e->last_target_time = SDL_GetTicks();
    e->current_target = 1;
    e->vitesse = 1;
e->possprite.h = e->pos.h;

}
void animate_enemy(Enemy *e) {
    e->time_now = SDL_GetTicks();

    static int last_state = -1;
    if (e->etat_anim != last_state) {
        e->possprite.x = 0;
        e->current_frame = 0;
        last_state = e->etat_anim;
        e->last_frame_time = e->time_now;
    }


    e->possprite.y = e->etat_anim * e->possprite.h;

    switch (e->etat_anim) {
        case 0: e->frame_interval = 150; break;
        case 1: e->frame_interval = 100; break;
        case 2: e->frame_interval = 70;  break;
        default: e->frame_interval = 100; break;
    }


    if (e->time_now - e->last_frame_time >= e->frame_interval) {
        e->current_frame++;
        if (e->current_frame >= e->max_frames) {
            e->current_frame = 0;
        }
        e->possprite.x = e->current_frame * e->possprite.w;
        e->last_frame_time = e->time_now;
    }


    e->possprite.y = e->etat_anim * e->possprite.h;
}

void update_enemy(Enemy *e, SDL_Rect target) {
    if (e->has_phase2 && e->hp <= 50 && e->phase == 1) {
        e->phase = 2;
        if (e->sprite_phase2 != NULL) {
            e->sprite = e->sprite_phase2;
        }
        e->damage += 5;
    }

    Uint32 now = SDL_GetTicks();
    if (now - e->last_target_time >= 2000) {
        e->current_target = !e->current_target;
        e->last_target_time = now;
    }
    
  
    if (e->current_target == 1) {
        target.x = 1900;
    } else {
        target.x = 800;
    }
    target.y = e->pos.y;
    target.w = 100;
    target.h = 100;
    
    
    if (e->pos.x < target.x) {
        e->direction = 0; 
    } else {
        e->direction = 1; 
    }
  
    if (!check_collision(e->pos, target)) {
        switch (e->direction) {
            case 0:
                e->pos.x += e->vitesse;
                e->etat_anim = 0; 
                break;
            case 1:
                e->pos.x -= e->vitesse;
                e->etat_anim = 1; 
                break;
        }
    } else {
       
        switch (e->direction) {
            case 0: e->etat_anim = 2; break;
            case 1: e->etat_anim = 3; break; 
        }
    }
    e->posscreen.x = e->pos.x;
    e->posscreen.y = e->pos.y;
}

//void interaction(Enemy *e, perso *p) {
  //  Uint32 now = SDL_GetTicks();

   // if (check_collision(e->pos, p->pos)) {
        // range rika
     //   SDL_Rect player_hitbox = p->pos;
      //  if (p->direction == 0) {
      //      player_hitbox.x += 40;
      //  } else {
     //       player_hitbox.x -= 40;
     //   }
      //  player_hitbox.w += 20;
//
      //  if (check_collision(player_hitbox, e->pos)) {
       //     e->hp -= 10;
     //       e->etat_anim = 1;
        //    if (p->direction == 0)
       //         e->pos.x += 20;
        //    else
       //         e->pos.x -= 20;
      //  }

    //    if ((e->etat_anim == 2 || e->etat_anim == 3) && (now - e->last_hit_time >= 500)) {
      //      perdre_vie(p);
     //       e->last_hit_time = now;
  //      }
   // }
//}

int heal(SDL_Rect player, SDL_Rect *pack, int *visible, int *player_hp) {
    if (*visible && check_collision(player, *pack)) {
        *player_hp += 20;
        if (*player_hp > 100) *player_hp = 100;
        *visible = 0;
        printf("Health pack collected! Player HP: %d\n", *player_hp);
        return 1; 
    }
    return 0;
}


int check_collision(SDL_Rect a, SDL_Rect b) {
    if ((a.x + a.w < b.x) || (a.x > b.x + b.w) ||
        (a.y + a.h < b.y) || (a.y > b.y + b.h)) {
        return 0;
    } else {
        return 1;
    }

}


void liberer_enemy(Enemy *e) {
    if (e->sprite != NULL) {
        SDL_FreeSurface(e->sprite);
        e->sprite = NULL;
    }
    if (e->sprite_phase2 != NULL) {
        SDL_FreeSurface(e->sprite_phase2);
        e->sprite_phase2 = NULL;
    }
}