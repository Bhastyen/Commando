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


int collision(Hitbox* h1, Hitbox* h2, double dx1, double dy1, double dx2, double dy2){
    int i = 0;
    int max;
    double r, v;
    double x1, y1, x2, y2;
    Hitbox* h3, h4;
    
    
    if (h1->taille_x >= h2->taille_x){
        v = sqrt(dx1*dx1+dy1*dy1);
        if (h2->type == CERCLE)
            r = h2->taille_x;
        else
            r = h2->taille_x/2.0;
    }else{
        v = sqrt(dx2*dx2+dy2*dy2);
        if (h2->type == CERCLE)
            r = h2->taille_x;
        else
            r = h2->taille_x/2.0;
    }
    
    max = 1/r*2*v;
    
    while (i<max){
        // recuperePoint(h1->pos, dx1, dy1, &x1, &y1);
        // recuperePoint(h2->pos, dx2, dy2, &x2, &y2);
        
        h3 = creer_box(creer_pos((x1+h1->camera->x), (y1+h1->camera->y)), h1->taille_x, h1->taille_y, h1->type);
        h4 = creer_box(creer_pos((x2+h2->camera->x), (y2+h2->camera->y)), h2->taille_x, h2->taille_y, h2->type);
    
        if (collision_aux(h3, h4)){
            return true;
        }
        
        h3 = supprimer_box(h3);
        h4 = supprimer_box(h4);
        
        i ++;
    }
    
    
    return false;
    
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
        x = h1->pos->x + h1->taille_x*cos(i*(360/max)*3.14/180);
        y = h1->pos->y + h1->taille_x*sin(i*(360/max)*3.14/180);
        
        x0 = h2->pos->x - x;
        y0 = h2->pos->y - y;
        
        if (sqrt(x0*x0+y0*y0) < h2->taille_x){
            return true;
        }
        
        i++;
    }
    
    
    return false;

}


int rectCollisionOnRect(Hitbox* h1, Hitbox* h2){
   double x1 = h1->pos->x, y1 = h1->pos->y;
   double x2 = h1->pos->x+h1->taille_x, y2 = h1->pos->y;
   double x3 = h1->pos->x, y3 = h1->pos->y+h1->taille_y;
   double x4 = h1->pos->x+h1->taille_x, y4 = h1->pos->y+h1->taille_y;
   
   int i;
   
   
   x_h2 = h2->pos->x;
   y_h2 = h2->pos->y;
      
   if (x1 > x_h2 && x1 < (x_h2 + h2->taille_x) && y1 > y_h2 && y1 < (y_h2+h2->taille_y)){
       return true;
   }else if (x2 > x_h2 && x2 < (x_h2 + h2->taille_x) && y2 > y_h2 && y2 < (y_h2+h2->taille_y)){
       return true;
   }else if (x3 > x_h2 && x3 < (x_h2 + h2->taille_x) && y3 > y_h2 && y3 < (y_h2+h2->taille_y)){
       return true;
   }else if (x4 > x_h2 && x4 < (x_h2 + h2->taille_x) && y4 > y_h2 && y4 < (y_h2+h2->taille_y)){
       return true;
   }
   
   
   return false;
   
}


int circleCollisionOnRect(Hitbox* h1, Hitbox* h2){
    double x, y, x0, y0;
    int max = 8;
    int i = 0;
    
    while (i<max){
        x = h1->pos->x + h1->taille_x*cos(i*(360/max)*3.14/180);
        y = h1->pos->y + h1->taille_x*sin(i*(360/max)*3.14/180);
        
        x_h2 = h2->pos->x;
        y_h2 = h2->pos->y;
        
        if (x > x_h2 && x < (x_h2 + h2->taille_x) && y > y_h2 && y < (y_h2+h2->taille_y)){
            return true;
        }
        
        i++;
    }
    
    
    return false;

}


int rectCollisionOnCircle(Hitbox* h1, Hitbox* h2){

    return circleCollisionOnRect(h2, h1);
    
}


