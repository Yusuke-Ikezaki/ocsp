#include "command.h"

void print_info(char *name);

/* ファイルの情報を表示 */
void ls(int nargs, char *args[]){
  /* 引数が多い場合 */
  if(nargs > 2){
    puts("too many arguments"); return;
  }

  /* ファイル名の補完 */
  int option = 0; // オプションの有無
  /* lsのみの場合 */
  if(nargs == 1) args[1] = ".";
  /* ls -lの場合 */
  else if(strcmp(args[1], "-l") == 0){
    args[1] = ".";
    option = 1;
  }

  /* ファイルの状態の取得 */
  struct stat st;
  lstat(args[1], &st);

  /* ファイルのタイプごとの処理 */
  /* ディレクトリ */
  if(S_ISDIR(st.st_mode)){
    DIR *directory;
    struct dirent *ent;

    /* ディレクトリを開く */
    directory = opendir(args[1]);

    /* オプション有り */
    if(option)
      while((ent = readdir(directory)) != NULL)
	print_info(ent -> d_name);
    /* オプション無し */
    else
      while((ent = readdir(directory)) != NULL)
	/* 名前 */
	printf("%s\n", ent -> d_name);

    /* ディレクトリを閉じる */
    closedir(directory);
  }
  /* 通常ファイル、FIFO、シンボリックリンク、ソケット */
  else if(S_ISREG(st.st_mode) || S_ISFIFO(st.st_mode) ||
	  S_ISLNK(st.st_mode) || S_ISSOCK(st.st_mode))
    print_info(args[1]);
  /* それ以外 */
  else
    puts("No such file or directory");
}

/* ファイルの情報を出力 */
void print_info(char *name){
  /* ファイルの状態の取得 */
  struct stat st;
  lstat(name, &st);

  /* ファイルの種類とアクセス保護モード */
  /* モードの取得 */
  int mode = (int)st.st_mode;
  /* ファイルの種類 */
  char type = '-';
  if(S_ISDIR(mode)) type = 'd';
  else if(S_ISFIFO(mode)) type = 'f';
  else if(S_ISLNK(mode)) type = 'l';
  else if(S_ISSOCK(mode)) type = 's';
  /* アクセス保護モード */
  char permission[10] = "---------";
  int i;
  for(i = 9; i > 0; i--){
    if(mode % 2){
      if((i % 3) == 0) permission[i - 1] = 'x';
      else if(((i + 1) % 3) == 0) permission[i - 1] = 'w';
      else if(((i + 2) % 3) == 0) permission[i - 1] = 'r';
    }
    mode /= 2;
  }
  printf("%c%s", type, permission);

  /* ハードリンクの数 */
  printf("%2d ", (int)st.st_nlink);

  /* 大きさ */
  printf("%5d ", (int)st.st_size);

  /* 最終修正時刻 */
  char *changed = ctime(&(st.st_mtime));
  /* 改行文字の削除 */
  changed[strlen(changed) - 1] = '\0';
  printf("%s ", changed);

  /* 名前 */
  printf("%s\n", name);
}
