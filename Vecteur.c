#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <MLV/MLV_all.h>

#include "Vecteur.h"




int vec_vide(Vecteur* vec){

    return (vec == NULL);

}


Vecteur* creer_vec(double x, double y, double angle, double taille){
    Vecteur* vec = (Vecteur*) malloc(sizeof(Vecteur));
    if (!vec){
        fprintf(stderr,"ErrMemory::creer_vec()::Allocation_echouer\n");
        exit(-1);
    }

    vec->pos = creer_position(x,y);
    vec->camera = creer_position(0.0,0.0);;

    vec->angle = angle;

    vec->taille = taille;
    
    vec->suivant = NULL;

    return vec;

}


Vecteur* ajouter_vec(Vecteur* vec, double x, double y, double angle, double taille){
    Vecteur* vec1 = vec;
    
    if (vec_vide(vec)){
        return creer_vec(x , y, angle, taille);
    }
    
    while (vec1->suivant != NULL){
        vec1 = vec1->suivant;
    }
    
    vec1->suivant = creer_vec(x , y, angle, taille);
    
    
    return vec;

}


Vecteur* destroy_vec(Vecteur* vec){
    Vecteur* v_suivant = NULL;

    while (!vec_vide(vec)){
        v_suivant = vec->suivant;
        
        if (!vec_vide(vec)){
            free(vec);
        }
        
        vec = v_suivant;
    }

    vec = NULL;
    return vec;

}


Vecteur* creer_vec_point_arriver(double x1, double y1, double x2, double y2){
    int x = x2 - x1;
    int y = y2 - y1;
    int x3, y3 = y1;
    
    double d;
    double alpha1, alpha2;
    double angle;
    
    
    Vecteur* vec = creer_vec(x1, y1, 0.0, sqrt(x*x+y*y));
    
    x3 = x1 + vec->taille;
    
    x = x3 - x2;
    y = y3 - y2;
    d = sqrt(x*x+y*y);
    
    if ((d/2)/vec->taille > 1.0){
        angle = 1.0;
    }else{
        angle = (d/2)/vec->taille;
    }
    
    if (y2 < y1){
        alpha1 = -asin(angle);
        alpha2 = -asin(angle);
    }else{
        alpha1 = asin(angle);
        alpha2 = asin(angle);
    }

    vec->angle = (alpha1+alpha2)*(180/3.14);

    return vec;

}


void point_arrivee_vec(Vecteur* vec, double* x, double* y){
    double t;
    double a;

    t = vec->taille;
    a = vec->angle*(3.14/180);

    if (vec_vide(vec)){
        fprintf(stderr,"ErrValeur::point_arrivee_vec()::vecteur_null\n");
        exit(-1);
    }

    *x = vec->pos->x+cos(a)*t;
    *y = vec->pos->y+sin(a)*t;

}


Vecteur* getVec(Vecteur* depart, int numero){
    Vecteur* v1 = NULL;
    Vecteur* v = depart;
    int compteur = 0;
    
    while (!vec_vide(v) && compteur < numero){
        v1 = v;
        v = v->suivant;
        compteur ++;
    }
    
    if (vec_vide(v)){
        return v1;
    }
    
    return v;

}


int nombre_vecteur(Vecteur* vec){
    Vecteur* v = vec;
    int compteur = 0;
    
    
    while (!vec_vide(v)){
        v = v->suivant;
        compteur ++;
    }
    
    
    return compteur;

}


void tracer_vec(Vecteur* vec){  //MLV_COLOR couleur
    double x2, y2;

    if (vec_vide(vec)){
        fprintf(stderr,"ErrValeur::tracer_vec()::vecteur_null\n");
        exit(-1);
    }

    point_arrivee_vec(vec, &x2, &y2);
    MLV_draw_line(vec->camera->x + vec->pos->x, vec->camera->y + vec->pos->y, x2, y2, MLV_rgba(0,255,0,255));

}


