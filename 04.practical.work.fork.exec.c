#include <stdio.h>
#include <unistd.h>
int main()
 {
  printf("Before Fork \n");
  int a =fork();
  if (a==0)
   { int b=fork();
if (b==0)
   {
    printf("Child \n");
    char *args[]= {"free","-h",NULL };
    execvp("free",args);
   } else{
    char *args[]= {"/bin/ps","-ef",NULL };
    execvp("/bin/ps",args);}
   }
   
 }
