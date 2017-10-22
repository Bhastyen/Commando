#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>
#include <time.h>
#include <MLV/MLV_all.h>

#include "Trajectoire.h"




int trajet_vide(Trajectoire trajet){

    return (trajet == NULL || trajet->direction == NULL);

}


Trajectoire creer_trajectoire_vide(){

    Trajectoire trajet = (Trajectoire) malloc(sizeof(struct trajectoire));
    if (!trajet){
        fprintf(stderr,"ErrMemory::Trajectoire.c::creer_trajet_vide()::Allocation_echouer\n");
        exit(-1);
    }
    
    trajet->vec_actuel = 0;
    trajet->position_vec = 0.0;
    
    
    trajet->direction = NULL;
    
    return trajet;

}


Trajectoire creer_trajectoire(double x, double y, double angle, double taille,...){
    Trajectoire trajet = creer_trajectoire_vide();
    Vecteur* v = NULL;
    double a, t, x1, y1;
    
    trajet->direction = creer_vec(x,y,angle,taille);
    v = trajet->direction;

    va_list liste;  // creer une va_liste
    va_start(liste,taille); // initialise liste avec le premiere argument

    a = va_arg(liste, double);   // recupere le premiere element de type double
    t = va_arg(liste, double);   // recupere le deuxieme element de type double
    while (a >= 0.0 && t >= 0.0){
        point_arrivee_vec(v, &x1, &y1);
        v->suivant = creer_vec(x1, y1 ,a, t);
    
        a = va_arg(liste, double);   // recupere le premiere element de type double
        t = va_arg(liste, double);   // recupere le deuxieme element de type double
    }

    va_end(liste);  // ferme la liste    


    return trajet;

}


Trajectoire creer_trajectoire_tab(double x, double y, double* tab){
    int n, i = 3;
    double a, t, x1, y1;
    
    Trajectoire trajet = creer_trajectoire_vide();
    Vecteur* v = NULL;
    
    if (tab == NULL){
        return NULL;
    }
    
    n = tab[0];
    
    trajet->direction = creer_vec(x,y,tab[1],tab[2]);
    v = trajet->direction;
    
    while (i<n){
        a = tab[i];
        t = tab[i+1];
    
        point_arrivee_vec(v, &x1, &y1);
        v->suivant = creer_vec(x1, y1 ,a, t);
    
        i += 2;
        v = v->suivant;
    }    


    return trajet;

}


double* gen_tab_trajectoire(double angle, double taille, int nb_changement){
    int i = 1;
    int j;
    int signe;
    double max = taille, min = 1.0;
    double a = angle;
    double t1 = (rand()/(double)(RAND_MAX))*(max-min)+min;
    double t = 0.0;
    double* tab = NULL;
    
    
    
    if (nb_changement < 0){
        nb_changement = rand()%(20-3)+3;
    }
    
    tab = (double*) malloc(sizeof(double)*nb_changement*2+3);
    if (tab == NULL){
        fprintf(stderr,"ErrMemoire::Trajectoire.c::gen_trajectoire()::malloc echoue\n");
        exit(-1);
    }
    
    tab[0] = nb_changement*2+3;
    
    while (i < nb_changement*2){
            
        tab[i] = a;
        tab[i+1] = t1;
            
        t += t1;
        max -= t1;
            
        if (t > taille){
            max = 0.0;
            min = 0.0;
            /*for (j=1; j<=i; j+=2){    // A revoir!!
                tab[j+1] /= 2.0;
                max += tab[j+1];
            }*/
        }
            
        i += 2;
        
        
        if (rand()%1 == 0){
            signe = -1;
        }else{
            signe = 1;
        }
        
        a += signe * (int) ((rand()/(double)(RAND_MAX))*(20-12)) % 360;
        t1 = (rand()/(double)(RAND_MAX))*(max-min)+min;
    }
        
    if (t < taille){
        tab[nb_changement*2-1] = (taille-t);
    }
    
    
    /*fprintf(stdout,"\n\n");
    for (i=1; i<tab[0]; i++){
        fprintf(stdout,"%lf\n",tab[i]);
    }*/
    
    return tab;

}


