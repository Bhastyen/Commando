#ifndef JOUEUR_H_INCLUDED
#define JOUEUR_H_INCLUDED

#include <time.h>
#include "Vecteur.h"
#include "Hitbox.h"
#include "Projectile.h"
#include "Position.h"
#include "env.h"

struct joueur{
  Pos* pos;
  Pos* camera;
  
  int vie;
  double vitesse;
  double acceleration;
  clock_t cadence_tire;
  
  Hitbox* box;
  Vecteur* vue;
  Projectile* p;
  
  struct joueur* suivant;
  
};


typedef struct joueur Joueur;



Joueur* creer_joueur();

Joueur* tuer_joueur(Joueur* j);

Pos* get_position(Joueur* j);

int get_vie(Joueur* j);

void set_position(Joueur*j, Pos* pos);

void set_vie(Joueur* j, int vie);

void set_vue(Joueur* j, double angle);

void afficher_joueur(Joueur* j);

int player_collision_on_border(Joueur* j, Env* e, double vitesse_x1, double vitesse_y1, double vitesse_x2, double vitesse_y2);

int player_collision_on_terrain(Joueur* j, Env* e, double vitesse_x1, double vitesse_y1, double vitesse_x2, double vitesse_y2);

void recupere_angle_vue(Joueur* j);


#endif
