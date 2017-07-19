#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

void stop(int dummy);

clock_t start, restart, end;

int main(void){
  signal(SIGINT, stop);

  start = restart = clock();
  puts("計測中... (Ctrl-c: ストップ)");
  while(1);
  end = clock();

  return 0;
}

void stop(int dummy){
  char answer[16];

  end = clock();
  printf("\n経過時間: %.2f [s]\n", (double)(end - restart) / CLOCKS_PER_SEC);
  while(1){
    printf("r: 再開, q: 終了> ");
    fgets(answer, sizeof(answer), stdin);
    strtok(answer, "\n");
    if(strlen(answer) > 1){
      puts("1文字を入力してください");
    } else if(answer[0] == 'q'){
      printf("合計計測時間: %.2f [s]\n", (double)(end - start) / CLOCKS_PER_SEC);
      exit(EXIT_SUCCESS);
    } else if(answer[0] == 'r'){
      break;
    } else puts("rかqを入力してください");
  }
  restart = clock();
  puts("計測中... (Ctrl-c: ストップ)");
}
