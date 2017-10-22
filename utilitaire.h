/*
Nom: fonctions utiles
Auteur: Duraj Bastien
Date: 24/02/2017
Contenu: Prototype de fonctions diverses qui serviront pour 
         la calculatrice mais aussi pour d'autre programme
*/

#ifndef UTILITAIRE
#define UTILITAIRE


/*

  Usage: Affiche un nombre de chaine de caractere non determiner, sert a decrire l'usage du programme
  Input: prends un nombre indeterminer de chaine,
         attention la derniere chaine devra etre un pointeur NULL 
         pour que la fonction s'arrete correctement
  Output: ne renvoi rien

*/
void usage(char* s,...);

/*

  operation: renvoie le code entier associer a une chaine representant une operation ou une fonction
  Input: une chaine representant une operation ou une fonction
  Output: type int, un code de 1 a 19, 0 voulant dire que l'operateur n'existe pas
  
*/
int operation(char* arg);

/*

  operande: permet de recuperer le flottant correspondant a une chaine
  Input: une chaine representant un flottant
  Output: type double, le flottant correspondant
  
*/
double operande(char* arg);

/*

  mon_realloc: augmente dynamiquement une chaine de caractere de n caractere 
  Input: une chaine, attention doit avoir ete creer dynamiquement par un malloc ou un calloc
  Output: type char*, la chaine avec sa nouvelle taille et le '\0' au bonne endroit,
          les nouveaux caracteres sont initialiser a '0'
  
*/
char* mon_realloc(char* chaine, int n);

/*

  str_concat: concatene deux chaines creer dynamiquement
  Input: deux chaines a concatene, attention a l'ordre
  Output: type char*, renvoie la chaine contenant la concatenation
  
*/
char* str_concat(char* ch1, char* ch2);

/*

  reverse: permet de recuperer l'inverse de la chaine creer dynamiquement
  Input: une chaine a renverser
  Output: type char*, la chaine renverser il s'agit d'une copie
  
*/
char* reverse(char* chaine);

/*

  sliceof: permet de recuperer la sous chaine d'une chaine de l'indice depart a l'indice fin exclu
  Input: une chaine a couper(char*), un indice de depart(int) et un indice de fin(int)
  Output: type char*, renvoie la sous chaine creer dynamiquement avec un malloc
  
*/
char* sliceof(char* chaine, int depart, int fin);

/*

  est_nombre: dit si une chaine represente un reel(i.e. entier) ou pas
  Input: une chaine quelconque
  Output: type int, 0 s'il ne s'agit pas d'un reel(i.e. entier), 1 s'il s'agit bien d'un reel(i.e. entier)
  
*/
int est_nombre(char* chaine);

#endif
