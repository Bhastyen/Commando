#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <MLV/MLV_all.h>

#include "define.h"

#include "Hitbox.h"



Hitbox* creer_box(Pos* pos, double taille_x, double taille_y, int type){
	Hitbox* h = (Hitbox*) malloc(sizeof(Hitbox));
	if (h == NULL){
		fprintf(stderr,"ErrMemoire::creer_box()::probleme_allocation_box\n");
		exit(-1);
	}


	h->pos = creer_position(pos->x, pos->y);
	h->camera = creer_position(0.0, 0.0);

	h->taille_x = taille_x;

	h->taille_y = taille_y;
	
	h->type = type;

	h->suivant = NULL;


	return h;

}


Hitbox* ajouter_collision(Hitbox* box1, Hitbox* box2){
	Hitbox* h = box1;

	if (h == NULL){
		return box2;
	}

	while(h->suivant != NULL){
		h = h->suivant;
	}

	h->suivant = box2;


	return box1;

}


void deplacer_box(Hitbox* box, Pos* pos){
	Hitbox* h = box;

	while(h != NULL){
		deplacement_position(h->pos, pos->x, pos->y);
		h = h->suivant;
	}

}


int collision(Hitbox* h1, Hitbox* h2, double dx1, double dy1, double dx2, double dy2, double* dx_plus, double* dy_plus){
    int i = 0;
    int max;
    double r, v;
    double x1, y1, x2, y2, x0 = h1->pos->x, y0 = h1->pos->y;
    
    
    if (h1->taille_x >= h2->taille_x){
        v = sqrt(dx2*dx2+dy2*dy2);
        r = h2->taille_x;
    }else{
        v = sqrt(dx1*dx1+dy1*dy1);
        r = h1->taille_x;
    }
    
    max = 1/r*2*v;
    if (max == 0){
        max = r;
    }
        
    x2 = h2->pos->x + h2->camera->x + dx2;
    y2 = h2->pos->y + h2->camera->y + dy2;
    modifier_position(h2->pos, x2, y2);
    
    max = 1;
    while (i<max){
        x1 = x0 + h1->camera->x + (dx1-(i*dx1/max));
        y1 = y0 + h1->camera->y + (dy1-(i*dy1/max));
        modifier_position(h1->pos, x1, y1);
    
        if (collision_aux(h1, h2) || collision_aux(h2, h1)){
            // calcule de dx_plus dy_plus ici
            modifier_position(h1->pos, x0, y0);
            modifier_position(h2->pos, h2->pos->x - h2->camera->x - dx2, h2->pos->y - h2->camera->y - dy2);
            return 1;
        }
        
        i ++;
    }
    
    modifier_position(h1->pos, x0, y0);
    modifier_position(h2->pos, h2->pos->x - h2->camera->x - dx2, h2->pos->y - h2->camera->y - dy2);
    
    
    return 0;
    
}


int collision_aux(Hitbox* h1, Hitbox* h2){
    
    if (h1->type == CERCLE){
        return circleCollision(h1, h2);
    }else{
        return rectCollision(h1, h2);
    }

}


int circleCollision(Hitbox* h1, Hitbox* h2){
    
    if (h2->type == CERCLE){
        return circleCollisionOnCircle(h1, h2);
    }else{
        return circleCollisionOnRect(h1, h2);
    }

}


int rectCollision(Hitbox* h1, Hitbox* h2){
    
    if (h2->type == CERCLE){
        return rectCollisionOnCircle(h1, h2);
    }else{
        return rectCollisionOnRect(h1, h2);
    }

}


int circleCollisionOnCircle(Hitbox* h1, Hitbox* h2){
    double x, y, x0, y0;
    int max = 8;
    int i = 0;
    
    while (i<max){
        x = h1->pos->x + h1->taille_x*cos(i*(360/max)*(3.14/180));
        y = h1->pos->y + h1->taille_x*sin(i*(360/max)*(3.14/180));
        
        x0 = h2->pos->x - x;
        y0 = h2->pos->y - y;
        
        if (h2->taille_x < sqrt(x0*x0+y0*y0)){
            return 1;
        }
        
        i++;
    }
    
    
    return 0;

}


int rectCollisionOnRect(Hitbox* h1, Hitbox* h2){
   double x1 = h1->pos->x-h1->taille_x, y1 = h1->pos->y-h1->taille_y;
   double x2 = h1->pos->x+h1->taille_x, y2 = h1->pos->y-h1->taille_y;
   double x3 = h1->pos->x-h1->taille_x, y3 = h1->pos->y+h1->taille_y;
   double x4 = h1->pos->x+h1->taille_x, y4 = h1->pos->y+h1->taille_y;
   
   double x_h2 = h2->pos->x;
   double y_h2 = h2->pos->y;
   
      
   if (x1 > (x_h2 - h2->taille_x) && x1 < (x_h2 + h2->taille_x) && y1 > (y_h2-h2->taille_y) && y1 < (y_h2+h2->taille_y)){
       return 1;
   }else if (x2 > (x_h2 - h2->taille_x) && x2 < (x_h2 + h2->taille_x) && y2 > (y_h2-h2->taille_y) && y2 < (y_h2+h2->taille_y)){
       return 1;
   }else if (x3 > (x_h2 - h2->taille_x) && x3 < (x_h2 + h2->taille_x) && y3 > (y_h2-h2->taille_y) && y3 < (y_h2+h2->taille_y)){
       return 1;
   }else if (x4 > (x_h2 - h2->taille_x) && x4 < (x_h2 + h2->taille_x) && y4 > (y_h2-h2->taille_y) && y4 < (y_h2+h2->taille_y)){
       return 1;
   }
   
   
   return 0;
   
}


int circleCollisionOnRect(Hitbox* h1, Hitbox* h2){
    double x, y;
    double x_h2;
    double y_h2;
    int max = 8;
    int i = 0;
    
    
    while (i < max){
        x_h2 = h2->pos->x;
        y_h2 = h2->pos->y;
        
        x = h1->pos->x + h1->taille_x*cos(i*(360/max)*(3.14/180));
        y = h1->pos->y + h1->taille_x*sin(i*(360/max)*(3.14/180));
        
        if (x > (x_h2 - h2->taille_x) && x < (x_h2 + h2->taille_x) && y < (y_h2 - h2->taille_y) && y > (y_h2 + h2->taille_y)){
            return 1;
        }
        
        i++;
    }
    
    
    return 0;

}


int rectCollisionOnCircle(Hitbox* h1, Hitbox* h2){

    return circleCollisionOnRect(h2, h1);
    
}


Hitbox* supprimer_box(Hitbox* box){
	Hitbox* h = box;
	Hitbox* suivant = NULL;

	if (h == NULL){
		return h;
	}

	while (h != NULL){
		suivant = h->suivant;
		free(h);
		h = NULL;
		h = suivant;
	}

	box = NULL;
	return box;

}


void tracer_hitbox(Hitbox* box){

	if (box != NULL){
        
        if (box->type == CARRE){
            MLV_draw_rectangle((box->camera->x+box->pos->x)-box->taille_x, (box->camera->y+box->pos->y)-box->taille_y, box->taille_x*2, box->taille_y*2, MLV_rgba(0,255,0,255));
        }else if (box->type == CERCLE){
		    MLV_draw_circle((box->camera->x+box->pos->x), (box->camera->y+box->pos->y), box->taille_x, MLV_rgba(0,255,0,255));
        }

	}


}

