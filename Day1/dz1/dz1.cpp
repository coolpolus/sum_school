#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include "sort.h"
int main() {
pid_t pid;
int fd[2];
char str[1000], st[1000]; 
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
  printf("child process %d\n", getpid());
  close(fd[0]);
  dup2(fd[1], 1);
  dup2(fd[1], 2);
  close(fd[1]);
  int ret;
  ret = execlp("/bin/ls", "ls", "-l", "/tmp/", NULL);
  if (ret == -1)
        perror ("execl");
  exit(1); 
 }
else { //родительский
 int stat;
 close(fd[1]);
 wait(&stat);
 printf("parrent process %d finished %d\n", getpid(), stat);
 size = read(fd[0], st, sizeof(st));
char* buf = strtok(st, " \n");
char* p;
char* file[100];
int i = 0;
while (buf)
{
  p = strstr(buf,"."); // только файлы
  if ((p) and (*(p+1)!='\0')) { 
   file[i] = new char[100]; 
   strcpy(file[i],buf); 
   i++;
  }
  buf = strtok(NULL, " \n");
}
 sort(file,i-1);
 close(fd[0]); 
}
return 0;
}
