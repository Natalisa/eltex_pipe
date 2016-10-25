#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(){
    int fd[2];
    pipe(fd);
    switch(fork()){
      case 0: {
         close(fd[1]);
         char buf[255];
         read(fd[0],buf,255);
         printf("%s\n",buf);
         close(fd[0]);
      } break;
      default:{
          close(fd[0]);
          write(fd[1],"Hi",sizeof("Hi"));
          close(fd[1]);
        }break;
    }
    return 0;
}
