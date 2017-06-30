#include "command.h"

int split_commandline(char *line, char *args[]);
char *current_name();

/* メインプログラム */
int main(void){
  char buffer[BUFSIZE]; // コマンドラインからの入力受け付け用バッファ
  char *args[MAXARGS]; // 引数保存用
  int nargs; // 引数の数
  char *current = "Myshell"; // カレントディレクトリ名

  /* 入力の繰り返し */
  while(1){
    printf("[myshell %s]$ ", current);
    /* コマンドラインからの入力 */
    if(fgets(buffer, sizeof(buffer), stdin) == NULL) break;
    /* 入力の分割 */
    nargs = split_commandline(buffer, args);

    /* コマンド処理 */
    if(strcmp(args[0], "ls") == 0) ls(nargs, args);
    else if(strcmp(args[0], "cd") == 0){
      cd(nargs, args);
      current = current_name();
    }
    else if(strcmp(args[0], "mv") == 0) mv(nargs, args);
    else if(strcmp(args[0], "cp") == 0) cp(nargs, args);
    else if(strcmp(args[0], "rm") == 0) rm(nargs, args);
    else if(strcmp(args[0], "ln") == 0) ln(nargs, args);
    else if(strcmp(args[0], "echo") == 0) echo(nargs, args);
    else if(strcmp(args[0], "pwd") == 0) pwd(nargs);
    else if(strcmp(args[0], "cat") == 0) cat(nargs, args);
    else if(strcmp(args[0], "head") == 0) head(nargs, args);
    else if(strcmp(args[0], "exit") == 0) Exit(nargs);
    else unknown(args[0]);
  }
  return 0;
}

/* コマンドラインからの入力を分割する */
int split_commandline(char *line, char *args[]){
  char *p; // コマンドラインからの入力文字列
  int argc;  // 引数の数
  
  /* 空白文字を飛ばす */
  for(p = line; *p != '\0' && isspace(*p); p++);
  /* コマンドの保存 */
  args[0] = p;
  /* 引数の分割 */
  for(argc = 1; argc < MAXARGS; argc++) {
    /* 文字列の終わりまたは空白文字まで飛ばす */
    for(; *p != '\0' && !isspace(*p); p++);
    if(*p == '\0') break;
    /* 空白文字をナル文字に変換 */
    *p++ = '\0';
    /* 空白文字を飛ばす */
    for(; *p != '\0' && isspace(*p); p++);
    if(*p == '\0') break;
    /* 引数の保存 */
    args[argc] = p;
  }
  return argc;
}

/* カレントディレクトリの名前を返す */
char *current_name(){
  /* カレントディレクトリまでのパスを取得 */
  char pathname[PATHSIZE];
  getcwd(pathname, PATHSIZE);

  /* カレントディレクトリの名前の先頭を探す */
  int i;
  int pathlength = strlen(pathname);
  for(i = pathlength - 1; pathname[i] != '/'; i--);

  /* カレントディレクトリの名前をコピー */
  int j;
  char *p = (char *) malloc (pathlength - i - 1);
  for(j = 0; j < pathlength - i - 1; j++)
    p[j] = pathname[i + j + 1];

  return p;
}
