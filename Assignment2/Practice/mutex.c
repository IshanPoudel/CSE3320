#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define MAX_THREAD 1000

// #if you don't have a lock condition , two might write to the global variable at the sametime
//  the moment someone needs to modify it , we need to use either mutex or semaphores.

// pthread_mutex_t is a datatype whoch has the id of a muted.
//  pthread_lock means that that particular thread is locked and other threads can't use the condition first.

//analogy for mutex is that whenever you have a big discussion , only the person 
// holding for example , the rubber chicken would be able to talk.

// the more code we lock , the less we run in parallel.


int count;
pthread_t tid[MAX_THREAD];
pthread_mutex_t mutex;

// pthread_mutex_lock takes in the id of the mutex you created.

void *do_nothing(void *ptr)
{
    pthread_mutex_lock(&mutex);
  
    count =count+1;
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main()
{
    pthread_mutex_lock(&mutex);
    count = 0;
    pthread_mutex_unlock(&mutex);
    pthread_t thread_id;


    for (int i=0; i<MAX_THREAD;i++)
    {
        pthread_create(&tid[i] , NULL , do_nothing , NULL);

    }
    
    for (int i=0; i<MAX_THREAD;i++)
    {
        pthread_join(tid[i] , NULL);

    }

    pthread_mutex_lock(&mutex);
    printf("%d\n" , count);
    pthread_mutex_unlock(&mutex);

    return 0;
}