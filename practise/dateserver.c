#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

int main(int argc, const char *argv[])
{
  int listenfd = 0, connfd = 0;
  struct sockaddr_in serv_addr;

  char sendBuff[1025];
  char recvBuff[1025];
  time_t ticks;

  listenfd = socket(AF_INET, SOCK_STREAM, 0);
  memset(&serv_addr, '0', sizeof(serv_addr));
  memset(sendBuff, '0', sizeof(sendBuff));
  memset(recvBuff, '0', sizeof(recvBuff));

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(5000);

  bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

  listen(listenfd, 10);

  while(1)
  {
  connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);

    ticks = time(NULL);

    /* snprintf(sendBuff, sizeof(sendBuff), "%.24s\r\n", ctime(&ticks)); */
    /* read(connfd, recvBuff, sizeof(recvBuff) - 1); */

    int data = 1;

    int r = read(connfd, recvBuff, sizeof(recvBuff) - 1);
    recvBuff[r+1] = '\0';
    fputs(recvBuff, stdout);
    printf("\n");

    write(connfd, recvBuff, strlen(recvBuff));
    close(connfd);
    /* sleep(1); */
  }
  return 0;
}
