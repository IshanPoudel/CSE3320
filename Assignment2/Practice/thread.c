#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define MAX_THREAD 1000

// #if you don't have a lock condition , two might write to the global variable at the sametime


int count = 0;
pthread_t tid[MAX_THREAD];

void *do_nothing(void *ptr)
{
  
  count =count+1;
  return NULL;
}

int main()
{
    pthread_t thread_id;


    for (int i=0; i<MAX_THREAD;i++)
    {
        pthread_create(&tid[i] , NULL , do_nothing , NULL);
    }
    
    for (int i=0; i<MAX_THREAD;i++)
    {
        pthread_join(tid[i] , NULL);

    }

   
    printf("%d\n" , count);

    return 0;
}