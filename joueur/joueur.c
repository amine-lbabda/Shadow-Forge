#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <math.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "joueur.h"
void init_perso(perso *p){
p->sprite_player=IMG_Load("rika.png");
if(p->sprite_player==NULL){
printf("erreur %s\n",IMG_GetError());
SDL_Quit();
}
p->nbc=8;
p->nbl=10;
p->pos.x = 0;
p->pos.y = 0;
p->pos.w = 131; 
p->pos.h = 188;
p->posscreen.x = 0;
p->posscreen.y = 0;
p->possprite.x=0;
p->possprite.y=0;
p->possprite.w=p->sprite_player->w/p->nbc;
p->possprite.h=p->sprite_player->h/p->nbl;
p->coeurs_pleins=5;
p->coeur_partiel=0;
p->score=0;
p->high_score=0;
p->acceleration=0;
p->vitesse=0;
p->vitesse_normale=150;
p->vitesse_max=p->vitesse_normale;
p->vitesse_dash=250;
p->duree_dash=0.1;
p->temps_dash=0;
p->en_dash=0;
p->x_rel = 0;
p->y_rel = 0;
p->type_saut = 0;
p->vitesse_x = 0;
p->vitesse_y = 0;
p->surface_actuelle=0;
p->gravite = 1100;
p->posinit = 0;
p->direction = 1;
p->joueur = 1;
p->up = 0;
p->double_saut_dispo = 1;
p->temps_presse = 0;
p-> frameActuelle = 0;
p->etat_animation = 0;
p->dernierChangement = 0;
p->tempsActuel=0;
p->tempsEntreFrames=100;
p->frameMax=8;
p->nb_joueur=1;
p->pos_actuelle_x = p->pos.x;  
p->pos_actuelle_y = p->pos.y; 
p->dash_start_x=0;
p->distance_dash = 80;
p->distance_parcourue= 0;
}
void animer(perso *p, int etat) {
p->tempsActuel = SDL_GetTicks(); 
if (p->etat_animation != etat) {
p->possprite.x = 0;
p->frameActuelle = 0;
p->etat_animation = etat;
p->dernierChangement = p->tempsActuel;
}
switch (etat) {
case 0:
p->possprite.y = 0 * p->possprite.h;
break;
case 1:
p->possprite.y = 1 * p->possprite.h;
break;
case 2:
p->possprite.y = 2 * p->possprite.h;
break;
case 3:
p->possprite.y = 3 * p->possprite.h;
break;
case 4:
p->possprite.y = 4 * p->possprite.h;
break;
case 5:
p->possprite.y = 5 * p->possprite.h;
break;
case 6:
p->possprite.y = 6 * p->possprite.h;
break;
case 7:
p->possprite.y = 7 * p->possprite.h;
break;
case 8:
p->possprite.y = 8 * p->possprite.h;
break;
case 9:
p->possprite.y = 9 * p->possprite.h;
break;
}
if (p->tempsActuel - p->dernierChangement >= p->tempsEntreFrames) {
if (p->frameActuelle + 1 >= p->frameMax) {
p->possprite.x = 0;
p->frameActuelle = 0;
}
else {
p->possprite.x += p->possprite.w;
p->frameActuelle++;
}
p->dernierChangement = p->tempsActuel;
}
if((etat==8)||(etat==9)){
p->tempsEntreFrames = 150; 
}
else{
p->tempsEntreFrames = 100;
}
}
void deplacer(perso *p, Uint32 dt) {
double dt_sec = (double)dt / 1000.0;
double dx;
double vitesse_effective;
double dash_speed;
int left_bound;
int right_bound;

p->vitesse += p->acceleration * dt_sec * 15;
if (p->acceleration == 0) {
if (p->vitesse > 0.01) {
p->vitesse -= 0.05;
if (p->vitesse < 0) p->vitesse = 0;
} 
else 
if (p->vitesse < -0.01) {
p->vitesse += 0.05;
if (p->vitesse > 0) 
p->vitesse = 0;
}
}    
if (p->vitesse > p->vitesse_max) {
p->vitesse = p->vitesse_max;
} else
if (p->vitesse < -p->vitesse_max) {
p->vitesse = -p->vitesse_max;
}   
if (p->acceleration == 0) {
p->vitesse *= 0.8; 
if (fabs(p->vitesse) < 0.5) 
p->vitesse = 0;
}
vitesse_effective = fabs(p->vitesse);
if (p->direction == -1)
vitesse_effective *= -1;
dx = vitesse_effective * dt_sec * 100;
if (p->en_dash) {
dash_speed = p->vitesse_dash * p->direction;
dx = dash_speed * dt_sec * 100;
p->distance_parcourue += fabs(dx);
if (p->distance_parcourue >= p->distance_dash) {
p->en_dash = 0;
p->vitesse_max = p->vitesse_normale;
p->distance_parcourue = 0;
}
} 
else {
p->distance_parcourue = 0; 
}
p->pos.x += (int)dx;
p->pos_actuelle_x = p->pos.x;
p->posscreen.x = p->pos.x;
if (p->pos.x < 0) 
p->pos.x = 0;
else 
if (p->pos.x > 1920 - p->pos.w) p->pos.x = 1920 - p->pos.w;

printf("Accel: %.2f, Vitesse: %.2f, Dir: %d, PosX: %d\n",p->acceleration, p->vitesse, p->direction, p->pos.x);
if (p->en_dash) 
printf(" DASH ACTIVÉ | vitesse = %.2f\n", p->vitesse);

}

