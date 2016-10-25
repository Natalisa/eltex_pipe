#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(){
/*Читаем из стандартного потока*/
    int fd[2];
    pipe(fd);
    switch(fork()){
      case 0: {
         close(fd[1]);
         char buf[255];
         dup2(fd[0],0);
         read(0,buf,255);
         printf("%s\n",buf);
         close(fd[0]);
      } break;
      default:{
          close(fd[0]);
          write(fd[1],"Hi\0",sizeof("Hi\0"));
          close(fd[1]);
        }break;
    }
    return 0;
}
