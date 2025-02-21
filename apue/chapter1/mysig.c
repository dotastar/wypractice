#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFSIZE 1024

static void sig_int(int);

int main(){
  char buf[BUFSIZE] = {0};
  pid_t pid;
  int status;

  if(signal(SIGINT, sig_int) == SIG_ERR){
    printf("sig error\n");
    exit(1);
  }
  
  printf("%% ");
  while( NULL != fgets(buf, BUFSIZE, stdin)){

    int len = strlen(buf) - 1;
    if(buf[len] == '\n'){
      buf[len] = 0;
    }
    if((pid = fork()) < 0){
      printf("fork error\n");
      exit(1);
    }else if(pid == 0){
      execlp(buf, buf, (char*)0);
      printf("execlp error\n");
      exit(1);
    
    }
    if((pid = waitpid(pid, &status, 0)) < 0){
      printf("waitpid error\n");
      exit(1);
    }
    printf("%%");
  }
  exit(0);
}

void sig_int(int signo){
  printf("interupt\n%% ");
}
