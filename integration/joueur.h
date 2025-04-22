#pragma once
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include "background.h"
#include <math.h>
typedef struct perso
{
    SDL_Surface *sprite_player;
    SDL_Rect pos;
    SDL_Rect posscreen;
    SDL_Rect possprite;
    int coeurs_pleins;
    float coeur_partiel;
    int score;
    int high_score;
    int vitesse_max;
    double vitesse;
    double vitesse_normale;
    double vitesse_dash;
    double duree_dash;
    double temps_dash;
    double acceleration;
    double x_rel;
    double y_rel;
    int type_saut;
    int vitesse_x;
    int vitesse_y;
    int en_dash;
    int gravite;
    int posinit;
    int direction;
    int joueur;
    int up;
    int double_saut_dispo;
    int surface_actuelle;
    Uint32 temps_presse;
    int frameActuelle;
    int etat_animation;
    Uint32 dernierChangement;
    Uint32 tempsActuel;
    Uint32 tempsEntreFrames;
    int frameMax;
    int nbc;
    int nbl;
    int nb_joueur;
    int argent;
    int posinit_x;
    int posinit_y;
    int etat_precedent;
    double pos_actuelle_x;
    double pos_actuelle_y;
    int dash_start_x;
    double distance_dash;
    double distance_parcourue;
    int collision_plateforme;
    int hauteur_collision;
} perso;

void init_perso(perso *p);
void gagner_vie(perso *p);
void perdre_vie(perso *p);
void ajouter_score(perso *p, int points);
void ajouter_argent(perso *p, int montant);
void sauvegarder_progression(perso *p, char fich[]);
void charger_progression(perso *p, char fich[]);
void reinitialiser_score(perso *p);
void afficher_perso(perso *p, SDL_Surface *ecran);
void deplacer(perso *p, Uint32 dt);
void sauter(perso *p, Uint32 dt);
void animer(perso *p, int etat);
void ajout_autre_joueur(perso *j, int *nb_joueurs);
void liberation(perso *p);
