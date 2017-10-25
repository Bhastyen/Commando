#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <MLV/MLV_all.h>

#include "define.h"

#include "env.h"



Env* creer_env(int x, int y, int valeur, int t_x1, int t_y1, int t_x2, int t_y2, double t_case_x, double t_case_y){
    Env* e = NULL;
    
    if (x >= t_x1 && x <= t_x2 && y >= t_y1 && y <= t_y2 && t_case_x < (t_x2-t_x1) && t_case_y < (t_y2-t_y1) && (t_x2-t_x1) > 0 && (t_y2-t_y1) > 0){
        e = (Env*) malloc(sizeof(Env));
        if (e == NULL){
            fprintf(stderr,"ErrMemoire::creer_env()::probleme_allocation_memoire\n");
            exit(-1);
        } 
        
        e->camera = creer_position(0.0, 0.0); 

        e->t_x1 = t_x1;
        e->t_y1 = t_y1;
        e->t_x2 = t_x2;
        e->t_y2 = t_y2;
        e->t_case_x = t_case_x;
        e->t_case_y = t_case_y;
    
        e->x = x;
        e->y = y;
        e->valeur = valeur;
    
        e->box = creer_box(creer_position(x*TAILLE_CASE + (TAILLE_CASE/2), y*TAILLE_CASE + (TAILLE_CASE/2)), TAILLE_CASE/2, TAILLE_CASE/2, CARRE);   
        e->suivant = NULL;
        
        return e;
    
    }else{
        fprintf(stderr,"ErrValeur::creer_env()::valeur_env_non_valide\n");
        exit(-1);
    }
    

}


Env* completer_env(Env* e, Env* case1){
    Env* m = e;
    
    if (e == NULL){
        return case1;
    }
    
    while(m->suivant != NULL){   // inserer dans l'ordre
        m = m->suivant;
    }
    
    m->suivant = case1;

    return e;

}


Env* gen_env(int t_x1, int t_y1, int t_x2, int t_y2, double proba, int graine){
    int x,y;
    double n;
    Env *e = NULL, *e1 = NULL;
    
    
    if (graine != 0){
        srand(graine);
    }else{
        srand(time(NULL));
    }
    
    
    //fprintf(stderr,"Probleme: \n");
    for (x = (t_x1/TAILLE_CASE); x < (t_x2/TAILLE_CASE); x++){
        for (y = (t_y1/TAILLE_CASE); y < (t_y2/TAILLE_CASE); y++){
            n = (double)random()/RAND_MAX;
            //fprintf(stderr,"Probleme: %lf\n",n);
            if (n <= proba){
                e1 = creer_env(x,y,BLANC,t_x1,t_y1,t_x2,t_y2,TAILLE_CASE,TAILLE_CASE);
                e = completer_env(e, e1);
            }
        }
    }


    return e;

}


Env* vider_env(Env* e){
    Env* m = NULL;
    
    while (e != NULL){
        m = e->suivant;
        // libere la memoire des autres structures
        free(e);
        e = m;
    }


    return NULL;

}


Env* supprimer_case(Env* e, int x ,int y){
    Env* m = e;
    Env* suivant = NULL;
    
    
    if (e == NULL){
        return e;
    }
    
    while (m->suivant != NULL && m->suivant->x != x && m->suivant->y != y){
        m = m->suivant;
    }

    if (m->suivant != NULL){
        suivant = m->suivant->suivant;
        free(m->suivant);
        m->suivant = suivant;
    }
    
    
    return e;

}


void tracer_env(Env* e){
    Env* m = e;
    int x,y;
    double camera_x = e->camera->x, camera_y = e->camera->y;
    
    
    while (m != NULL){
        x = m->x*m->t_case_x;
        y = m->y*m->t_case_y;
        
        if (m->valeur == BLANC){
            MLV_draw_filled_rectangle(camera_x + x, camera_y + y, m->t_case_x, m->t_case_y, MLV_rgba(255,255,255,255));   // tracer une image plus tard
            tracer_hitbox(m->box);
        }
        
        
        m = m->suivant;
    }
    
    MLV_draw_rectangle(camera_x+e->t_x1, camera_y+e->t_y1, (e->t_x2 - e->t_x1), (e->t_y2 - e->t_y1), MLV_rgba(255,255,255,255));   // contour du terrain

}


void tracer_grille_env(Env* e){
    Env* m = e;
    int x,y;
    double camera_x = e->camera->x, camera_y = e->camera->y;
    
    if (e == NULL){
       return ;
    }

    for (x = m->t_x1; x < m->t_x2; x += m->t_case_x){
        for (y = m->t_y1; y < m->t_y2; y += m->t_case_y){
            MLV_draw_rectangle(camera_x + x,camera_y + y,m->t_case_x,m->t_case_y,MLV_rgba(127,127,127,255));
        }
    }

}



