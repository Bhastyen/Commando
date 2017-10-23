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

int collision(Hitbox* h1, Hitbox* h2, double dx1, double dy1, double dx2, double dy2);

int circleCollision(Hitbox* h1, Hitbox* h2);

int rectCollision(Hitbox* h1, Hitbox* h2);

int circleCollisionOnCircle(Hitbox* h1, Hitbox* h2);

int rectCollisionOnRect(Hitbox* h1, Hitbox* h2);

int circleCollisionOnRect(Hitbox* h1, Hitbox* h2);

int rectCollisionOnCircle(Hitbox* h1, Hitbox* h2);

Hitbox* supprimer_box(Hitbox* h);

void tracer_hitbox(Hitbox* box);


#endif
