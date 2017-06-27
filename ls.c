#include "command.h"

void ls(int nargs, char *args[]){
  DIR *directory;
  FILE *fp;
  struct dirent *ent;

  if(nargs == 1){
    directory = opendir(".");
    while((ent = readdir(directory)) != NULL)
      printf("%s\n", ent -> d_name);
    closedir(directory);
  } else{
    struct stat st;
    mode_t filetype;
    stat(args[1], &st);
    filetype = st.st_mode & S_IFMT;
    if(filetype == S_IFDIR){
      directory = opendir(args[1]);
      while((ent = readdir(directory)) != NULL)
        printf("%s\n", ent -> d_name);
      closedir(directory);
    } else if(filetype == S_IFREG){
      puts(args[1]);
      fp = fopen(args[1], "r");
      printf("デバイスID                       : %d\n", st.st_dev);
      printf("inode番号                        : %d\n", st.st_ino);
      printf("アクセス保護                     : %o\n", st.st_mode);
      printf("ハードリンクの数                 : %d\n", st.st_nlink);
      printf("所有者のユーザID                 : %d\n", st.st_uid);
      printf("所有者のグループID               : %d\n", st.st_gid);
      printf("デバイスID（特殊ファイルの場合） : %d\n", st.st_rdev);
      printf("容量（バイト単位）               : %d\n", st.st_size);
      printf("ファイルシステムのブロックサイズ : %d\n", st.st_blksize);
      printf("割り当てられたブロック数         : %d\n", st.st_blocks);
      printf("最終アクセス時刻                 : %s", ctime(&(st.st_atime)));
      printf("最終修正時刻                     : %s", ctime(&(st.st_mtime)));
      printf("最終状態変更時刻                 : %s", ctime(&(st.st_ctime)));
      fclose(fp);
    } else{
      puts("No such  file or directory");
    }
  }
}
