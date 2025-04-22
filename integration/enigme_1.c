#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <time.h>
#include "enigme_1.h"
void init_menu(menu* m){
   TTF_Init();
    m->bg_principale=IMG_Load("bground.png");
    m->bquiz[0]=IMG_Load("buttons/bquiz1.png");
    m->bquiz[1]=IMG_Load("buttons/bquiz2.png");
    m->bpuzzle[0]=IMG_Load("buttons/bpuzzle1.png");
    m->bpuzzle[1]=IMG_Load("buttons/bpuzzle2.png");
    m->posquiz.x=1920/2 - (m->bquiz[0]->w / 2);
    m->posquiz.y=700;
    m->posquiz.w=m->bquiz[0]->w;
    m->posquiz.h=m->bquiz[0]->h;
    m->pospuzzle.h=m->bpuzzle[0]->h;
    m->pospuzzle.w=m->bpuzzle[0]->w;
    m->pospuzzle.x=1920/2 -(m->bpuzzle[0]->w / 2);
    m->pospuzzle.y=900;
    m->pospuzzle2.h=m->bpuzzle[1]->h;
    m->pospuzzle2.w=m->bpuzzle[1]->w;
    m->pospuzzle2.x=1920/2 -(m->bpuzzle[1]->w / 2);
    m->pospuzzle2.y=840;
    m->posquiz2.h=m->bpuzzle[1]->h;
    m->posquiz2.w=m->bpuzzle[1]->w;
    m->posquiz2.x=1920/2 -(m->bpuzzle[1]->w / 2);
    m->posquiz2.y=640;
    m->logo=IMG_Load("LOGO.png");
    m->posl.w=100;
 m->posl.h=100;
 m->posl.x=1920/2 - m->logo->w / 2;
 m->posl.y=2;
 SDL_Color color3={255,255,246};
 m->Return[0]=TTF_RenderText_Solid(TTF_OpenFont("HARRYP__.TTF",120),"Return",color3);
 if(!m->Return[0]){
   puts("erreur Reuturn");
 }
 m->posr.x=20;
 m->posr.y=920;
m->posr.w=m->Return[0]->w;
m->posr.h=m->Return[0]->h;
SDL_Color red={255,0,0};
 m->Return[1] =TTF_RenderText_Solid(TTF_OpenFont("HARRYP__.TTF",120),"Return",red);
 m->click=Mix_LoadWAV("press.wav");
}
void afficher_menu(menu m,SDL_Surface *ecran){
TTF_Font* police=TTF_OpenFont("HARRYP__.TTF",180);
 SDL_BlitSurface(m.bg_principale,NULL,ecran,NULL);
 SDL_Color color={255,255,255};
 SDL_Surface* text=TTF_RenderText_Solid(police,"QUIZ/PUZZLE TIME!",color);
 if(!text){
    puts("error text!"); 
 }
 SDL_Rect textRect = {ecran->w/2 - text->w /2, 320, 0, 0};
 
 SDL_BlitSurface(text,NULL,ecran,&textRect);
 SDL_BlitSurface(m.logo,NULL,ecran,&m.posl);
 SDL_Color color2 ={200,148,98};
 TTF_Font* police2=TTF_OpenFont("HARRYP__.TTF",80);
 SDL_Surface* text2=TTF_RenderText_Solid(police2,"choose one option to continue",color2);
 if(!text2){
    puts("error text!"); 
 }
 SDL_Rect textRect2 = {ecran->w/2 - text2->w /2, 634, 0, 0};
 SDL_BlitSurface(text2,NULL,ecran,&textRect2);
 
 if(!cursor(m.posquiz)){
 SDL_BlitSurface(m.bquiz[0],NULL,ecran,&m.posquiz);}
 else{
    SDL_BlitSurface(m.bquiz[1],NULL,ecran,&m.posquiz2);
 }
 if(!cursor(m.pospuzzle))
 SDL_BlitSurface(m.bpuzzle[0],NULL,ecran,&m.pospuzzle);
 else SDL_BlitSurface(m.bpuzzle[1],NULL,ecran,&m.pospuzzle2);
 if(!cursor(m.posr)) SDL_BlitSurface(m.Return[0],NULL,ecran,&m.posr);
else SDL_BlitSurface(m.Return[1],NULL,ecran,&m.posr);
SDL_FreeSurface(text);
    SDL_FreeSurface(text2);
    TTF_CloseFont(police);
    TTF_CloseFont(police2);
}
void update(menu* m){
   if(cursor(m->posquiz)){
      m->poscursor=1;
   }
   else{
      if(cursor(m->pospuzzle)){
         m->poscursor=2;
      }
      else{
      if(cursor(m->posr)){
         m->poscursor=3;
      }
      
      else{
         m->poscursor=0;
      }
   }
}
}
int cursor(SDL_Rect pos){
   int x,y;
   SDL_GetMouseState(&x,&y);
   return x>pos.x && x<pos.x+pos.w && y>pos.y && y< pos.y+pos.h;
}
void cleanup(menu* m, quiz* q) {
   SDL_FreeSurface(m->bg_principale);
   SDL_FreeSurface(m->logo);
   SDL_FreeSurface(m->bquiz[0]);
   SDL_FreeSurface(m->bquiz[1]);
   SDL_FreeSurface(m->bpuzzle[0]);
   SDL_FreeSurface(m->bpuzzle[1]);
   SDL_FreeSurface(m->Return[0]);
   SDL_FreeSurface(m->Return[1]);
   SDL_FreeSurface(q->bg);
   SDL_FreeSurface(q->Return[0]);
   SDL_FreeSurface(q->Return[1]);
   TTF_Quit();
   SDL_Quit();
}
void init_quiz(quiz* q,int t[],int* n){
   TTF_Init();
   SDL_Color red={255,0,0};
   q->bg=IMG_Load("bground.png");
   q->logo=IMG_Load("LOGO.png");
   SDL_Color color3={255,255,246};
   TTF_Font *font = TTF_OpenFont("HARRYP__.TTF", 120);
   TTF_Font *font2 = TTF_OpenFont("HARRYP__.TTF", 60);
   if (!font) {
       printf("Error loading font: %s\n", TTF_GetError());
       exit(1);  // Exit if the font is missing
   }
   q->Return[0] = TTF_RenderText_Solid(font, "Return", color3);
   q->Return[1] = TTF_RenderText_Solid(font, "Return", red);    if(!q->Return[0]){
     puts("erreur Return");
   }
   q->cadre1=IMG_Load("c1.png");
   q->cadre2[0]=IMG_Load("c2.png");
   q->cadre2[1]=IMG_Load("c3.png");
   q->posr.x=20;
   q->posr.y=920;
   q->posr.w=q->Return[0]->w;
  q->posr.h=q->Return[0]->h;
   q->posl.w=100;
   q->posl.h=100;
   q->posl.x=1920/2 - q->logo->w / 2;
   q->posl.y=2;
   q->poscadre1.h=q->cadre1->h;
   q->poscadre1.w=q->cadre1->w;
   q->poscadre1.x=(1920/2)-q->cadre1->w/2;
   q->poscadre1.y=200;
   q->poscadre2[0].x=300;
   q->poscadre2[0].y=700;
   q->poscadre2[1].x=1260;
   q->poscadre2[1].y=700;
   int k;
   for(k=0;k<4;k++){
   q->poscadre2[k].w=q->cadre2[0]->w;
   q->poscadre2[k].h=q->cadre2[0]->h;
   }
   q->poscadre2[2].x=300;
   q->poscadre2[2].y=840;
   q->poscadre2[3].x=1260;
   q->poscadre2[3].y=840;
   int j;
   for(j=0;j<4;j++){
     q->poscadre2[j].h=q->cadre2[0]->h;
   q->poscadre2[j].w=q->cadre2[0]->w;
   }
   q->click=Mix_LoadWAV("press.wav");
  q->clock=Mix_LoadWAV("clock.wav");
  q->win=Mix_LoadMUS("win.mp3");
  q->lose=Mix_LoadMUS("lose.mp3");
  q->posclock.y=-60;
  q->posclock.x=-260;
  q->clock_pic[0]=IMG_Load("1.png");
  q->clock_pic[1]=IMG_Load("2.png");
  q->clock_pic[2]=IMG_Load("3.png");
  q->clock_pic[3]=IMG_Load("4.png");
  q->clock_pic[4]=IMG_Load("5.png");
  q->clock_pic[5]=IMG_Load("6.png");
  q->clock_pic[6]=IMG_Load("7.png");
  q->clock_pic[7]=IMG_Load("8.png");
  q->clock_pic[8]=IMG_Load("9.png");
  srand(time(NULL));
  int alea;
  do{
   alea=(rand()%10)+1;
  }while(exist(t,*n,alea));
  q->nb_q=alea;
  int i;
t[(*n)++]=alea;
  char qs[100];
  FILE* f = fopen("quiz2.txt","r");
  for(i=0;i<alea;i++){
   fgets(qs,sizeof(qs),f);
  }
  qs[strlen(qs)-2]='\0';
  fclose(f);
  q->question=TTF_RenderText_Solid(font2,qs,color3); 
  q->pos_question.x=(q->poscadre1.x+(q->poscadre1.w/2))-(q->question->w)/2 +40;
q->pos_question.y = q->poscadre1.y + (q->poscadre1.y/2) + 100;   
q->pos_question.h=q->question->h;
  q->pos_question.w=q->question->w;
  switch(alea){
   case 1:
   init_rep(q->reponses,"A) Picasso","B) Da Vinci","C) Van Gogh","D) Monet");
   q->true_rep=q->poscadre2[1];break;
   case 2:
   init_rep(q->reponses,"A) 10","B) 16","C) 14","D) 12");
   q->true_rep=q->poscadre2[3];break;
   case 3:
   init_rep(q->reponses,"A) Newton","B) Einstein","C) Galileo","D) Tesla");
   q->true_rep=q->poscadre2[0];break;
   case 4:
   init_rep(q->reponses,"A) Monet","B) Dali","C) Van Gogh","D) Picasso");
   q->true_rep=q->poscadre2[2];break;
   case 5:
   init_rep(q->reponses,"A) Twain","B) Shakespeare","C) Dickens","D) Austen");
   q->true_rep=q->poscadre2[1];break;
   case 6:
   init_rep(q->reponses,"A) Tokyo","B) Beijing","C) Seoul","D) Bangkok");
   q->true_rep=q->poscadre2[0];break;
   case 7:
   init_rep(q->reponses,"A) Earth","B) Venus","C) Mercury","D) Mars");
   q->true_rep=q->poscadre2[2];break;
   case 8:
   init_rep(q->reponses,"A) 4","B) 6","C) 7","D) 8");
   q->true_rep=q->poscadre2[1];break;
   case 9:
   init_rep(q->reponses,"A) Water","B) Oxygen","C) Salt","D) Acid");
   q->true_rep=q->poscadre2[0];break;
   case 10:
   init_rep(q->reponses,"A) India","B) USA","C) China","D) Russia");
   q->true_rep=q->poscadre2[2];break;
  }
  q->pos_reponses[0].x=(q->poscadre2[0].x+(q->cadre2[0]->w/2))-(q->reponses[0]->w)/2;
  q->pos_reponses[0].y = q->poscadre2[0].y + (q->cadre2[0]->h/2)-q->reponses[0]->h/2;   
  q->pos_reponses[1].x=(q->poscadre2[1].x+(q->cadre2[0]->w/2))-(q->reponses[1]->w)/2;
  q->pos_reponses[1].y = q->poscadre2[1].y + (q->cadre2[0]->h/2)-q->reponses[0]->h/2;
  q->pos_reponses[2].x=(q->poscadre2[2].x+(q->cadre2[0]->w/2))-(q->reponses[2]->w)/2;
  q->pos_reponses[2].y = q->poscadre2[2].y + (q->cadre2[0]->h/2)-q->reponses[0]->h/2;
  q->pos_reponses[3].x=(q->poscadre2[3].x+(q->cadre2[0]->w/2))-(q->reponses[3]->w)/2;
  q->pos_reponses[3].y = q->poscadre2[3].y + (q->cadre2[0]->h/2)-q->reponses[0]->h/2;
  q->box[0]=IMG_Load("lose1.png");
  q->box[1]=IMG_Load("win.png");
  q->box[2]=IMG_Load("lose 2.png");
  q->label_score=TTF_RenderText_Solid(font,"score: ",color3);
  q->pos_labelscore.x=460;
  q->pos_labelscore.y=660;
  q->posscore.x=480 + q->label_score->w;
  q->posscore.y=660;
 }
  void afficher_quiz(quiz q,SDL_Surface *ecran,unsigned int nb,int* animation){
     SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO);
     TTF_Init();
     SDL_BlitSurface(q.bg,NULL,ecran,NULL);
     SDL_BlitSurface(q.logo,NULL,ecran,&q.posl);
     SDL_BlitSurface(q.cadre1,NULL,ecran,&q.poscadre1);
          cursor(q.poscadre2[0])? SDL_BlitSurface(q.cadre2[1],NULL,ecran,&q.poscadre2[0]): SDL_BlitSurface(q.cadre2[0],NULL,ecran,&q.poscadre2[0]);
         cursor(q.poscadre2[1])? SDL_BlitSurface(q.cadre2[1],NULL,ecran,&q.poscadre2[1]): SDL_BlitSurface(q.cadre2[0],NULL,ecran,&q.poscadre2[1]);
         cursor(q.poscadre2[2])? SDL_BlitSurface(q.cadre2[1],NULL,ecran,&q.poscadre2[2]): SDL_BlitSurface(q.cadre2[0],NULL,ecran,&q.poscadre2[2]);
         cursor(q.poscadre2[3])? SDL_BlitSurface(q.cadre2[1],NULL,ecran,&q.poscadre2[3]): SDL_BlitSurface(q.cadre2[0],NULL,ecran,&q.poscadre2[3]);
           SDL_BlitSurface(q.question,NULL,ecran,&q.pos_question);
           int i;
           for(i=0;i<4;i++){
             SDL_BlitSurface(q.reponses[i],NULL,ecran,&q.pos_reponses[i]);
           }
