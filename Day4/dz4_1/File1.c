#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "bin_sem.h"
#define BUF 10000000
int main(){
 char *addr;
 char *s;
 s = (char*) malloc(BUF*sizeof(char));
 key_t key = ftok("File1.c", 1);
 int id = shmget(key,BUF,IPC_CREAT | 0666);//выделение
 int semid = binary_semaphore_allocation(key, 0666 | IPC_CREAT);
 FILE *d; 
 d = fopen("100mb_file.txt","r");
 printf("Begin\n" );
 while(fread(s, sizeof(char), BUF, d)==BUF){
  printf("FILE to MEMORY\n");
  binary_semaphore_take(semid);
  addr = (char *) shmat(id,0,0);
  sprintf(addr,s);
  shmdt(addr);
  binary_semaphore_free(semid);
  printf("End\n");
 }
 binary_semaphore_deallocate(semid);
 printf("Transmission succes!\n");
 free(s);
 exit(0);
}
