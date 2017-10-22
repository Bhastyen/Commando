#ifndef ENV_H_INCLUDED
#define ENV_H_INCLUDED

#include "Hitbox.h"


typedef struct env{
    Pos* camera;
    
    int t_x1;
    int t_y1;
    int t_x2;
    int t_y2;
    double t_case_x;
    double t_case_y;
    
    int x;
    int y;
    int valeur;   // a remplacer par le chemin d'une image plus tard
    
    Hitbox* box;
    struct env* suivant;
} Env;


Env* creer_env(int x, int y, int valeur, int t_x1, int t_y1, int t_x2, int t_y2, double t_case_x, double t_case_y);

Env* completer_env(Env* e, Env* case1);

Env* gen_env(int t_x1, int t_y1, int t_x2, int t_y2, double proba, int graine);

Env* vider_env(Env* e);

Env* supprimer_case(Env* e, int x ,int y);

void tracer_env(Env* e);

void tracer_grille_env(Env* e);


#endif
