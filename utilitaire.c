/*
Nom: fonction utilitaire
Auteur: Duraj Bastien
Date: 24/02/2017
Contenu: fonction usage: affiche le manuel du programme
         fonction operation: renvoie le code de la fonction ou de l'operation
         fonction operande: renvoie le flottant d'une chaine
         fonction mon_realloc: augmente dynamiquement une chaine dynamique de n caractere
         fonction str_concat: concatene deux chaines dynamique entre elle 
         fonction reverse: renverse une chaine de caractere, ne la modifie pas cree une nouvelle chaine
         fonction sliceof: renvoie la sous_chaine d'une chaine de caractere d'un indice a un autre (exclut)
         fonction est_nombre: indique si une chaine represente un nombre reel(i.e. entier) ou pas 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>


// Fonction d'usage

void usage(char* s,...){  // fonction d'usage a argument variable
  char* ch = NULL;  // servira a parcourir la liste a argument variable
  
  va_list liste;  // creer une va_liste

  va_start(liste,s); // initialise liste avec le premiere argument

  fprintf(stderr,"\nUsage: %s ",s);

  ch = va_arg(liste,char *);   // recupere le premiere element de type char *
  while (ch != NULL){    // s'arrete quand un pointeur NULL est recuperer (cas d'arret)
    fprintf(stderr,"%s ",ch);   // affiche la chaine
    ch = va_arg(liste,char *);   // recupere la prochaine chaine a afficher
  }

  fprintf(stderr,"\n"); // termine par un saut de ligne

  va_end(liste);  // ferme la liste

}


// Fonction de recuperation

double operande(char* arg){  // recupere un argument et le transforme en double

  return atof(arg);

}


int operation(char* arg){   // recupere une operation (une chaine) et renvoie un code lui correspondant

  if (strcmp("+",arg) == 0){
    return 1;
  }else if (strcmp("-",arg) == 0){
    return 2;
  }else if (strcmp("*",arg) == 0){
    return 3;
  }else if (strcmp("/",arg) == 0){
    return 4;
  }else if (strcmp("^",arg) == 0){
    return 5;
  }else if (strcmp("exp",arg) == 0){
    return 6;
  }else if (strcmp("ln",arg) == 0){
    return 7;
  }else if (strcmp("log",arg) == 0){
    return 8;
  }else if (strcmp("sqrt",arg) == 0){
    return 9;
  }else if (strcmp("cos",arg) == 0){
    return 10;
  }else if (strcmp("sin",arg) == 0){
    return 11;
  }else if (strcmp("tan",arg) == 0){
    return 12;
  }else if (strcmp("acos",arg) == 0){
    return 13;
  }else if (strcmp("asin",arg) == 0){
    return 14;
  }else if (strcmp("atan",arg) == 0){
    return 15;
  }else if (strcmp("fib",arg) == 0){
    return 16;
  }else if (strcmp("fact",arg) == 0){
    return 17;
  }else if (strcmp("pgcd",arg) == 0){
    return 18;
  }else if (strcmp("%",arg) == 0){
    return 19;
  }else{
    return 0;  // si l'operation n'existe on renvoie 0 pour prevenir le programme
  }

}



// Fonction sur des chaine de caracteres, utiliser lors du calcul de la factoriel en chaine de caractere

char* mon_realloc(char* chaine, int caractere_sup){  // augmente la taille une chaine de caractere de caractere_sup element
    char* chaine_tmp = strdup(chaine); // cree une copie de la chaine pour ne pas la perdre en cas de probleme
    int taille; int i;
    
    chaine_tmp = (char*) realloc(chaine_tmp,(strlen(chaine_tmp)+caractere_sup+1)*sizeof(char));  // reallou de la memoire supplementaire (+1 pour le '\0') 
    if (chaine_tmp == NULL){  // verifie que l'operation a marcher sinon on informe l'utilisateur
        fprintf(stderr,"ErrMemoire::Probleme allocation memoire!\n");
        exit(-1);
    }
    chaine = chaine_tmp;  // recupere la nouvelle chaine de taille chaine + caractere_sup
    
    if (strlen(chaine)+caractere_sup != 0){   // verifie le cas particulier d'une chaine de taille 0
        chaine[strlen(chaine)+caractere_sup] = '\0';  // rajoute un '\0' a la nouvelle fin de chaine
    }else{
        chaine[0] = '\0';  // mets la fin de la chaine au premier caractere
    }
    
    taille = strlen(chaine);  // sauvegarde la taille car celle ci va changer 
    for (i=0;i<caractere_sup;i++){
        chaine[taille+i] = '0';  // de l'ancienne taille a la nouvelle on mets un '0' pour eliminer les '\0' entre
    }
    
    return chaine;  // renvoie la chaine de taille augmenter avec le '\0' au bonne endroit 

}


char* str_concat(char* ch1, char* ch2){ // concatene deux chaines avec un realloc
    int n = strlen(ch1);  // sauvegarde la taille
    int i;
    
    ch1 = mon_realloc(ch1,strlen(ch2));   // utilise mon_realloc pour augmenter la taille de la chaine de strlen(ch2) caractere 
    
    for (i=n;i<strlen(ch1);i++){
        ch1[i] = ch2[i-n]; // recopie en partant de la fin la chaine ch2 dans la nouvelle partie libre de ch1 
    }

    return ch1; // retourne ch1 concatene a ch2

}


char* reverse(char* chaine){ // renverse une chaine sans la modifier
    int i;  
    char tmp;  
    
    char* resultat = strdup(chaine); // recupere une copie de la chaine pour ne pas la modifier
    
    for (i=0;i<(strlen(resultat)/2);i++){ // boucle renversant la copie de la chaine 
        tmp = resultat[i]; // sauvegarde le caractere pour l'echange
        
        resultat[i] = resultat[(strlen(resultat)-1)-i]; // on echange le caractere de debut avec le caractere de fin
        resultat[(strlen(resultat)-1)-i] = tmp; // on recupere le caractere de debut de chaine
    }
    
    return resultat; // on renvoie le resultat

}


char* sliceof(char* chaine, int depart, int fin){ // creer une sous chaine de depart a fin
    char* sous_chaine = NULL;  // contiendra la sous chaine
    int i;
    
    if (depart > fin){  // on verifie que la fin soit bien superieur au debut
        puts("Vos indice depart est trop grand");
        exit(-1);
    }
    
    sous_chaine = (char *) malloc((fin-depart+1)*sizeof(char)); // on alloue de l'espace memoire pour la sous chaine
    if (sous_chaine == NULL){  // on informe l'utilisateur s'il y a eu un probleme
        fprintf(stderr,"ErrMemoire::Probleme allocation memoire!\n");
        exit(-1);
    }
    sous_chaine[fin-depart] = '\0'; // on mets le nouveau caractere de fin de chaine 
    
    for (i=0;i<(fin-depart);i++){  // on copie les caractere de la chaine de l'indice depart a fin exclu
        sous_chaine[i] = chaine[i+depart];
    }
    
    return sous_chaine; // on retourne la sous_chaine

}


int est_nombre(char* chaine){  // renvoie 1 si la chaine represente un reel ou un entier
    int i; 
    int compteur = 0;  // compte le nombre de '.' et donc de virgule
    
    for (i=0;i<strlen(chaine);i++){
        if (i == 0){  // verifi qu'une virgule ne se trouve pas en debut de nombre
            if (chaine[i] == '.'){ // renvoie faux si on a bien une virgule
                return 0;
            }
        }
        
        if (chaine[i] < '0' || chaine[i] > '9'){  // on regarde si le caractere n'est pas un chiffre
            if (chaine[i] != '.' || (compteur >= 1 && chaine[i] == '.')){    // on regarde s'il s'agit d'un caractere autre q'un point ou si c'est la deuxieme virgule
                return 0;  // renvoie faux si c est le cas
            }else{
                compteur++;  // sinon augmente le nombre de virgule croiser de 1
            }    
        }
    }
    
    return 1;  // si on a pas croiser de caractere different d'un chiffre ou une seule virgule au max on renvoie vrai

}




