/**
 * @file background.h
 * @author Mohamed Amine Lbabda
 * @brief Ce fichier représente les différentes fonctions et structures afin d'en intégrer dans le jeu
 * @version 1.0
 * @date 2025-05-01
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#define LARGEURFENETRE 1920
#define HAUTEURFENETRE 1080
#define ECRAN 1
/**
 * @struct background
 * @brief Cette structure représente la structure qu'on a définie afin d'afficher notre background
 *
 */
typedef struct background
{
    SDL_Surface *image; /*<!Image du background*/
    SDL_Rect posimage;  /*<!Représente la position du l'image */
    SDL_Rect poscamera; /*<!Représente la position du caméra qu'elle va suivre le joueur */
    Mix_Music *musique; /*<!Représente la musique du background*/
    // Mix_Chunk *passe_niveau;
} background;
void init_background(background *b, SDL_Surface *e, char nom_fichier[]);

void posbackground(background *b, int x, int y, int w, int h);

void poscam(background *b, int x, int y, int w, int h);

void animate_leaves(SDL_Surface *leaves, SDL_Rect leaves_pos, int world_x, int *bounce_y, int *direction,
                    int bounce_min, int bounce_max, int bounce_speed, int camX, SDL_Surface *screen);
