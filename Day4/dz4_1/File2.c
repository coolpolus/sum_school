#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "bin_sem.h"
#define BUF 10000000
int main(){
 key_t key = ftok("File1.c", 1);
 char *addr;
 int id = shmget(key,BUF,IPC_CREAT | 0666); //связывание
 int semid = binary_semaphore_allocation(key, 0666 | IPC_CREAT);
 FILE *d;
 d = fopen("output.txt","w");
 int i=0;
 binary_semaphore_initialize(semid);
 if (semid > 0){
  while(i<10){
   printf("MEMORY to FILE \n");
   binary_semaphore_take(semid);
   addr = (char *) shmat(id,0,0);
   fwrite(addr, sizeof(char), BUF, d);
   binary_semaphore_free(semid);
   printf("Released 10mb\n");
   shmdt(addr);
   sleep(1);
   i=i+1;
  }
 }
 binary_semaphore_deallocate(semid);
 exit(0);
}
