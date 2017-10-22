#ifndef VECTEUR_H_INCLUDED
#define VECTEUR_H_INCLUDED

#include "Position.h"



struct vecteur{
    Pos* pos;
    Pos* camera;
    
    double angle;
    double taille;
    
    struct vecteur* suivant;
};

typedef struct vecteur Vecteur;



int vec_vide(Vecteur* vec);

Vecteur* creer_vec(double x, double y, double angle, double taille);

Vecteur* ajouter_vec(Vecteur* vec, double x, double y, double angle, double taille);

Vecteur* destroy_vec(Vecteur* vec);

Vecteur* creer_vec_point_arriver(double x1, double y1, double x2, double y2);

void point_arrivee_vec(Vecteur* vec, double* x, double* y);

Vecteur* getVec(Vecteur* depart, int numero);

int nombre_vecteur(Vecteur* vec);

void tracer_vec(Vecteur* vec);

void affiche_vec_term(Vecteur* vec);

double prod_scalaire_vec(Vecteur* vec1, Vecteur* vec2);

Vecteur* rotation_vec(Vecteur* vec, double x_ancrage, double y_ancrage, double angle);

int point_align_on_vec(double x, double y, Vecteur* vec);

int point_on_vec(double x, double y, Vecteur* vec1);

int point_in_arc(double x, double y, Vecteur* vec1, double angle_arc);


#endif // VECTEUR_H_INCLUDED
