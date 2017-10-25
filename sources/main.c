#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include </usr/include/pthread.h>
#include <X11/Xlib.h>
#include <MLV/MLV_all.h>

#include "define.h"
#include "utilitaire.h"
#include "joueur.h"
#include "env.h"
#include "ennemi.h"
#include "Projectile.h"
#include "Hitbox.h"
#include "File.h"
#include "Vecteur.h"
#include "Trajectoire.h"
#include "evenement.h"



void recupere_angle_vue(Joueur* j);
void gere_event(int* arret, int* grille, int* hitbox, int* trajet);
void gestion_deplacement(Joueur* j, Env* e);
void gere_tire(Joueur* j);
void gestion_camera(Joueur* j, Env* e, double dx, double dy);


int main(int argc, char** argv){
  int l,la;
  int arret = 0;
  int grille = 0;
  int hitbox = 0;
  int trajet = 0;
  clock_t temps_actuel = clock();
  //data_event* d = NULL;
  //pthread_t event;
  //int touche;   //MLV_Keyboard_button
  //int etat;   //MLV_Keyboard_modifier
  Joueur* j = NULL;
  Env* e = NULL;
  
  
  if (argc < 3){
    usage(argv[0],"<entier positif>","compris entre 800 et 1500 pixels","<entier positif>","compris entre 600 et 1000 pixels",NULL);
    exit(-1);
  }
  
  l = atoi(argv[1]);
  la = atoi(argv[2]);

  if (l < 800 || la < 600 || l > 1500 || la > 1000){
    usage(argv[0],"<entier positif>","compris entre 800 et 1500 pixels","<entier positif>","compris entre 600 et 1000 pixels",NULL);
    exit(-1);
  }
  
  srand(time(NULL));
  
  MLV_create_window("Commando","Commando",l,la);
  
  e = gen_env(-2*l, -2*la, 2*l, 2*la, 0.05, 0);
  j = creer_joueur(creer_position(l/2,la/2));
  j->vitesse = DT*(2.0/3.0);

  //XInitThreads();
  
  //d = init_data_event();
  //event = init_thread_event(d);
  
  while (arret == 0){
    MLV_actualise_window();
    recupere_angle_vue(j);
    gere_tire(j);
    gestion_deplacement(j, e);   // gestion des collisions
    gere_event(&arret, &grille, &hitbox, &trajet);
    tracer_env(e);
    if (grille){
        tracer_grille_env(e);
    }
    afficher_joueur(j);
    //afficher_joueur(ennemi);   // a appliquer a chaque ennemi dans une liste d'ennemi
    // set_vie(j, 100)  // pour chaque joueur
    MLV_actualise_window();
    
    if ((clock()-temps_actuel)/(double)CLOCKS_PER_SEC < DT){
        MLV_wait_milliseconds(DT-(clock()-temps_actuel)/(double)CLOCKS_PER_SEC);
    }
    
    MLV_clear_window(MLV_rgba(0,0,0,255)); // nettoie la fenetre pour mettre a jour l'affichage
  }
  
  e = vider_env(e);
  //d = fin_event(&event,d);
  
  MLV_free_window();

  exit(0);

}


void gere_event(int* arret, int* grille, int* hitbox, int* trajet){
   
   *grille = 0;
   *hitbox = 0;
   *trajet = 0;

   if (MLV_get_keyboard_state(27) == MLV_PRESSED){
       *arret = 1;
   }
   
   if (MLV_get_keyboard_state(MLV_KEYBOARD_g) == MLV_PRESSED){
       *grille = 1;
   }
   
   if (MLV_get_keyboard_state(MLV_KEYBOARD_h) == MLV_PRESSED){
       *hitbox = 1;
   }
   
   if (MLV_get_keyboard_state(MLV_KEYBOARD_t) == MLV_PRESSED){
       *trajet = 1;
   }
  
}


void gere_tire(Joueur* j){
    double x, y;
    clock_t temps_actuel = clock();
    Projectile* proj = NULL;
    
    if (j != NULL){
        if (MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED && (temps_actuel-j->cadence_tire)/(double)CLOCKS_PER_SEC >= (0.4/DT)){
            point_arrivee_vec(j->vue,&x,&y);
            proj = creer_projectile(creer_position(x,y), j->vue->angle);
            j->p = ajouter_proj(j->p, proj);
            
            j->cadence_tire = clock();
        }
    
    }/*else if (touche == MLV_BUTTON_MIDDLE){
        set_position(j, creer_position(0.0,j->vitesse));
    }else if (touche == MLV_BUTTON_RIGHT){
        set_position(j, creer_position(-j->vitesse,0.0));
    }*/

}


