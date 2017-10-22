#ifndef HITBOX_H_INCLUDED
#define HITBOX_H_INCLUDED

#include "Vecteur.h"
#include "Position.h"

struct hitbox{

    Pos* pos;
    Pos* camera;
    
    double taille_x;
    double taille_y;
    int type;

    struct hitbox* suivant;
};

typedef struct hitbox Hitbox;



Hitbox* creer_box(Pos* pos, double taille_x, double taille_y, int type);

Hitbox* ajouter_collision(Hitbox* box1, Hitbox* box2);

void deplacer_box(Hitbox* h, Pos* pos);

int collision_box(Hitbox* box1, Hitbox* box2, double vitesse_x1, double vitesse_y1, double vitesse_x2, double vitesse_y2);

Hitbox* supprimer_box(Hitbox* h);

void tracer_hitbox(Hitbox* box);


#endif
