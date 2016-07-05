#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstdlib>
int main() {
pid_t pid;
int fd[2];
char str[10], st[10]; 
size_t size;
if(pipe(fd) < 0){
  printf("Can\'t create pipe\n");
  exit(-1);
}
pid = fork();
if (pid == -1) {
printf("Some error happened\n");
exit(-1);
}
else if(pid == 0) { //дочерний
  close(fd[0]);
  printf("child process %d\n", getpid());
  scanf("%s",str);
  size = write(fd[1], str, sizeof(str));
  if(size != 10){
   printf("Can\'t write all string\n"); 
   exit(-1); 
  }
  close(fd[1]);
  exit(1); 
 }
else { //родительский
 int stat;
 close(fd[1]);
 wait(&stat);
 printf("parrent process %d finished %d\n", getpid(), stat);
 size = read(fd[0], st, sizeof(st));
 if (size != 10){
  printf("Can\'t write all string\n"); 
  exit(-1); 
 }
 printf("%s\n",st);
 close(fd[0]); 
}
return 0;
}
