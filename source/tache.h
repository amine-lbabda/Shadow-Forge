#ifndef TACHE_H
#define TACHE_H

typedef struct
{
    SDL_Surface *bg;
    SDL_Surface *gp[2];
    SDL_Surface *key[2];
    SDL_Surface *multi[2];
    SDL_Surface *single[2];
    SDL_Surface *zone[2];
    SDL_Surface *rika[2];
    SDL_Surface *rikam[2];
    SDL_Surface *logo;
    SDL_Rect pos_gp;
    SDL_Rect pos_key;
    SDL_Rect pos_single;
    SDL_Rect pos_multi;
    SDL_Rect pos_zone;
    SDL_Rect pos_rika;
    SDL_Rect pos_rikam;
    SDL_Rect pos_retour;
    SDL_Rect pos_confirm;
    SDL_Rect pos_text;
    SDL_Rect pos_textname;
    SDL_Rect pos_question;
    SDL_Rect pos_textmode;
    SDL_Rect pos_logo;
    TTF_Font *font;
    TTF_Font *font_text;
    TTF_Font *font_question;
    TTF_Font *font_textname;
    TTF_Font *font_textmode;
    SDL_Surface *retour_blanc;
    SDL_Surface *retour_rouge;
    SDL_Surface *confirm_blanc;
    SDL_Surface *confirm_rouge;
    SDL_Surface *text;
    SDL_Surface *textmode;
    SDL_Surface *textname;
    SDL_Surface *question;
    SDL_Color color_blanc;
    SDL_Color color_rouge;
    int btn_select;
    Mix_Music *continu;
    Mix_Chunk *hover_sound;
    int selected_character;
    int selected_input;
    char nom_joueur[30];
    int saisie_active;
    int joueur_actif;
} joueur;

void mode_init_menu(joueur *s);
void mode_afficher_menu(joueur s, SDL_Surface *ecran, int show_cursor);
int mode_collisionsouris(SDL_Rect pos);
void mode_miseajour(joueur *s);
void mode_liberer_save(joueur *s);
void mode_afficher_sous_menu(joueur s, SDL_Surface *ecran);
void mode_miseajour_sous_menu(joueur *s);
void start_tache(SDL_Surface *ecran, int *run, int *initial_menu);

#endif // TACHE_H