void sauter(perso *p, Uint32 dt){
double seuil=250;
double dt_sec=dt/1000.0;
static Mix_Chunk *saut_son;
if (p->up == 0) {
p->pos_actuelle_x = p->pos.x;
p->pos_actuelle_y = p->pos.y;
p->posscreen.x = p->pos.x;
p->posscreen.y = p->pos.y;
return;
}
if(p->up==1){
p->tempsActuel = SDL_GetTicks();
if(saut_son == NULL) {
saut_son = Mix_LoadWAV("saut.wav");
if(!saut_son) {
printf("Erreur chargement son: %s\n", Mix_GetError());
}
} 
if(p->type_saut==0){
if(p->vitesse_y == 0) {
p->vitesse_y = -400;
if(p->vitesse_y == 0 || (p->type_saut == 0 && p->double_saut_dispo == 1)) {
if(saut_son) {
Mix_PlayChannel(-1, saut_son, 0);
}
}
}
p->pos_actuelle_y += p->vitesse_y * dt_sec;
p->vitesse_y += p->gravite * dt_sec;
p->posscreen.y = (int)(p->pos_actuelle_y);
printf("Y=%.2f  vitesse_y=%.2f  up=%d\n", p->pos_actuelle_y, (double)p->vitesse_y, p->up);

if (p->collision_plateforme && p->vitesse_y > 0 && p->pos_actuelle_y >= p->hauteur_collision) {
p->pos_actuelle_y = p->hauteur_collision;
p->posscreen.y = p->hauteur_collision;
p->posinit = p->hauteur_collision;
p->vitesse_y = 0;
p->up = 0;
p->double_saut_dispo = 1;
return;
}

if(p->pos_actuelle_y <= p->posinit - 300){
p->pos_actuelle_y = p->posinit - 300;
p->vitesse_y=0;
}
if (p->pos_actuelle_y >= p->posinit) {
p->pos_actuelle_y = p->posinit;
p->up = 0;  
p->vitesse_y = 0; 
p->double_saut_dispo=1; 
}
}
else{
p->tempsActuel = SDL_GetTicks();
if (p->tempsActuel - p->dernierChangement >= p->tempsEntreFrames) {
p->frameActuelle++;
printf("frameActuelle = %d\n", p->frameActuelle);
p->dernierChangement = p->tempsActuel;
}
if (p->frameActuelle < 8) {
p->x_rel += 80 * dt_sec;
p->y_rel = -0.0025 * p->x_rel * p->x_rel + 120;
if (p->y_rel <= 0) {
p->y_rel = 0;
}

p->pos_actuelle_x= p->posinit_x + (int)p->x_rel * p->direction;
p->pos_actuelle_y= p->posinit_y - (int)p->y_rel;
}
else{
p->pos_actuelle_y>= p->posinit_y;
p->up = 0;
p->x_rel = 0;
p->y_rel = 0;
p->frameActuelle = 0;
}
if (p->collision_plateforme && p->pos_actuelle_y >= p->hauteur_collision) {
p->pos_actuelle_y = p->hauteur_collision;
p->posscreen.y = p->hauteur_collision;
p->posinit = p->hauteur_collision;
p->up = 0;
p->x_rel = 0;
p->y_rel = 0;
p->frameActuelle = 0;
}
if ((p->pos_actuelle_y>= p->posinit_y)||(p->frameActuelle >= 8 )) {
p->pos_actuelle_y = p->posinit_y;
p->posscreen.y = p->pos_actuelle_y;  
p->posscreen.x = p->pos.x;  
p->up = 0;
p->x_rel = 0;
p->y_rel = 0;
p->frameActuelle = 0;
if (p->direction == 1) {    
p->etat_animation = 0;     
} 
else{
p->etat_animation = 1;       

}
}
}
}
p->posscreen.x = (int)p->pos_actuelle_x;
p->posscreen.y = (int)p->pos_actuelle_y;
}

