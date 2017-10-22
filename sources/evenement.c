#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include </usr/include/pthread.h>
#include <X11/Xlib.h>
#include <MLV/MLV_all.h>

#include "evenement.h"



void traite_event(int* entree, File* f){
    int* arret = &entree[4];
    int touche = entree[0];
    int clic = 0;

    if (touche == 27){
        *arret = 1;
    }else if (touche != 0){
        enfile(f, touche);
    }
    
    entree[0] = 0;

}


int sous_tache1(int* entree, File* f, pthread_mutex_t* mutex){

    while (!entree[4]){
        pthread_mutex_lock(mutex);     // lock des donnees
        MLV_get_event((MLV_Keyboard_button*) &entree[0],(MLV_Keyboard_modifier*) &entree[1],NULL,NULL,NULL,NULL,NULL,NULL,NULL);
        traite_event(entree, f);
        pthread_mutex_unlock(mutex);   // unlock
    }

    return 0;

}


int convert(data_event* data){

    sous_tache1(data->entree, data->file_event, &(data->mutex1));
    /* place restante pour d'autre sous tache */
    
    return 0;

}


void *thread_1(void* arg){

    convert((data_event*) arg);
    
    printf("Le thread s'est bien terminé\n");
    
    (void) arg;
    pthread_exit(0);
}


pthread_t init_thread_event(data_event* d){

   XInitThreads();
  
  
   pthread_t thread1;
  
   if (pthread_create(&thread1, NULL, thread_1, (void*) d)){
     perror("pthread_create");
     return EXIT_FAILURE;
   }
   
   
   return thread1;

}


data_event* fin_event(pthread_t* thread, data_event* data){

  if (pthread_join(*thread, NULL)) {
    perror("pthread_join");
    exit(EXIT_FAILURE);
  }
  
  
  if (data != NULL){
  
      if (data->entree != NULL){
        free(data->entree);
        data->entree = NULL;
      }
      
      data->file_event = vider_file(data->file_event);
      
      pthread_mutex_destroy(&data->mutex1);
      
      free(data);
      data = NULL;
  }
  
  
  return data;

}


data_event* init_data_event(void){
  int i;
  
  data_event* d = (data_event*) malloc(sizeof(data_event));
  if (d == NULL){
    fprintf(stderr,"ErrMemoire::init_data_event()::Probleme_allocation_memoire_data\n");
    exit(-1);
  }
  
  int* entree = (int*) malloc(sizeof(int)*5);
  if (entree == NULL){
    fprintf(stderr,"ErrMemoire:init_data_event()::Probleme_allocation_memoire_entree\n");
    exit(-1);
  }
  
  for (i=0;i<5;i++){
    entree[i] = 0;
  }
  
  d->entree = entree;
  d->file_event = file_vide();
  pthread_mutex_init(&(d->mutex1), NULL);   // PTHREAD_MUTEX_INITIALIZER;
  
  
  return d;

}


