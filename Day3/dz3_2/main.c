#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_THREADS	4

int global_i = 1, k;
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mut1 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond;



void* work_loop(void *t) {
    int i; 
    long my_id = (long)t;
	printf("Start thread %ld\n", my_id);
	pthread_mutex_lock(&mut);       
	k = global_i;
	sleep(k);  // сон
	global_i++;
	pthread_mutex_unlock(&mut);
	printf("Glob = %d \n", global_i);
	if(k == NUM_THREADS){
         pthread_cond_broadcast(&cond);
         printf("All treads is free!\n");
        } else {
	 printf("Wait Thread = %ld \n",my_id);
	 pthread_mutex_lock(&mut1);
	 while (k<NUM_THREADS) {
	 pthread_cond_wait(&cond, &mut1);
	 printf("Thread %ld Condition signal received.\n", my_id);
	 }
	 pthread_mutex_unlock(&mut1);
        }
        pthread_exit(NULL);

}

int main () {
    pthread_t threads[NUM_THREADS];
    long rc, t;
    pthread_cond_init (&cond, NULL);
    //pthread_attr_t attr;
    //pthread_attr_init(&attr);
    //pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    for(t = 0; t < NUM_THREADS; t++) {
        printf("In main: creating thread %ld\n", t);
        rc = pthread_create(&threads[t], NULL, work_loop, (void *)(t+1));
        if (rc) {
            printf("ERROR; return code from pthread_create() is %ld\n", rc);
            exit(-1);
        }
    }

    for(t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t], NULL);
        printf("Thread #%ld finished\n", t);
    }

  //pthread_attr_destroy(&attr);
  pthread_mutex_destroy(&mut);
  pthread_mutex_destroy(&mut1);  
  pthread_cond_destroy(&cond);
  pthread_exit(NULL);
    
return 0;
}