void gagner_vie(perso *p){
int nb_max_coeurs=5;
int max_coeurs=7;
float gain_max;
float gain_min;
gain_max=0.1;
gain_min=0.4;
if(p->coeurs_pleins<nb_max_coeurs){
p->coeur_partiel+=gain_max;
}
else{
p->coeur_partiel+=gain_min;
if(p->coeur_partiel>=1){
p->coeurs_pleins++;
if (p->coeurs_pleins > max_coeurs) {
p->coeurs_pleins = max_coeurs;
p->coeur_partiel = 0;
}
}
}
}

void perdre_vie(perso *p) {
if (p->coeur_partiel > 0) {
p->coeur_partiel -= 0.25;
if (p->coeur_partiel < 0) {
p->coeurs_pleins--;
p->coeur_partiel = 1 - p->coeur_partiel; 
}
} 
else{ 
if (p->coeurs_pleins > 0) {
p->coeurs_pleins--;
p->coeur_partiel = 0.75 ;
}
}
if (p->coeurs_pleins < 0) {
p->coeurs_pleins = 0;
p->coeur_partiel = 0;
}
}

void ajouter_score(perso *p, int points) {
p->score += points;
if (p->score > p->high_score) {
p->high_score = p->score;
}
}
void ajouter_argent(perso *p, int montant) {
p->argent += montant;
if (p->argent < 0) 
p->argent = 0; 
}

void sauvegarder_progression(perso *p,char fich[]) {
FILE *f = fopen(fich, "wb");
if (f==NULL){
printf("impossible\n");
}
else{
fwrite(p, sizeof(perso), 1, f);
fclose(f); 
}   
}

void charger_progression(perso *p,char fich[]) {
FILE *f = fopen(fich, "rb");
if (f==NULL){
printf("impossible\n");
}
else{
fread(p, sizeof(perso), 1, f);
fclose(f);
}
}

void reinitialiser_score(perso *p) {
p->score = 0;
p->argent = 0; 
}
void afficher_perso(perso *p,SDL_Surface *ecran){
SDL_BlitSurface(p->sprite_player, &p->possprite, ecran, &p->posscreen);
}
void liberation(perso *p){
static Mix_Chunk *saut_son;
SDL_FreeSurface(p->sprite_player);
if(saut_son) {
Mix_FreeChunk(saut_son);
saut_son = NULL;
}
}


void ajout_autre_joueur(perso *joueurs,int *nb_joueurs) {
if (*nb_joueurs >= 2) {
printf("Nombre maximum de joueurs atteint.\n");
return;
}
init_perso(&joueurs[1]);
joueurs[1].nb_joueur = 2;
joueurs[1].pos.x = 300; 
joueurs[1].direction = -1; 
(*nb_joueurs)++;
printf("Deuxième joueur ajouté avec succès !\n");
}
    
    
