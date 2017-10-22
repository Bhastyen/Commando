/*
Nom: fonctions pour gerer les listes
Auteur: Duraj Bastien
Date: 03/04/2017
Contenu: Prototype des fonctions de bases pour gerer les listes
*/
#ifndef _LISTE_H_
#define _LISTE_H_

typedef int element;

/*
  type Liste: representation en memoire de la structure de donnee Liste
*/
struct cellule{

  element objet;
  struct cellule* suivant;

};

typedef struct cellule Liste;


/*

  creer_liste_vide: initialise une Liste qui ne contient rien 
  Input: X
  Output: renvoie un type pointeur sur une Liste
  
*/
Liste* creer_liste_vide();

/*

  est_vide: determine si une Liste est vide
  Input: prends un pointeur sur une Liste
  Output: renvoie 0 si la Liste n'est pas vide et 1 si elle l'est 
  
*/
int est_vide(Liste* l);

/*

  insere_element: rajoute un element au debut de la Liste
  Input: prends un pointeur sur une Liste et un element
  Output: renvoie un pointeur sur la nouvelle Liste
  
*/
Liste* insere_element(Liste* l, element el);

/*

  vider_Liste: supprime chaque element de la Liste de la memoire et la Liste elle-même
  Input: prends un pointeur sur une Liste
  Output: renvoie la Liste vide
  
*/
Liste* vider_liste(Liste* l);

/*

  supprime_liste: enleve un element d'une Liste d'un indice precis
  Input: prends une liste et un indice, fait une erreur si celui ci est trop grand
  Output: renvoie la liste modifier
  
*/
Liste* supprime_liste(Liste* l, int indice);

/*

  affiche_Liste: affiche les elements de la Liste sous un certain format 
  Input: prends un pointeur sur une Liste
  Output: X
  
*/
void affiche_liste(Liste* p);


#endif

