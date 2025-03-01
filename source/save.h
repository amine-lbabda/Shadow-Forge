#pragma once

typedef struct
{
    SDL_Surface *bg;
    SDL_Surface *yes[2];
    SDL_Surface *no[2];
    SDL_Surface *load[2];
    SDL_Surface *new[2];
    SDL_Surface *logo;
    SDL_Rect pos_yes;
    SDL_Rect pos_no;
    SDL_Rect pos_load;
    SDL_Rect pos_new;
    SDL_Rect pos_retour;
    SDL_Rect pos_text;
    SDL_Rect pos_question;
    SDL_Rect pos_logo;
    TTF_Font *font;
    TTF_Font *font_text;
    TTF_Font *font_question;
    SDL_Surface *retour_blanc;
    SDL_Surface *retour_rouge;
    SDL_Surface *text;
    SDL_Surface *question;
    SDL_Color color_blanc;
    SDL_Color color_rouge;
    int btn_select;
    Mix_Music *continu;
    Mix_Chunk *hover_sound;
} save;

void init_save(save *s);
void afficher_save(save s, SDL_Surface *ecran);
int collisionsouris(SDL_Rect pos);
void miseajour(save *s);
void miseajour_sous_menu(save *s);
void afficher_sous_menu(save s, SDL_Surface *ecran);
void liberer_save(save *s);
void chargement(SDL_Surface *ecran, int *run);
