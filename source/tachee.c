#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "tache.h"
#include "save.h"
void start_tache(SDL_Surface *ecran, int *run, int *initial_menu){

SDL_Event event;
joueur s;
int quitter=1;
int indice=0;
char c;
int len;
Uint32 last_cursor_time = SDL_GetTicks();
int show_cursor = 1;

SDL_EnableUNICODE(1);



mode_init_menu(&s);
s.joueur_actif = 1;
while(quitter){
switch (indice){
case 0:
mode_afficher_sous_menu(s, ecran);
while(SDL_PollEvent(&event)) {
switch(event.type) {
case SDL_QUIT:
quitter = 0;
break;
case SDL_MOUSEBUTTONDOWN:
if(event.button.button == SDL_BUTTON_LEFT) {
mode_miseajour_sous_menu(&s);
if (s.btn_select == 5) { 
 quitter = 0;
 return;
 
}
if(s.btn_select == 8) {
indice = 1;
s.selected_input = 0;
s.selected_character = 0;
s.saisie_active = 0;
strcpy(s.nom_joueur, "");
s.joueur_actif = 1;
}
if(s.btn_select == 9) {
indice= 2;
s.selected_input = 0;
s.selected_character = 0;
s.saisie_active = 0;
strcpy(s.nom_joueur, "");
s.joueur_actif = 1;
}
}
break;
}
}
break;
case 1:
if (SDL_GetTicks() - last_cursor_time > 500) {
show_cursor = !show_cursor;
last_cursor_time = SDL_GetTicks();
}
mode_afficher_menu(s, ecran,show_cursor);
while(SDL_PollEvent(&event)) {
switch(event.type) {
case SDL_QUIT:
quitter = 0;
break;
case SDL_MOUSEBUTTONDOWN:
if(event.button.button == SDL_BUTTON_LEFT) {
mode_miseajour(&s);
if (s.btn_select == 5) { 
indice = 0; 

}
if(s.btn_select == 1) {
s.selected_input = 1;
}
if(s.btn_select == 2) {
s.selected_input = 2;
}
if(s.btn_select == 3) {
s.selected_character = 1;
}
if(s.btn_select == 4) {
s.selected_character = 2;
}
if(s.btn_select == 5) {
indice = 0;
}
if(s.btn_select == 6) {

}
if(s.btn_select == 7) {
}
if (mode_collisionsouris(s.pos_zone)) {
s.saisie_active = 1; 
} else {
s.saisie_active = 0; 
}

}
break;
case SDL_KEYDOWN:
if (s.saisie_active) {
if (event.key.keysym.sym == SDLK_BACKSPACE && strlen(s.nom_joueur) > 0) {
s.nom_joueur[strlen(s.nom_joueur) - 1] = '\0';
} else {
if (strlen(s.nom_joueur) < sizeof(s.nom_joueur) - 1) {
c = event.key.keysym.unicode;
if (c >= 32 && c <= 126) { 
len = strlen(s.nom_joueur);
s.nom_joueur[len] = c;
s.nom_joueur[len + 1] = '\0';
}
}
}
}

break;

}
}
break;
case 2:
if (SDL_GetTicks() - last_cursor_time > 500) {
show_cursor = !show_cursor;
last_cursor_time = SDL_GetTicks();
}
mode_afficher_menu(s, ecran, show_cursor);
while (SDL_PollEvent(&event)) {
if (event.type == SDL_QUIT)
quitter = 0;
else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
mode_miseajour(&s);
if (s.btn_select == 5 ) {
indice = 0;
} else if (s.btn_select == 6) { 
if (s.joueur_actif == 1) {
s.joueur_actif = 2;
s.selected_input = 0;
s.selected_character = 0;
s.saisie_active = 0;
strcpy(s.nom_joueur, "");
indice=3;
} else {
 
}
} else if (s.btn_select == 1) {
s.selected_input = 1;
} else if (s.btn_select == 2) {
s.selected_input = 2;
} else if (s.btn_select == 3) {
s.selected_character = 1;
} else if (s.btn_select == 4) {
s.selected_character = 2;
}
if (mode_collisionsouris(s.pos_zone)) {
s.saisie_active = 1;
} else {
s.saisie_active = 0;
}
} else if (event.type == SDL_KEYDOWN && s.saisie_active) {
if (event.key.keysym.sym == SDLK_BACKSPACE && strlen(s.nom_joueur) > 0) {
s.nom_joueur[strlen(s.nom_joueur) - 1] = '\0';
} else if (strlen(s.nom_joueur) < sizeof(s.nom_joueur) - 1) {
c = event.key.keysym.unicode;
if (c >= 32 && c <= 126) {
len = strlen(s.nom_joueur);
s.nom_joueur[len] = c;
s.nom_joueur[len + 1] = '\0';
}
}
break;
}
}
break;


case 3:
if (SDL_GetTicks() - last_cursor_time > 500) {
show_cursor = !show_cursor;
last_cursor_time = SDL_GetTicks();
}
mode_afficher_menu(s, ecran,show_cursor);
while(SDL_PollEvent(&event)) {
switch(event.type) {
case SDL_QUIT:
quitter = 0;
break;
case SDL_MOUSEBUTTONDOWN:
if(event.button.button == SDL_BUTTON_LEFT) {
mode_miseajour(&s);
if (s.btn_select == 5) { 
indice = 0; 

}
if(s.btn_select == 1) {
s.selected_input = 1;
}
if(s.btn_select == 2) {
s.selected_input = 2;
}
if(s.btn_select == 3) {
s.selected_character = 1;
}
if(s.btn_select == 4) {
s.selected_character = 2;
}
if(s.btn_select == 5) {
indice = 0;
}
if(s.btn_select == 6) {

}
if(s.btn_select == 7) {
}
if (mode_collisionsouris(s.pos_zone)) {
s.saisie_active = 1; 
} else {
s.saisie_active = 0; 
}

}
break;
case SDL_KEYDOWN:
if (s.saisie_active) {
if (event.key.keysym.sym == SDLK_BACKSPACE && strlen(s.nom_joueur) > 0) {
s.nom_joueur[strlen(s.nom_joueur) - 1] = '\0';
} else {
if (strlen(s.nom_joueur) < sizeof(s.nom_joueur) - 1) {
c = event.key.keysym.unicode;
if (c >= 32 && c <= 126) { 
len = strlen(s.nom_joueur);
s.nom_joueur[len] = c;
s.nom_joueur[len + 1] = '\0';
}
}
}
}
break;

}
}
break;
}
SDL_Flip(ecran);

}
mode_liberer_save(&s);
SDL_FreeSurface(ecran);
SDL_Quit();



}