switch(nb){
 case 0:
 SDL_BlitSurface(q.clock_pic[0],NULL,ecran,&q.posclock);break;
 case 1:
 SDL_BlitSurface(q.clock_pic[1],NULL,ecran,&q.posclock);break;
 case 2:
 SDL_BlitSurface(q.clock_pic[2],NULL,ecran,&q.posclock);break;
 case 3:
 SDL_BlitSurface(q.clock_pic[3],NULL,ecran,&q.posclock);break;
 case 4:
 SDL_BlitSurface(q.clock_pic[4],NULL,ecran,&q.posclock);break;
 case 5:
 SDL_BlitSurface(q.clock_pic[5],NULL,ecran,&q.posclock);break;
 case 6:
 SDL_BlitSurface(q.clock_pic[6],NULL,ecran,&q.posclock);break;
 case 7:
 SDL_BlitSurface(q.clock_pic[7],NULL,ecran,&q.posclock);break;
 case 8:
 SDL_BlitSurface(q.clock_pic[8],NULL,ecran,&q.posclock);break;
   }
}
void init_rep(SDL_Surface* reponse[],char* rep1,char* rep2,char* rep3,char* rep4){
 TTF_Font *font = TTF_OpenFont("HARRYP__.TTF", 80);
 SDL_Color white={255,255,246};
 reponse[0]=TTF_RenderText_Solid(font,rep1,white);
 reponse[1]=TTF_RenderText_Solid(font,rep2,white); 
 reponse[2]=TTF_RenderText_Solid(font,rep3,white); 
 reponse[3]=TTF_RenderText_Solid(font,rep4,white); 
}
int exist(int t[],int n,int nb){
   int i=0;
   while(i<n && t[i]!=nb)i++;
   return i!=n; 
}
char* convch(int nb){
   static char ch[100];
   int i=0;
   if(!nb)return "0";
   while(nb!=0){
      ch[i++]=(nb%10)+'0';
      nb/=10;
   }
   ch[i]='\0';
   for(i=0;i<strlen(ch)/2;i++){
      char aux=ch[i];
      ch[i]=ch[strlen(ch)-1-i];
      ch[strlen(ch)-1-i]=aux;
   }
   return ch;
}