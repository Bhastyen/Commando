#ifndef PROJECT_H_INCLUDED
#define PROJECT_H_INCLUDED

#include "Trajectoire.h"
#include "Position.h"
#include "Hitbox.h"
#include "env.h"


struct projectile{
    Pos* pos;
    Pos* camera;
    
    int vie;
    int degat;
    int zombie;
    double portee;
    double vitesse;
    double acceleration;
    
    Hitbox* box;
    Trajectoire trajet;
    struct projectile* suivant;
};

typedef struct projectile Projectile;



Projectile* creer_projectile(Pos* pos, double angle);

Projectile* ajouter_proj(Projectile* p1, Projectile* p2);

Projectile* supprimer_proj(Projectile* p);

Projectile* suppr_prj(Projectile* p);

void deplace_proj(Projectile* proj);

void afficher_proj(Projectile* proj);

void affiche_proj_term(Projectile* proj);

void change_direction_proj(Projectile* proj, double angle);

void calcul_vitesse_absolu_proj(Projectile* proj, double* proj_vx, double* proj_vy);

int fire_collision_on_border(Projectile* p, Env* e, double vitesse_x1, double vitesse_y1, double vitesse_x2, double vitesse_y2);

int fire_collision_on_terrain(Projectile* p, Env* e, double vitesse_x1, double vitesse_y1, double vitesse_x2, double vitesse_y2);


#endif