void gestion_deplacement(Joueur* j, Env* e){
   Projectile* proj = NULL;
   double proj_vx = 0, proj_vy = 0;
   
   j->p = supprimer_proj(j->p);  // suppression des projs terminer
   proj = j->p;   // sinon changement non pris en compte
   
   
   if (MLV_get_keyboard_state(122) == MLV_PRESSED){   // fleche du haut
      if (player_collision_on_border(j, e, 0.0, -j->vitesse, 0.0, 0.0) != 4 && !player_collision_on_terrain(j, e, 0.0, -j->vitesse, 0.0,0.0)){
          gestion_camera(j, e, 0.0, j->vitesse);
      }else{
          // completer le deplacement pour coller l'obstacle: gestion_camera(j, e, dx_plus, dy_plus);
      }
   }
   
   if (MLV_get_keyboard_state(115) == MLV_PRESSED){     // fleche du bas
      if (player_collision_on_border(j, e, 0.0, j->vitesse, 0.0, 0.0) != 3 && !player_collision_on_terrain(j, e, 0.0, j->vitesse, 0.0, 0.0)){
          gestion_camera(j, e, 0.0, -j->vitesse);
      }
   }

   if (MLV_get_keyboard_state(100) == MLV_PRESSED){     // fleche droite
      if (player_collision_on_border(j, e, j->vitesse, 0.0, 0.0, 0.0) != 1 && !player_collision_on_terrain(j, e, j->vitesse, 0.0, 0.0, 0.0)){
          gestion_camera(j, e, -j->vitesse, 0.0);
      }
   }
   
   if (MLV_get_keyboard_state(113) == MLV_PRESSED){     // fleche gauche
      if (player_collision_on_border(j, e, -j->vitesse, 0.0, 0.0, 0.0) != 2 && !player_collision_on_terrain(j, e, -j->vitesse, 0.0, 0.0, 0.0)){
          gestion_camera(j, e, j->vitesse, 0.0);
      }
   }
   
   
   while (proj != NULL){
      
      calcul_vitesse_absolu_proj(proj, &proj_vx, &proj_vy);
       
      if (fire_collision_on_terrain(proj, e, proj_vx, proj_vy, 0.0, 0.0)||
          fire_collision_on_border(proj, e, proj_vx, proj_vy, 0.0, 0.0)){
          //proj->acceleration = 0.0; 
          //change_direction_proj(proj, 45);
          proj->zombie = 1;
      }
      
      deplace_proj(proj);
      if (!avancer(proj->trajet, proj->vitesse)){
          proj->zombie = 1;
      }
      proj = proj->suivant;
   }
   
   
   /*if (MLV_get_keyboard_state(122) == MLV_PRESSED){
      if (j->pos->y > e->camera->y+e->t_y1){
          if (j->pos->y < 100){  
              gestion_camera(j, e, 0.0, j->vitesse);
          }else{
              set_position(j, creer_position(0.0, -j->vitesse));
          }
      }
   }
   
   if (MLV_get_keyboard_state(115) == MLV_PRESSED){
      if (j->pos->y < e->camera->y+e->t_y2){
          if (j->pos->y > la-100){
              gestion_camera(j, e, 0.0, -j->vitesse);
          }else{
              set_position(j, creer_position(0.0, j->vitesse));
          }
      }
   }

   if (MLV_get_keyboard_state(100) == MLV_PRESSED){
      if (j->pos->x < e->camera->x+e->t_x2){
          if (j->pos->x > l-100){
              gestion_camera(j, e, -j->vitesse, 0.0);
          }else{
              set_position(j, creer_position(j->vitesse, 0.0));
          }
      }
   }
   
   if (MLV_get_keyboard_state(113) == MLV_PRESSED){
      if (j->pos->x > e->camera->x+e->t_x1){
          if (j->pos->x < 100){
              gestion_camera(j, e, j->vitesse, 0.0);
          }else{
              set_position(j, creer_position(-j->vitesse, 0.0));
          }
      }
   }*/


}


void gestion_camera(Joueur* j, Env* e, double dx, double dy){
    Projectile* proj = j->p;
    Env* e1 = e;
    
    while (e1 != NULL){
        deplacement_position(e1->camera, dx, dy);
        deplacement_position(e1->box->camera, dx, dy);
        
        e1 = e1->suivant;
    }
    
    while (proj != NULL){
        deplacement_position(proj->camera, dx, dy);
        deplacement_position(proj->box->camera, dx, dy);
    
        proj = proj->suivant;
    }
    
    
}


void handler_collider(Joueur* j, Env* e){   // ne sert a rien
    
    
    // gere les projectiles ennemis et le bord
    
    // gere le joueur et les projectiles ennemis
    
    // gere le terrain et les projectiles du joueur
    
    // gere le terrain et les projectiles ennemis
    
    
}


// MLV_create_full_screen_window()
// MLV_disable_full_screen()
// MLV_draw_bezier_curve()
// MLV_draw_text_box_with_font()
// MLV_enable_full_screen()
// MLV_free_window()
// MLV_get_event()
// MLV_get_mouse_position()
// MLV_get_random_integer()
// MLV_get_time()
// MLV_is_full_screen()
// MLV_left_shift_key_was_pressed()
// MLV_resize_image_with_proportions()
// MLV_rgba()
// MLV_rotate_and_scale_image()
// MLV_update_window()
// MLV_wait_event()
// MLV_wait_milliseconds()
// MLV_wait_mouse()
// MLV_wait_keyboard_or_mouse()
// MLV_wait_keyboard_or_mouse_or_seconds()
// MLV_actualise_window()
// MLV_change_default_font()
// MLV_change_window_size()
// MLV_clear_window()



