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
  int socket_fd;
  struct sockaddr_in server;
  struct hostent *hp;
  uint16_t port;
  char buffer[BUFSIZE];

  if(argc != 3){
    fprintf(stderr, "Usage: %s <hostname> <port>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  port = atoi(argv[2]);

  socket_fd = socket(PF_INET, SOCK_STREAM, 0);
  if(socket_fd == -1){
    perror("client: socket");
    exit(EXIT_FAILURE);
  }

  memset((void *) &server, 0, sizeof(server));
  server.sin_family = PF_INET;
  server.sin_port = htons(port);

  if((hp = gethostbyname(argv[1])) == NULL){
    perror("client: gethostbyname");
    exit(EXIT_FAILURE);
  }
  memcpy(&server.sin_addr, hp -> h_addr_list[0], hp -> h_length);
  
  if(connect(socket_fd, (struct sockaddr *) &server, sizeof(server)) == -1){
    perror("client: connect");
    exit(EXIT_FAILURE);
  }

  while(1){
    memset(buffer, '\0', BUFSIZE);
    printf("> ");
    if(fgets(buffer, BUFSIZE, stdin) == NULL)
      strcpy(buffer, "quit");
    chop(buffer);
    send(socket_fd, buffer, BUFSIZE, 0);
    if(strcmp(buffer, "quit") == 0)
      break;
  }

  close(socket_fd);
  
  return 0;
}