int collision_box(Hitbox* box1, Hitbox* box2, double vitesse_x1, double vitesse_y1, double vitesse_x2, double vitesse_y2){
	double s1, s2, s3, s4, s5, s6, s7, s8, t1, t2, t3, t4, x1, x2, x, y1, y2, y, d;
	Hitbox* h1 = box1, *h2;

	if (box1 == NULL || box2 == NULL){
		return 0;
	}


	while (h1 != NULL){
		h2 = box2;
		
		t1 = h1->taille_x;
		t2 = h2->taille_x;
		t3 = h1->taille_y;
		t4 = h2->taille_y;

		x1 = h1->camera->x+h1->pos->x+vitesse_x1;
		x2 = h2->camera->x+h2->pos->x+vitesse_x2;
		y1 = h1->camera->y+h1->pos->y+vitesse_y1;
		y2 = h2->camera->y+h2->pos->y+vitesse_y2;

		while (h2 != NULL){
		    if (h1->type == CARRE && h2->type == CARRE){
			    s1 = x1-t1/2.0; s2 = x1+t1/2.0; s5 = x2-t2/2.0; s6 = x2+t2/2.0;
			    s3 = y1-t3/2.0; s4 = +y1+t3/2.0; s7 = y2-t4/2.0; s8 = y2+t4/2.0;
			    
			    if (s5 >= s1 && s5 <= s2){
			        if (s7 >= s3 && s7 <= s4){
			            return 1;
			        }else if (s8 >= s3 && s8 <= s4){
			            return 1;
			        }
			    }else if(s6 >= s1 && s6 <= s2){
			        if (s7 >= s3 && s7 <= s4){
			            return 1;
			        }else if (s8 >= s3 && s8 <= s4){
			            return 1;
			        }
			    }
		        
		    }else if (h1->type == CARRE && h2->type == CERCLE){  // cas non gerer quand un sommet n'est pas dans le cercle mais collision quand meme
		        s1 = x1-t1/2.0; s2 = x1+t1/2.0;
		        s3 = y1-t3/2.0; s4 = y1+t3/2.0;
		        
		        // test du sommet bas gauche
			    x = s1 - x2;
			    y = s3 - y2;

			    d = sqrt(x*x+y*y);
			    if (d <= t2){
				    return 1;
			    }
			    
		        // test du sommet haut gauche
			    x = s1 - x2;
			    y = s4 - y2;

			    d = sqrt(x*x+y*y);
			    if (d <= t2){
				    return 1;
			    }
			    
		        // test du sommet bas droit
			    x = s2 - x2;
			    y = s3 - y2;

			    d = sqrt(x*x+y*y);
			    if (d <= t2){
				    return 1;
			    }
			    
		        // test du sommet haut droit
			    x = s2 - x2;
			    y = s4 - y2;

			    d = sqrt(x*x+y*y);
			    if (d <= t2){
				    return 1;
			    }
			    
			}else if (h1->type == CERCLE && h2->type == CARRE){
		        s1 = x2-t2/2.0; s2 = x2+t2/2.0;
		        s3 = y2-t4/2.0; s4 = y2+t4/2.0;
		        
		        //printf("Probleme0: %lf %lf %lf %lf %lf %lf\n",s1,s2,s3,s4,x1,y1);
		        MLV_draw_rectangle(s1, s3, t2, t4, MLV_rgba(255,255,255,255));
		        
		        // test du sommet bas gauche
			    x = s1 - x1;
			    y = s3 - y1;
		        
		        //printf("Probleme1: %lf %lf\n",x,y);

			    d = sqrt(x*x+y*y);
			    if (d <= t1){
				    return 1;
			    }
			    
		        // test du sommet haut gauche
			    x = s1 - x1;
			    y = s4 - y1;
		        
		        //printf("Probleme2: %lf %lf\n",x,y);

			    d = sqrt(x*x+y*y);
			    if (d <= t1){
				    return 1;
			    }
			    
		        // test du sommet bas droit
			    x = s2 - x1;
			    y = s3 - y1;
		        
		        //printf("Probleme3: %lf %lf\n",x,y);

			    d = sqrt(x*x+y*y);
			    if (d <= t1){
				    return 1;
			    }
			    
		        // test du sommet haut droit
			    x = s2 - x1;
			    y = s4 - y1;
		        
		        //printf("Probleme4: %lf %lf\n",x,y);

			    d = sqrt(x*x+y*y);
			    if (d <= t1){
				    return 1;
			    }
			    
			}else if (h1->type == CERCLE && h2->type == CERCLE){
			    x = x1 - x2;
			    y = y1 - y2;

			    d = sqrt(x*x+y*y);
			    if ((d <= t1) || (d <= t2)){
				    return 1;
			    }
			}
			
			h2 = h2->suivant;
		}
		h1 = h1->suivant;
	}


	return 0;

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
            MLV_draw_rectangle((box->camera->x+box->pos->x)-box->taille_x/2, (box->camera->y+box->pos->y)-box->taille_y/2, box->taille_x, box->taille_y, MLV_rgba(0,255,0,255));
        }else if (box->type == CERCLE){
		    MLV_draw_circle((box->camera->x+box->pos->x), (box->camera->y+box->pos->y), box->taille_x, MLV_rgba(0,255,0,255));
        }

	}


}

