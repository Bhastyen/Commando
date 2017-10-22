/*
Nom: fonctions pour gerer les files
Auteur: Duraj Bastien
Date: 03/04/2017
Contenu: Prototype des fonctions de bases pour gerer les files
*/
#ifndef _FILE_H_
#define _FILE_H_

#include "Liste.h"

/*
  type File: representation en memoire de la structure de donnee File
*/
typedef struct {
  Liste* liste;
  Liste* fin;
} File;
  


/*

  file_vide: initialise une File qui ne contient rien 
  Input: X
  Output: renvoie un type pointeur sur une File 
  
*/
File* file_vide();

/*

  est_file_vide: determine si une File est vide
  Input: prends un pointeur sur une File
  Output: renvoie 0 si la file n'est pas vide et 1 si elle l'est 
  
*/
int est_file_vide(File* f);

/*

  enfile: rajoute un element a la fin de la File
  Input: prends un pointeur sur une File
  Output: renvoie un pointeur sur la nouvelle File
  
*/
File* enfile(File* f, element e);

/*

  defile: enleve le premier element d'une file et renvoie cette element
  Input: prends le pointeur d'un pointeur sur une File, sert pour la modification
  Output: renvoie le premier element de la file
  
*/
int defile(File** f);

/*

  affiche_file: affiche les elements de la file sous un certain format 
  Input: prends un pointeur sur une File
  Output: X
  
*/
void affiche_file(File* f);

/*

  vider_file: supprime chaque element de la file de la memoire et la file elle-même
  Input: prends un pointeur sur une File
  Output: renvoie la file vide
  
*/
File* vider_file(File* f);



#endif
