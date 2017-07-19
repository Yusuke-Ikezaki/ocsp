#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

void stop(int dummy);

clock_t start, restart, elapsed, end;

int main(void){
  signal(SIGINT, stop);

  start = restart = clock();
  while(1){
    sleep(1);
    printf(".");
    fflush(stdout);
  }
  end = clock();

  return 0;
}

void stop(int dummy){
  char answer[16];

  elapsed = clock();
  while(1){
    printf("本当に終了しますか？ (r: 再開, q: 終了)> ");
    fgets(answer, sizeof(answer), stdin);
    strtok(answer, "\n");
    if(strlen(answer) > 1){
      puts("1文字を入力してください"); 
    } else if(answer[0] == 'q'){
      end = clock();
      printf("計測時間: %.2f\n", (double)(end - start) / CLOCKS_PER_SEC);
      exit(EXIT_SUCCESS);
    } else if(answer[0] == 'r'){
      elapsed = clock();
      printf("経過時間: %.2f\n", (double)(elapsed - restart) / CLOCKS_PER_SEC);
      break;
    } else puts("rかqを入力してください");
  }
  restart = clock();
}