double* gen_tab_trajectoire_alea(double angle){
    int i = 1;
    int j;
    int signe;
    int nb_changement = rand()%(20-3)+3;
    
    double a = angle;
    double taille = (rand()/(double)(RAND_MAX))*(2000-150)+150;
    double max = taille, min = 1.0 ;
    double t1 = (rand()/(double)(RAND_MAX))*(max-min)+min;
    double t = 0.0;
    double* tab = NULL;
        
        
        
    tab = (double*) malloc(sizeof(double)*nb_changement*2+3);
    if (tab == NULL){
        fprintf(stderr,"ErrMemoire::Trajectoire.c::gen_trajectoire()::malloc echoue\n");
        exit(-1);
    }
    
    tab[0] = nb_changement*2+3;
    
    while (i < nb_changement*2){
            
        tab[i] = a;
        tab[i+1] = t1;
            
        t += t1;
        max -= t1;
            
        if (t > taille){
            max = 0.0;
            /*for (j=1; j<=i; j+=2){    // A revoir!!
                tab[j+1] /= 2.0;
                max += tab[j+1];
            }*/
        }
            
        i += 2;
        
        
        if (rand()%1 == 0){
            signe = -1;
        }else{
            signe = 1;
        }
        
        a += (int) ((rand()/(double)(RAND_MAX))*(15-2)) % 360;
        t1 = (rand()/(double)(RAND_MAX))*(max-min)+min;
    }
        
    if (t < taille){
        tab[nb_changement*2-1] = (taille-t);
    }
    
    
    return tab;

}


Trajectoire completer_trajectoire(Trajectoire trajet, double angle, double taille){
     double x,y;
     Vecteur* v = NULL;
     
     if (trajet_vide(trajet)){
         fprintf(stderr,"ErrValue::Trajectoire.c::completer_trajectoire()::ne peut completer un trajet vide\n");
         exit(-1);
     }
     
     v = trajet->direction;
     
     
     while (!vec_vide(v->suivant)){
          v = v->suivant;
     }
     
     
     point_arrivee_vec(v, &x, &y);
     v->suivant = creer_vec(x, y, angle, taille);
     
     return trajet;

}


Trajectoire destroy_trajectoire(Trajectoire trajet){

    if (!trajet_vide(trajet)){
        trajet->direction = destroy_vec(trajet->direction);
    }

    
    trajet = NULL;
    return trajet;

}


void MLVtracer_trajet(Trajectoire trajet){  //MLV_COLOR couleur
    Vecteur* v = NULL;
    
    if (!trajet_vide(trajet)){
        v = trajet->direction;
        
        while (!vec_vide(v)){
            tracer_vec(v);
            v = v->suivant;
        }
    }
    

}


void affiche_trajet_term(Trajectoire trajet){
    int compteur = 0;
    Vecteur* v = NULL;

    if (!trajet_vide(trajet)){
        v = trajet->direction;

        fprintf(stdout,"Affichage trajectoire:\n\n");
        while (!vec_vide(v)){
    
            fprintf(stdout,"Numero du vecteur: %d\n",compteur);
            fprintf(stdout,"Base: %lf %lf\n",v->pos->x, v->pos->y); 
            fprintf(stdout,"Direction (Angle en degree): %lf\n",v->angle);
            fprintf(stdout,"Norme: %lf\n",v->taille);
        
            v = v->suivant;
            compteur ++;
        }
    }
    
    
}


double longueur_trajectoire(Trajectoire trajet){
    Vecteur* v = NULL;
    double somme = 0.0;
    
    if (trajet_vide(trajet)){
        return 0.0;
    }
    
    v = trajet->direction;
    
    while (!vec_vide(v)){
        somme += v->taille;
        v = v->suivant;
    }

    return somme;

}


int avancer(Trajectoire t, double vitesse){
    int vecteur = 0;
    Vecteur* v = NULL;
    
    
    if (trajet_vide(t) || t->vec_actuel == -1){
        return 0;
    }
    
    t->position_vec += vitesse;

    v = getVec(t->direction, t->vec_actuel);
    
    if (t->position_vec > v->taille){
        t->vec_actuel ++;
        t->position_vec = (t->position_vec - v->taille);
        if (t->vec_actuel >= nombre_vecteur(t->direction)){
            t->vec_actuel = -1;
            t->position_vec = 0.0;
        }
    }
    
    
    return (t->vec_actuel != -1);

}




