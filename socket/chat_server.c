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
  int listening_socket;
  int connected_socket;
  struct sockaddr_in server;
  struct sockaddr_in client;
  socklen_t fromlen;
  uint16_t recv_port;
  uint16_t send_port;
  char buffer[BUFSIZE];
  int temp = 1;

  if(argc != 2){
    fprintf(stderr, "Usage: %s <port>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  recv_port = atoi(argv[1]);

  listening_socket = socket(PF_INET, SOCK_STREAM, 0);
  if(listening_socket == -1){
    perror("server: socket");
    exit(EXIT_FAILURE);
  }

  if(setsockopt(listening_socket, SOL_SOCKET, 
                SO_REUSEADDR, (void *) &temp, sizeof(temp))){
    perror("server: setsockopt");
    exit(EXIT_FAILURE);
  }

  memset((void *) &server, 0, sizeof(server));
  server.sin_family = PF_INET;
  server.sin_recv_port = htons(recv_port);
  server.sin_addr.s_addr = htonl(INADDR_ANY);
  
  if(bind(listening_socket, (struct sockaddr *) &server, sizeof(server)) == -1){
    perror("server: bind");
    exit(EXIT_FAILURE);
  }

  if(listen(listening_socket, 5) == -1){
    perror("server: listen");
    exit(EXIT_FAILURE);
  }

  memset((void *) &client, 0, sizeof(client));
  fromlen = sizeof(client);
  connected_socket = accept(listening_socket, 
                            (struct sockaddr *) &client, &fromlen);
  if(connected_socket == -1){
    perror("server: accept");
    exit(1);
  }

  close(listening_socket);

  while(1){
    memset(buffer, '\0', BUFSIZE);
    printf("> ");
    if(fgets(buffer, BUFSIZE, stdin) == NULL)
      strcpy(buffer, "quit");
    chop(buffer);
    send(socket_fd, buffer, BUFSIZE, 0);

    memset(buffer, '\0', BUFSIZE);
    recv(connected_socket, buffer, BUFSIZE, 0);
    printf("%s\n", buffer);
    if(strcmp(buffer, "quit") == 0)
      break;
  }

  close(connected_socket);

  return 0;
}
