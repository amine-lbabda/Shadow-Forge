#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <math.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "joueur.h"
int main(int argc,char *argv[]){
SDL_Surface *ecran;
SDL_Event event;
perso p;
char fich[]="sauvegarde.bin";
int quitter=1;
Uint32 t_prev;
Uint32 dt;
Uint32 temps_ecoule;
Uint32 t_now;
Uint32 t_press_start=0;
perso joueurs[2];
int nb_joueurs = 1;
int etat=0;
int right_pressed = 0;
int left_pressed = 0;
t_prev=SDL_GetTicks();

if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_TIMER)!=0){
printf("erreur %s\n",SDL_GetError());
return 1;
}

ecran=SDL_SetVideoMode(1920,1080,32,SDL_SWSURFACE|SDL_DOUBLEBUF);
if(ecran==NULL){
printf("erreur %s\n",SDL_GetError());
SDL_Quit();
return 1;
}
if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
printf("Erreur initialisation audio: %s\n", Mix_GetError());
return 1;
}



init_perso(&p);        
charger_progression(&p,fich);
p.posscreen.x = p.pos.x;
p.posscreen.y = p.pos.y;
p.pos_actuelle_x = p.pos.x;
p.pos_actuelle_y = p.pos.y;
while(quitter){
t_now = SDL_GetTicks();
dt=t_now-t_prev;
t_prev=t_now;
if(dt>50){
dt=50;
}
while(SDL_PollEvent(&event)) {
switch(event.type) {
case SDL_QUIT:
quitter = 0;
break;
case SDL_KEYDOWN:
if(event.key.keysym.sym == SDLK_p && nb_joueurs < 2) {
ajout_autre_joueur(joueurs, &nb_joueurs);
}
if((event.key.keysym.sym == SDLK_RIGHT)||(event.key.keysym.sym == SDLK_d)) {
right_pressed = 1;
p.direction = 1;
if (p.acceleration < 3.0) p.acceleration += 0.15;
if((etat==0)||(etat==1)){
etat=2;
}
if (t_press_start == 0) { 
t_press_start = SDL_GetTicks();  
}
p.temps_presse = SDL_GetTicks();
}
if((event.key.keysym.sym == SDLK_LEFT)||(event.key.keysym.sym == SDLK_a)) {
left_pressed = 1;
p.direction = -1;
if (p.acceleration > -3.0) p.acceleration -= 0.15;
if((etat==0)||(etat==1)){
etat=3;
}

if (t_press_start == 0) { 
t_press_start = SDL_GetTicks();  
}
p.temps_presse = SDL_GetTicks();
}
if((event.key.keysym.sym == SDLK_LSHIFT)||(event.key.keysym.sym == SDLK_RSHIFT)){
p.vitesse_max=p.vitesse_dash;
p.temps_dash=0.5;
p.en_dash=1;
p.dash_start_x = p.pos.x;
}
if((event.key.keysym.sym == SDLK_c )){
if(p.up==0){
p.type_saut = 1;
p.up = 1;
p.posinit_x = p.pos_actuelle_x;
p.posinit_y = p.pos_actuelle_y; 
p.x_rel = 0;
p.frameActuelle = 0; 
p.tempsActuel = SDL_GetTicks();  
p.dernierChangement = p.tempsActuel; 
p.etat_precedent = p.etat_animation; 
}
p.temps_presse = SDL_GetTicks();
if ((etat == 0 )||(etat == 2 )|| (etat == 4)) {  
p.vitesse_y = -300;  
etat = 6; 
} 
else{ 
if ((etat == 1 )||(etat == 3) || (etat == 5)) {  
p.vitesse_y = -300;  
etat = 7;  
}
}
}
if((event.key.keysym.sym == SDLK_SPACE)){
if(p.up==0){
p.type_saut = 0;
p.up = 1;
p.double_saut_dispo=1;
p.vitesse_y = -380;
p.posinit = p.pos_actuelle_y;
if (p.direction != 1 && p.direction != -1) {
p.direction = 1;
}
if (p.direction == 1) {
etat = 6; 
} 
else {
etat = 7; 
}
p.temps_presse = SDL_GetTicks();
}
else{
if(p.double_saut_dispo==1 && p.vitesse_y > -300){
p.vitesse_y=-380;
p.double_saut_dispo=0;
p.posinit = p.pos_actuelle_y;
p.temps_presse = SDL_GetTicks();
if (p.direction == 1) {
etat = 6;
} 
else {
etat = 7;
}
}
}
p.temps_presse = SDL_GetTicks();
}

if (event.key.keysym.sym == SDLK_e) {
if(p.direction==1){
if ((etat == 2) || (etat == 4)||(etat == 0)||(etat == 6)) {  
etat = 8;  
}
}
else{
if ((etat == 3) || (etat == 5)||(etat == 1)||(etat == 7)) {
etat = 9;
}
}
}
break;
case SDL_KEYUP:
if ((event.key.keysym.sym == SDLK_RIGHT) || (event.key.keysym.sym == SDLK_d)) {
right_pressed = 0;
if ((etat == 2) || (etat == 4)){
etat =0;
}
}
if ((event.key.keysym.sym == SDLK_LEFT) || (event.key.keysym.sym == SDLK_a)) {
left_pressed = 0;
if ((etat == 3) || (etat == 5)){
etat = 1;
}
}
break;
}
if (event.key.keysym.sym == SDLK_SPACE) {

}

break;            
}

if (t_press_start != 0) {
temps_ecoule = SDL_GetTicks() - t_press_start;
if (temps_ecoule > 1500) {  
if (etat == 2) {  
etat = 4;  
} 
else{
if (etat == 3) { 
etat = 5;  
}
}
}
}

if(p.temps_presse >0){
temps_ecoule = SDL_GetTicks() - p.temps_presse;
if((temps_ecoule>1000)&&(p.acceleration<0.2)){
p.acceleration+=0.001;
}
}
if (right_pressed) {
if (p.acceleration < 0.5)
p.acceleration += 0.01;
}
else if (left_pressed) {
if (p.acceleration > -0.5)
p.acceleration -= 0.01;
}
else {
if(!right_pressed && !left_pressed)
p.acceleration = 0;
}
if (right_pressed && left_pressed) {
p.direction = 0;
p.acceleration = 0;     
p.vitesse *= 0.8;   
} else
if (right_pressed) {
p.direction = 1;
} else
if (left_pressed) {
p.direction = -1;
}
if (etat == 8 || etat == 9) {
printf("Attaque en cours... on ne change pas l'état !\n");
} 
else {
if (right_pressed && (etat == 0 || etat == 1)) 
etat = 2;
else 
if (left_pressed && (etat == 0 || etat == 1)) etat = 3;
}
animer(&p,etat);
if ((etat == 8 || etat == 9) && p.frameActuelle >= 7) {
if (p.direction == 1) {
etat = 0;
}
else 
if (p.direction == -1) {
etat = 1;
}
}
if (etat == 8 || etat == 9) {
p.vitesse = 0;
p.acceleration = 0;
}
deplacer(&p,dt);
printf("x logique = %d | x affiché = %d\n", p.pos.x, p.posscreen.x);

sauter(&p, dt);
if ((etat == 6 || etat == 7) && p.up == 0 ) {
if (p.direction == 1) {
etat = 0; 
}
else {
etat = 1; 
}
}
if (p.up == 0 && p.type_saut == 1) {
p.pos.x = (int)p.pos_actuelle_x; 
p.pos.y = (int)p.pos_actuelle_y;
p.posscreen.x = p.pos.x;
p.posscreen.y = p.pos.y;
p.type_saut = 0; 
}
if (p.up == 0) {
p.double_saut_dispo = 1;
}
SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
afficher_perso(&p, ecran);
SDL_Flip(ecran);
}

liberation(&p);
TTF_Quit();
Mix_CloseAudio();
Mix_Quit();
IMG_Quit();
SDL_Quit();
SDL_Delay(16);
return 0;
}





