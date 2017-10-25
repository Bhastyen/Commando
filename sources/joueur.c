#include <stdio.h>
#include <stdlib.h>
//#include <time.h>
#include <MLV/MLV_all.h>

#include "define.h"
#include "joueur.h"




Joueur* creer_joueur(Pos* set_pos){
  Joueur* j = (Joueur*) malloc(sizeof(Joueur));
  if (j == NULL){
    fprintf(stderr,"ErrMemoire::creer_joueur()::probleme_allocation_joueur\n");
    exit(-1);
  }

  j->pos = creer_position(set_pos->x, set_pos->y); 
  j->camera = creer_position(0.0, 0.0); 

  j->vie = 100;
  j->vitesse = 1.0;
  j->acceleration = 1.0;
  j->cadence_tire = clock();

  j->box = creer_box(j->pos, TAILLE_JOUEUR, TAILLE_JOUEUR, CARRE);
  j->vue = creer_vec(j->pos->x, j->pos->y, 0.0, TAILLE_JOUEUR+10.0);
  j->p = NULL;

  j->suivant = NULL;

  return j;

}


Joueur* tuer_joueur(Joueur* j){

  if (j != NULL){
    j->pos = supprimer_position(j->pos);
    j->box = supprimer_box(j->box);
    j->vue = destroy_vec(j->vue);

    j->p = supprimer_proj(j->p);

    j->suivant = NULL;
  }
  
  return NULL;
  
}


Pos* get_position(Joueur* j){

  if (j != NULL){
    return j->pos;
  }else{
    return NULL;
  }
  
}


int get_vie(Joueur* j){

  if (j != NULL){
    return j->vie;
  }else{
    return 0;
  }

}


void set_position(Joueur* j, Pos* set_pos){

  if (j != NULL){
    deplacement_position(j->pos, set_pos->x, set_pos->y);
    deplacement_position(j->box->pos, set_pos->x, set_pos->y);
    deplacement_position(j->vue->pos, set_pos->x, set_pos->y);
  }
  
  //detruit position
  
}


void set_vie(Joueur* j, int vie){

  if (j != NULL){
    j->vie = vie;
  }
  
}


void set_vue(Joueur* j, double angle){
  
  if (j != NULL){
    j->vue->angle = angle;
  }

}


void afficher_joueur(Joueur* j){
  Projectile* proj = j->p;
    

  if (j == NULL){
      return ;
  }


  tracer_vec(j->vue);
  MLV_draw_filled_circle(j->camera->x + j->pos->x, j->camera->y + j->pos->y, TAILLE_JOUEUR, MLV_rgba(0,255,0,255));
  
  tracer_hitbox(j->box);
  //MLV_draw_filled_circle(j->camera->x + j->box->pos->x, j->camera->y + j->box->pos->y, TAILLE_JOUEUR, MLV_rgba(255,255,0,127));
  
  
  while (proj != NULL){
      afficher_proj(proj);
      proj = proj->suivant;
  }
  
}


int player_collision_on_border(Joueur* j, Env* e, double vitesse_x1, double vitesse_y1, double vitesse_x2, double vitesse_y2){
    //printf("Probleme: bord droit: %lf + %lf %lf + %d\n",j->pos->x, TAILLE_JOUEUR,e->camera->x, e->t_x2);
    
    // gere le joueur et le bord droit
    if ((j->pos->x + vitesse_x1) >= (e->camera->x + vitesse_x2 + e->t_x2)){
        return 1;
    // gere le joueur et le bord gauche
    }else if ((j->pos->x + vitesse_x1) <= (e->camera->x + vitesse_x2 + e->t_x1)){
        return 2;
    // gere le joueur et le bord haut
    }else if ((j->pos->y + vitesse_y1) >= (e->camera->y + vitesse_y2 + e->t_y2)){
        return 3;
    // gere le joueur et le bord bas
    }else if ((j->pos->y + vitesse_y1) <= (e->camera->y + vitesse_y2 + e->t_y1)){
        return 4;
    }else{
        return 0;
    }

}


int player_collision_on_terrain(Joueur* j, Env* e, double vitesse_x1, double vitesse_y1, double vitesse_x2, double vitesse_y2){
    Env* e1 = e;
    int v_collision = 0;
    double dx_plus, dy_plus;
    
    while (e1 != NULL){
        v_collision = collision(j->box, e1->box, vitesse_x1, vitesse_y1, vitesse_x2, vitesse_y2, &dx_plus, &dy_plus);
        if (v_collision){
            // coller le joueur a l'environnement ici
            //j->effect_collision();
            return 1;
        }
        
        e1 = e1->suivant;
    }


    return 0;

}


void recupere_angle_vue(Joueur* j){
    int tire_x, tire_y;
    Vecteur* v = NULL;

    MLV_get_mouse_position(&tire_x, &tire_y);
    v = creer_vec_point_arriver(j->pos->x, j->pos->y, tire_x, tire_y);
    set_vue(j, v->angle);
    v = destroy_vec(v);
    
}