void affiche_vec_term(Vecteur* vec){

    if (!vec_vide(vec)){
    
        fprintf(stdout,"Base: %lf %lf\n",vec->pos->x, vec->pos->y); 
        fprintf(stdout,"Direction (Angle en degree): %lf\n",vec->angle);
        fprintf(stdout,"Norme: %lf\n",vec->taille);   
    
    }

}


double angle_between_2vec(Vecteur* vec1, Vecteur* vec2){   // recupere l'angle former par vec1 et vec2

    if (vec_vide(vec1) || vec_vide(vec2)){
        fprintf(stderr,"ErrValeur::angle_between_2vec()::vecteur_null\n");
        exit(-1);
    }

    return 360.0-(fabs(vec1->angle-vec2->angle));

}


double prod_scalaire_vec(Vecteur* vec1, Vecteur* vec2){
    double a;

    if (vec_vide(vec1) || vec_vide(vec2)){
        fprintf(stderr,"ErrValeur::prod_scalaire_vec()::vecteur_null\n");
        exit(-1);
    }

    a = angle_between_2vec(vec1, vec2);
    a = a * (3.14/180);    // conversion en radian

    return vec1->taille*vec2->taille*cos(a);  // renvoie le resultat du produit scalaire (formule geometrique)

}


Vecteur* rotation_vec(Vecteur* vec, double x_ancrage, double y_ancrage, double angle){
    double x, y, x1, y1, x2, y2;
    Vecteur *vec1, *vec2;

    if (vec_vide(vec)){
        fprintf(stderr,"ErrValeur::rotation_vec()::vecteur_null\n");
        exit(-1);
    }

    point_arrivee_vec(vec, &x, &y);

    vec1 = creer_vec_point_arriver(x_ancrage,y_ancrage,vec->pos->x,vec->pos->y);
    vec2 = creer_vec_point_arriver(x_ancrage,y_ancrage,x,y);

    vec1->angle += angle;
    vec2->angle += angle;

    point_arrivee_vec(vec1, &x1, &y1);
    point_arrivee_vec(vec2, &x2, &y2);

    vec = destroy_vec(vec);

    return creer_vec_point_arriver(x1, y1, x2, y2);

}


/*double** rotation_polygone(double x, double y, double poly[][2], int nombre_point){
    double** rot_poly = (double**) malloc(sizeof(double*)*nombre_point);
    if (!rot_poly){
        fprintf(stderr,"ErrMemory::rotation_polygone()::Allocation_echouer\n");
        exit(-1);
    }





}*/


int vec_colineaire(Vecteur* vec1, Vecteur* vec2){

    if (vec_vide(vec1) || vec_vide(vec2)){
        fprintf(stderr,"ErrValeur::vec_colineaire()::vecteur_null\n");
        exit(-1);
    }



    return 1;

}


int point_align_on_vec(double x, double y, Vecteur* vec1){
    Vecteur* vec2 = NULL;

    if (vec_vide(vec1)){
        fprintf(stderr,"ErrValeur::point_align_on_vec()::vecteur_null\n");
        exit(-1);
    }

    vec2 = creer_vec_point_arriver(vec1->pos->x, vec1->pos->y, x, y);


    return ((int) angle_between_2vec(vec1, vec2) == 0);

}


int point_on_vec(double x, double y, Vecteur* vec1){
    Vecteur* vec2 = NULL;

    if (vec_vide(vec1)){
        fprintf(stderr,"ErrValeur::point_on_vec()::vecteur_null\n");
        exit(-1);
    }

    vec2 = creer_vec_point_arriver(vec1->pos->x, vec1->pos->y, x, y);


    return (( (int) angle_between_2vec(vec1, vec2) == 0) && (vec2->taille <= vec1->taille));

}


int point_in_arc(double x, double y, Vecteur* vec1, double angle_arc){

    // utiliser les determinant

    return 1;

}




