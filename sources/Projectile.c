#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>

#include "define.h"

#include "Projectile.h"



Projectile* creer_projectile(Pos* pos, double angle){
    double t[3] = {3.0, angle, 500.0};

    Projectile* p = (Projectile*) malloc(sizeof(Projectile));
    if (p == NULL){
       fprintf(stderr,"ErrMemoire::creer_projectile()::probleme_allocation_memoire_proj\n");
       exit(-1);
    }
    
    
    p->pos = creer_position(pos->x, pos->y);
    p->camera = creer_position(0.0, 0.0);
    
    p->vie = 100;
    p->degat = 25;
    p->zombie = 0;
    p->portee = 200.0;
    p->vitesse = 1.0*DT;
    p->acceleration = 0.0;
    
    p->box = creer_box(p->pos, TAILLE_PROJECTILE, TAILLE_PROJECTILE, CARRE);
    p->trajet = creer_trajectoire_tab(p->pos->x, p->pos->y, t);  //gen_tab_trajectoire(angle, 500.0, 3)
    p->suivant = NULL;
    
    return p;

}


Projectile* ajouter_proj(Projectile* p1, Projectile* p2){
    Projectile* p = p1;
    
    if (p == NULL){
        return p2;
    }
    
    while(p->suivant != NULL){
        p = p->suivant;
    }
    
    p->suivant = p2;
    
    return p1;

}


Projectile* supprimer_tout_proj(Projectile* p){


    return NULL;

}


Projectile* suppr_prj(Projectile* p){

    if (p == NULL){
        return NULL;
    }
    
    p->pos = supprimer_position(p->pos);
    p->camera = supprimer_position(p->camera);
    
    p->box = supprimer_box(p->box);
    p->trajet = destroy_trajectoire(p->trajet);
    
    free(p);
    p = NULL;
    
    return p;

}


Projectile* supprimer_proj(Projectile* p){
    Projectile* p_debut = p;
    Projectile* p1 = p;
    Projectile* p2 = NULL;
    Projectile* p3 = NULL;   // permet de relier les elements entre eux
    
    int debut = 1;
    
    if (p == NULL){
        return NULL;
    }
    
    
    while (p1 != NULL){
        if (p1->zombie){
            p2 = p1->suivant;
            p1 = suppr_prj(p1);
            p1 = p2;
            if (debut == 0){
                p3->suivant = p1;
                p3 = p1;
            }else if (debut == 1){
                p_debut = p1;
            }
            
        }else{ 
            p3 = p1;
            p1 = p1->suivant;
            debut = 0;
        }
    }


    return p_debut;

}


void deplace_proj(Projectile* proj){
   Vecteur* v = NULL;
   Vecteur* v1 = NULL;
   double x,y;
   int v_actu;
   
   
   if (proj != NULL){
      if (proj->vitesse < 0.0){
          proj->vitesse = 0.0;
      }
      
      if (proj->trajet->vec_actuel != -1){
          v_actu = proj->trajet->vec_actuel;
          v1 = getVec(proj->trajet->direction, v_actu);
          
          v = creer_vec(v1->pos->x, v1->pos->y, v1->angle, proj->trajet->position_vec);
          point_arrivee_vec(v, &x, &y);
          
          proj->pos->x = x;
          proj->pos->y = y;
          
          proj->box->pos->x = x;
          proj->box->pos->y = y;
       
          proj->vitesse += proj->acceleration;
      }
   }
   
   destroy_vec(v);

}


void change_direction_proj(Projectile* proj, double angle){
   Vecteur* v = NULL;
   
   if (proj != NULL){
       v = getVec(proj->trajet->direction, proj->trajet->vec_actuel);
        
       v->angle += angle;
       v->angle = (double) ((int) v->angle % 360);
   }

}


void afficher_proj(Projectile* proj){

    if (proj != NULL){
        MLV_draw_filled_circle(proj->camera->x + proj->pos->x, proj->camera->y + proj->pos->y, 5.0, MLV_rgba(0,0,255,255));    //camera_x + camera_y + 
        tracer_hitbox(proj->box);
        MLVtracer_trajet(proj->trajet);
    }

}


void affiche_proj_term(Projectile* proj){
   Projectile* p = proj;
   
   while(p != NULL){
      fprintf(stdout,"%p ",p);
      p = p->suivant;
   }
   fprintf(stdout,"\n");
   
}


void calcul_vitesse_absolu_proj(Projectile* proj, double* proj_vx, double* proj_vy){
   Vecteur* v = NULL;
   Vecteur* v1 = NULL;
   double x,y;
   int v_actu;
   
   if (proj != NULL){
      if (proj->vitesse < 0.0){
          proj->vitesse = 0.0;
      }
      
      if (proj->trajet->vec_actuel != -1){
          v_actu = proj->trajet->vec_actuel;
          v1 = getVec(proj->trajet->direction, v_actu);
          
          v = creer_vec(v1->pos->x, v1->pos->y, v1->angle, proj->trajet->position_vec);
          point_arrivee_vec(v, &x, &y);
          
          *proj_vx = x - proj->pos->x;
          *proj_vy = y - proj->pos->y;
       
          proj->vitesse += proj->acceleration;
      }
   }

}


int fire_collision_on_border(Projectile* p, Env* e, double vitesse_x1, double vitesse_y1, double vitesse_x2, double vitesse_y2){
    Projectile* proj = p;
    
    while (proj != NULL){
    
        // gere le projectile et le bord droit
        if ((proj->camera->x+proj->pos->x+vitesse_x1) >= (e->camera->x + vitesse_x2 + e->t_x2)){        // + TAILLE_PROJECTILE?
            return 1;
        // gere le projetile et le bord gauche
        }else if ((proj->camera->x+proj->pos->x+vitesse_x1) <= (e->camera->x + vitesse_x2 + e->t_x1)){
            return 2;
        // gere le projetile et le bord haut
        }else if ((proj->camera->y+proj->pos->y+vitesse_y1) >= (e->camera->y + vitesse_y2 + e->t_y2)){
            return 3;
        // gere le projetile et le bord bas
        }else if ((proj->camera->y+proj->pos->y+vitesse_y1) <= (e->camera->y + vitesse_y2 + e->t_y1)){
            return 4;
        }
        
        proj = proj->suivant;
    
    }

}


int fire_collision_on_terrain(Projectile* p, Env* e, double vitesse_x1, double vitesse_y1, double vitesse_x2, double vitesse_y2){
    Env* e1 = e;
    double dx_plus, dy_plus;
    
    while (e1 != NULL){
        
        if (collision(p->box, e1->box, vitesse_x1, vitesse_y1, vitesse_x2, vitesse_y2, &dx_plus, &dy_plus)){
            // deplacer_proj(dx_plus, dy_plus);
            // proj->effect_collision();
            return 1;
        }
        
        e1 = e1->suivant;
    }
   
   
    return 0;

}



