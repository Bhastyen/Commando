#include <stdio.h>
#include <stdlib.h>

#include "define.h"
#include "joueur.h"



Pos* creer_position(double x, double y){
	Pos* pos = (Pos*) malloc(sizeof(Pos));
	if (pos == NULL){
		fprintf(stderr,"ErrMemoire::creer_position()::probleme_allocation_memoire_position\n");
		exit(-1);
	} 


	pos->x = x;
	pos->y = y;

	return pos;

}


void modifier_position(Pos* pos, double x, double y){
	
	if (pos != NULL){
		pos->x = x;
		pos->y = y;
	}

}


void modifier_position_de_position(Pos* pos1, Pos* pos2){
	
	if (pos1 == NULL || pos2 == NULL){
		return ;
	}


	pos1->x = pos2->x;
	pos1->y = pos2->y;

}


void deplacement_position(Pos* pos, double x, double y){
	
	if (pos != NULL){
		pos->x += x;
		pos->y += y;
	}


}


Pos* supprimer_position(Pos* pos){
	
	if (pos != NULL){
		free(pos);
	}

	return pos;

}

