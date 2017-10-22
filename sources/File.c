/*
Nom: Fonctions sur les Files
Auteur: Duraj Bastien
Date: 03/04/2017
Contenu: Code des fonctions du type File
*/
#include <stdio.h>
#include <stdlib.h>

#include "File.h"



File* file_vide(){
  File* f = NULL;

  f = (File*) malloc(sizeof(File));
  f->liste = NULL;
  f->fin = NULL;

  return f;

}


int est_file_vide(File* f){

  if (f != NULL){
    return (est_vide(f->liste) || est_vide(f->fin));
  }

  return 0;

}


File* enfile(File* f, element e){
  if (!f){
    return f;
  }

  Liste* l = insere_element(creer_liste_vide(),e);

  if (!est_file_vide(f)){
    f->fin->suivant = l;
    f->fin = l;
  }else{
    f->liste = l;
    f->fin = l;
  }

  return f;

}


int defile(File** f){
  Liste* l;
  element el;
  
  if (!(*f) || est_file_vide(*f)){
    fprintf(stderr,"ErrValue::defile()::argument NULL\n");
    exit(-1);
  }

  l = (*f)->liste;
  el = (*f)->liste->objet;
  (*f)->liste = (*f)->liste->suivant;

  free(l);

  return el;

}


void affiche_file(File* f){
  Liste* f1;
  
  if (!f){
    printf("vide\n");
    return ;
  }

  f1 = f->liste;

  if (!est_vide(f1)){
    printf("%d ",f1->objet);
    f1=f1->suivant;
    while (!est_vide(f1)){
      printf("<- %d ",f1->objet);
      f1=f1->suivant;
    }
    printf("\n");
  }else{
    printf("vide\n");
  }

}


File* vider_file(File* f){
  Liste* l;
  Liste* suivant;

  if (!f){
    return f;
  }

  l = f->liste;

  while (!est_vide(l)){
    suivant = l->suivant;
    free(l);
    l = suivant;
  }

  f->fin = NULL;
  f->liste = NULL;

  free(f);
  f = NULL;
  
  return f;
  
}

