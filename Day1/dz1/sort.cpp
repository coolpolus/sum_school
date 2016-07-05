#include <stdio.h>
#include <cstring>
void sort(char* mas[], int num){ // по убыванию
char buf[200];
for (int i=0; i<num; i++) 
 for (int j=i+1; j<num+1; j++){
   if (mas[i][0]<mas[j][0]){
    strcpy(buf,mas[i]);
    strcpy(mas[i],mas[j]);
    strcpy(mas[j],buf); 
   }
}
for (int i=0; i<num+1; i++){
printf("%s\n",mas[i]);
} 
}
