#ifndef EVENT_H_INCLUDED
#define EVENT_H_INCLUDED

#include "File.h"


typedef struct data{

  int* entree;
  File* file_event;
  
  pthread_mutex_t mutex1;

} data_event;



data_event* init_data_event();

data_event* fin_event(pthread_t* thread, data_event* data);

pthread_t init_thread_event(data_event* d);




#endif
