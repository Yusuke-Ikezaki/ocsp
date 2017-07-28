#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define BUFSIZE 256

void chop(char *str){
  char *p = strchr(str, '\n');
  if(p != NULL)
    *p = '\0';
}

int main(int argc, char *argv[]){
  /* socket()の返すファイル識別子 */
  int socket_fd;
  /* サーバプロセスのソケットアドレス情報 */
  struct sockaddr_in server;
  /* ホスト情報 */
  struct hostent *hp;
  /* ポート番号 */
  uint16_t port;
  /* メッセージを格納するバッファ */
  char buffer[BUFSIZE];

  /* 引数の確認 */
  if(argc != 3){
    /* 引数が正しくない */
    fprintf(stderr, "Usage: %s <hostname> <port>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  /* ポート番号の設定 */
  port = atoi(argv[2]);

  /* ソケットの作成 */
  socket_fd = socket(PF_INET, SOCK_STREAM, 0);
  if(socket_fd == -1){
    /* 作成失敗 */
    perror("client: socket");
    exit(EXIT_FAILURE);
  }

  /* サーバプロセスのソケットアドレス情報の設定 */
  /* アドレス情報構造体の初期化 */
  memset((void *) &server, 0, sizeof(server));
  /* プロトコルファミリの設定 */
  server.sin_family = PF_INET;
  /* ポート番号の設定 */
  server.sin_port = htons(port);

  /* argv[1]のマシンのIPアドレスを返す */
  if((hp = gethostbyname(argv[1])) == NULL){
    /* 取得失敗 */
    perror("client: gethostbyname");
    exit(EXIT_FAILURE);
  }
  /* IPアドレスの設定 */
  memcpy(&server.sin_addr, hp -> h_addr_list[0], hp -> h_length);

  /* サーバに接続する */
  if(connect(socket_fd, (struct sockaddr *) &server, sizeof(server)) == -1){
    /* 接続失敗 */
    perror("client: connect");
    exit(EXIT_FAILURE);
  }

  /* サーバとの通信 */
  while(1){
    /* 受信用 */
    memset(buffer, '\0', BUFSIZE);
    recv(socket_fd, buffer, BUFSIZE, 0);
    printf("%s\n", buffer);

    /* 送信用 */
    memset(buffer, '\0', BUFSIZE);
    printf("> ");
    if(fgets(buffer, BUFSIZE, stdin) == NULL)
      strcpy(buffer, "quit");
    chop(buffer);
    send(socket_fd, buffer, BUFSIZE, 0);
    if(strcmp(buffer, "quit") == 0)
      break;
  }

  /* socket_fdを閉じる */
  close(socket_fd);

  return 0;
}
