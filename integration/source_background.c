/**
 * @file source_background.c
 * @author MMohamed Amine Lbabda
 * @brief Ce fichier représente les implémentations des fonctions définies dans background.h
 * @version 1.0
 * @date 2025-05-01
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "background.h"
#include "joueur.h"
/**
 * @brief Cette procédure va initialiser les champs de notre background
 *
 * @param b  un pointeur sur le background
 * @param e représente la fenêtre du notre écran
 * @param nom_fichier le chemin du notre background
 * @return rien
 */
void init_background(background *b, SDL_Surface *e, char nom_fichier[])
{
    b->image = IMG_Load(nom_fichier);
    if (b->image == NULL)
    {
        printf("Erreur:%s", IMG_GetError());
    }
    else
    {
        poscam(b, 0, 0, LARGEURFENETRE / ECRAN, HAUTEURFENETRE / ECRAN);
        posbackground(b, 0, 0, e->w, e->h);
    }
}
/**
 * @brief Initialiser les position du notre background
 * @param b un pointeur sur le background
 * @param x représente son position selon l'axe des abscisses
 * @param y représente son position selon l'axe des oordonnées
 * @param w représente la largeur du background
 * @param h représente la hauteur du background
 * @remark Cette fonction restera toujours privé, Cela veut dire qu'elle ne sera jamais exposé dans notre gameloop
 */
void posbackground(background *b, int x, int y, int w, int h)
{
    b->posimage.x = x;
    b->posimage.y = y;
    b->posimage.w = w;
    b->posimage.h = h;
}
/**
 * @brief Initialiser les positions du caméra
 *
 * @param b un pointeur sur le background
 * @param x représente son position selon l'axe des abscisses
 * @param y représente son position selon l'axe des oordonnées
 * @param w représente la largeur du background
 * @param h représente la hauteur du background
 * @remark Cette fonction restere toujours privé, Cela veut dire qu'elle ne sera jamais exposé dans notre gameloop
 */
void poscam(background *b, int x, int y, int w, int h)
{
    b->poscamera.x = x;
    b->poscamera.y = y;
    b->poscamera.w = w;
    b->poscamera.h = h;
}
/**
 * @brief Cette fonction va animer les feuilles verticalement
 *
 * @param leaves l'image des feuilles
 * @param leaves_pos position initiale des feuilles
 * @param world_x position dans le monde réelle du jeu (Coordonnées dans photoshop) selon l'axe des abscisses
 * @param bounce_y  position dans le monde réelle du jeu (Coordonnées dans photoshop) selon l'axe des ordonnées
 * @param direction direction des feuilles (1 pour haut et -1 pour la bas)
 * @param bounce_min représente la limite minimale du bouncing
 * @param bounce_max  représente la limite maximale du bouncing
 * @param bounce_speed représente la vitesse du mouvement
 * @param camX représente la position du caméra
 * @param screen représente l'écran
 * @return rien
 *
 */
void animate_leaves(SDL_Surface *leaves, SDL_Rect leaves_pos, int world_x, int *bounce_y, int *direction,
                    int bounce_min, int bounce_max, int bounce_speed, int camX, SDL_Surface *screen)
{
    *bounce_y += (*direction) * bounce_speed;
    if (*bounce_y > bounce_max)
    {
        *bounce_y = bounce_max;
        *direction = -1;
    }
    else if (*bounce_y < bounce_min)
    {
        *bounce_y = bounce_min;
        *direction = 1;
    }
    SDL_Rect leaves_screen_pos = leaves_pos;
    leaves_screen_pos.x = world_x - camX;
    leaves_screen_pos.y = leaves_pos.y - (*bounce_y);
    SDL_BlitSurface(leaves, NULL, screen, &leaves_screen_pos);
}