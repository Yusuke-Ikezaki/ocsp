#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUFSIZE 256

void chop(char *str){
  char *p = strchr(str, '\n');
  if(p != NULL)
    *p = '\0';
}

int main(int argc, char *argv[]){
  /* socket()が返すファイル識別子 */
  int listening_socket;
  /* accept()が返すファイル識別子 */
  int connected_socket;
  /* サーバプロセスのソケットアドレス情報 */
  struct sockaddr_in server;
  /* クライアントプロセスのソケットアドレス情報 */
  struct sockaddr_in client;
  /* クライアントプロセスのソケットアドレス情報の長さ */
  socklen_t fromlen;
  /* ポート番号 */
  uint16_t port;
  /* メッセージを格納するバッファ */
  char buffer[BUFSIZE];
  /* ソケットオプション用 */
  int temp = 1;

  /* 引数の確認 */
  if(argc != 2){
    /* 引数が正しくない */
    fprintf(stderr, "Usage: %s <port>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  /* ポート番号の設定 */
  port = atoi(argv[1]);

  /* ソケットの作成 */
  listening_socket = socket(PF_INET, SOCK_STREAM, 0);
  if(listening_socket == -1){
    /* 作成失敗 */
    perror("server: socket");
    exit(EXIT_FAILURE);
  }

  /* ソケットオプションの設定 */
  if(setsockopt(listening_socket, SOL_SOCKET, 
                SO_REUSEADDR, (void *) &temp, sizeof(temp))){
    /* 設定失敗 */
    perror("server: setsockopt");
    exit(EXIT_FAILURE);
  }

  /* サーバプロセスのソケットアドレス情報の設定 */
  /* アドレス情報構造体の初期化 */
  memset((void *) &server, 0, sizeof(server));
  /* プロトコルファミリの設定 */
  server.sin_family = PF_INET;
  /* ポート番号の設定 */
  server.sin_port = htons(port);
  /* IPアドレスの設定 */
  server.sin_addr.s_addr = htonl(INADDR_ANY);

  /* ソケットにアドレスをバインド */
  if(bind(listening_socket, (struct sockaddr *) &server, sizeof(server)) == -1){
    /* バインド失敗 */
    perror("server: bind");
    exit(EXIT_FAILURE);
  }

  /* 接続要求の受け入れ準備 */
  if(listen(listening_socket, 5) == -1){
    /* 準備失敗 */
    perror("server: listen");
    exit(EXIT_FAILURE);
  }

  /* クライアントプロセスのソケットアドレス情報の設定 */
  /* アドレス情報構造体の初期化 */
  memset((void *) &client, 0, sizeof(client));
  /* ソケットアドレス情報の長さを取得 */
  fromlen = sizeof(client);
  /* クライアントからの接続要求を受け入れ、通信経路を確保する */
  connected_socket = accept(listening_socket, 
                            (struct sockaddr *) &client, &fromlen);
  if(connected_socket == -1){
    /* 受け入れ失敗 */
    perror("server: accept");
    exit(1);
  }

  /* listening_socketを閉じる */
  close(listening_socket);

  /* クライアントとの通信 */
  while(1){
    /* 送信用 */
    memset(buffer, '\0', BUFSIZE);
    printf("> ");
    if(fgets(buffer, BUFSIZE, stdin) == NULL)
      strcpy(buffer, "quit");
    chop(buffer);
    send(connected_socket, buffer, BUFSIZE, 0);

    /* 受信用 */
    memset(buffer, '\0', BUFSIZE);
    recv(connected_socket, buffer, BUFSIZE, 0);
    printf("%s\n", buffer);
    if(strcmp(buffer, "quit") == 0)
      break;
  }

  /* connected_socketを閉じる */
  close(connected_socket);

  return 0;
}
