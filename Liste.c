/*
Nom: Fonctions des listes
Auteur: Duraj Bastien
Date: 03/04/2017
Contenu: Code des fonctions du type Liste
*/
#include <stdio.h>
#include <stdlib.h>
#include "Liste.h"


Liste* creer_liste_vide(){

  return NULL;

}



int est_vide(Liste* l){

  return (l==NULL);

}



Liste* insere_element(Liste* l, element el){
  Liste* cel;

  cel = (Liste*) malloc(sizeof(Liste));
  cel->objet = el;
  cel->suivant = l;
  
  return cel;
  
}




Liste* vider_liste(Liste* l){

  if (l == NULL){
    return NULL;
  }
  
  Liste* suivant = l->suivant;
  free(l);
  
  return vider_liste(suivant);

}



Liste* supprime_liste(Liste* l, int indice){
  int compteur=0;
  Liste* prec = NULL;
  Liste* p=l;
  prec = NULL;

  if (p == NULL){
    return p;
  }
  
  while (indice!=compteur){
    prec = p;
    p=p->suivant;
    if (p == NULL){
      fprintf(stderr,"ErrParam::supprime_liste()::indice_trop_grand\n");
      exit(-1);
    }
    compteur ++;
  }

  if (prec != NULL){
    prec->suivant = p->suivant;
    free(p);
  }else{
    prec = p;
    p=p->suivant;
    free(prec);

    return p;
  }
  
  return l;

}



void affiche_liste(Liste* l){
  Liste* l1 = l;

  if (!est_vide(l1)){
    printf("%d ",l1->objet);
    l1=l1->suivant;
    while (!est_vide(l1)){
      printf("-> %d ",l1->objet);
      l1=l1->suivant;
    }
    printf("\n");
  }else{
    printf("vide\n");
  }
  
}



