#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define BUFSIZE 256
#define SEND 0
#define RECV 1
#define PARENT 2

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
  /* プロセスID */
  pid_t pid[PARENT];
  /* ループ用 */
  int i;

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
    exit(EXIT_FAILURE);
  }

  /* listening_socketを閉じる */
  close(listening_socket);

  /* プロセスの複製 */
  for(i = 0; i < PARENT && (pid[i] = fork()) > 0; i++);

  /* プロセスごとの処理 */
  if(pid[i] == 0){
    /* 子プロセス */
    /* クライアントとの通信 */
    if(i == SEND){
      /* 送信用 */
      while(1){
	memset(buffer, '\0', BUFSIZE);
	if(fgets(buffer, BUFSIZE, stdin) == NULL)
	  strcpy(buffer, "quit");
	chop(buffer);
	/* クライアントにメッセージを送信 */
	send(connected_socket, buffer, BUFSIZE, 0);
	if(strcmp(buffer, "quit") == 0)
	  break;
      }
    } else if(i == RECV){
      /* 受信用 */
      while(1){
	memset(buffer, '\0', BUFSIZE);
	/* クライアントからメッセージを受信 */
	recv(connected_socket, buffer, BUFSIZE, 0);
	printf("\nfrom client: %s\n", buffer);
	if(strcmp(buffer, "quit") == 0)
	  break;
      }
    }
    /* 子プロセスの終了 */
    exit(0);
  } else{
    /* 親プロセス */
    /* 子プロセスの監視 */
    puts("-*- this is server -*-");
    /* 1つの子プロセスが終わるまでループ */
    while(waitpid(-1, NULL, WNOHANG) <= 0);
    /* 子プロセスを終了 */
    for(i = 0; i < PARENT; i++)
      kill(pid[i], SIGINT);
  }

  /* connected_socketを閉じる */
  close(connected_socket);

  return 0;
}
