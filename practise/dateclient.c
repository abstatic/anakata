#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

int main(int argc, const char *argv[])
{
  int sockfd = 0, n = 0;
  char recvBuff[1024];
  char sendBuff[1024];
  struct sockaddr_in serv_addr;

  if (argc != 2)
  {
    printf("\nUsage: %s <ip of server> \n", argv[0]);
    return 1;
  }

  // this the buffer where we receive the information
  memset(recvBuff, '0', sizeof(recvBuff));
  memset(sendBuff, '0', sizeof(sendBuff));

  // create a socket

  /* if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) */
  /* { */
    /* printf("\n Error: Connect Failed\n"); */
    /* return 1; */
  /* } */

  /*
  while ((n = read(sockfd, recvBuff, sizeof(recvBuff) - 1)) > 0)
  {
    recvBuff[n] = 0;
    if (fputs(recvBuff, stdout) == EOF)
    {
      printf("\n Error: fpouts error");
    }
  }
  */
  while (1)
  {
  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    printf("\n Error: Could not create socket \n");
    return 1;
  }

  memset(&serv_addr, '0', sizeof(serv_addr));

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(5000);

  if (inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) <= 0)
  {
    printf("\n inet_pton error occured\n");
    return 1;
  }
  if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
  {
    perror("server: socket");
    return 1;
  }
    char c;
    int i = 0;
    while ((c = getchar()) != '\n')
      sendBuff[i++] = c;
    sendBuff[i] = '\0';
    write(sockfd, sendBuff, i-1);
    int r = read(sockfd, recvBuff, sizeof(recvBuff) - 1);
    recvBuff[r+1] = '\0';
    fputs(recvBuff, stdout);
    printf("\n");
    close(sockfd);
  }

  if (n < 0)
    printf("\n Read error\n");

  return 0;
}
