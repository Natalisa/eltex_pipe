#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(){
/*Связь между дочерними процессами через стандартные потоки ввода\вывода*/
    int fd[2];
    pipe(fd);
    switch(fork()){
      case 0: {
         close(fd[1]);
         char buf[500];
         dup2(fd[0],0);
         read(0,buf,500);
         printf("%s",buf);
         close(fd[0]);
      } break;
      default:{
          switch (fork()) {
              case 0: {
                  close(fd[0]);
                  dup2(fd[1],1);
                  execlp("ls","ls","-l",NULL);
                  close(fd[1]);
              } break;
              default:
                  wait(0); 
              break;
          }
          wait(0);
      }break;
    }

    return 0;
}
