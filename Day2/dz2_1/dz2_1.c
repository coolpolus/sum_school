#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <string.h>
#define N 3 // количество рабочих потоков

typedef struct stream{
 int id; // 0 to N-1
 char mas[10];
 int num_cycl; // 0 to 20
 int disp; // any
} stream;

void* iterat(void *fdat1){
 int count = 0;
 int i;
 stream *fdat= (stream*)fdat1;
 for (i=0; i<fdat->num_cycl; i++){
  printf("Name of stream: %s|id of stream: %d|cycle number: %d| counter: %d\n", fdat->mas, fdat->id, i, count);
  count += fdat->disp;
  sleep(1);
 }
}

int main(){
 pthread_t mas[N];
 stream dat[N];
 int status;
 srand(time(0));
 char buf[3] = "";
 char name[10] = "name";
 long i;
 for (i=0; i<N; i++){
  dat[i].id = i;
  dat[i].num_cycl = rand()%(20);
  dat[i].disp = rand()%1000;
  sprintf(name, "name%d", rand()%10);
  strcpy(dat[i].mas, name);
  printf("id =%d, numcycl = %d, disp=%d, name = %s\n",dat[i].id,dat[i].num_cycl, dat[i].disp, dat[i].mas);
  status = pthread_create(&mas[i], NULL, iterat, (void*)&dat[i]);
  if (status != 0) {
   printf("Main error: can't create thread, status = %d\n", status);
   exit(-1);
  }
 }
 for (i=0; i<N; i++){
  status = pthread_join(mas[i], NULL);
  if (status != 0) {
   printf("Main error: can't join thread, status = %d\n", status);
   exit(-2);
  }
 }
}
