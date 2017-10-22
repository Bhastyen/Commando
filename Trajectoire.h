#ifndef TRAJECTOIRE_H_INCLUDED
#define TRAJECTOIRE_H_INCLUDED

#include "Vecteur.h"



struct trajectoire{

    int vec_actuel;
    double position_vec;

    Vecteur* direction;

};


typedef struct trajectoire* Trajectoire;




int trajet_vide(Trajectoire trajet);

Trajectoire creer_trajectoire_vide();

Trajectoire creer_trajectoire(double x, double y, double angle, double taille,...);

Trajectoire creer_trajectoire_tab(double x, double y, double* tab);

double* gen_tab_trajectoire_alea(double angle);

double* gen_tab_trajectoire(double angle, double taille, int nb_changement);

double* gen_tab_trajectoire_connu(double angle, int mode);

Trajectoire destroy_trajectoire(Trajectoire trajet);

Trajectoire completer_trajectoire(Trajectoire trajet, double angle, double taille);

void MLVtracer_trajet(Trajectoire trajet);

void affiche_trajet_term(Trajectoire trajet);

double longueur_trajectoire(Trajectoire trajet);

int avancer(Trajectoire t, double vitesse);


#endif // TRAJECTOIRE_H_INCLUDED
