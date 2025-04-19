#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

typedef struct{
    SDL_Surface* bg_principale;
    SDL_Surface* bquiz[2];
    SDL_Surface* bpuzzle[2];
    SDL_Surface* logo;
    SDL_Surface* Return[2];
    SDL_Rect posr;
    SDL_Rect posl;
    SDL_Rect posquiz;
    SDL_Rect pospuzzle;
    SDL_Rect posquiz2;
    SDL_Rect pospuzzle2;
    int poscursor;
    Mix_Chunk *click;

}menu;
typedef struct{
    SDL_Surface* bg;
    SDL_Surface* logo;
    SDL_Surface* Return[2];
    SDL_Surface* cadre1,*cadre2[2];
    SDL_Surface* clock_pic[9];
    SDL_Surface* question;
    SDL_Surface* box[3];
    SDL_Surface* label_score;
    int nb_q;
    SDL_Surface* reponses[4];
SDL_Rect poscadre1;
SDL_Rect poscadre2[4];
    SDL_Rect posclock;
    SDL_Rect  posl;
    SDL_Rect posr;
    SDL_Rect pos_question;
    SDL_Rect pos_reponses[4];
   SDL_Rect posscore;
    SDL_Rect true_rep;
    SDL_Rect pos_labelscore;
    int poscursor;
    int score;
    Mix_Chunk *click;
    Mix_Chunk *clock;
    Mix_Music *win,*lose;
}quiz;

void init_menu(menu*);
void afficher_menu(menu,SDL_Surface* ecran);
void update(menu*);
void cleanup(menu* m, quiz* q);
void init_quiz(quiz*,int t[],int*);
int exist(int t[],int n,int);
void afficher_quiz(quiz,SDL_Surface* ecran,unsigned int,int*);
int cursor(SDL_Rect pos);
void init_rep(SDL_Surface* reponse[],char* rep1,char* rep2,char* rep3,char* rep4);
char* convch(int);
#endif