#include <iostream>
#include <stdio.h>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

using namespace std;

int main(int argc, const char *argv[])
{
  struct addrinfo hints, *res, *p;
  int status;

  char ipstr[INET6_ADDRSTRLEN];

  if (argc != 2)
  {
    fprintf(stderr, "usage: showip hostname\n");
    return 1;
  }

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC; // AF_INET or AF_INET6 to force version
  hints.ai_socktype = SOCK_STREAM;

  if ((status = getaddrinfo(argv[1], NULL, &hints, &res)) != 0)
  {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
    return 2;
  }

  cout << "IP addresses for " << argv[1] << endl << endl;

  for (p = res; p != NULL; p = p -> ai_next)
  {
    void* addr;
    char* ipver;

    // get the pointer to the address itself,
    // different fields in ipv4 and ipv6:
    if (p->ai_family == AF_INET)
    {
      // IPV4
      struct sockaddr_in* ipv4 = (struct sockaddr_in*)p -> ai_addr;
      addr = &(ipv4 -> sin_addr);
      ipver = "IPv4";
    }
    else
    {
      // IPv6
      struct sockaddr_in6* ipv6 = (struct sockaddr_in6*) p -> ai_addr;
      addr = &(ipv6 -> sin6_addr);
      ipver = "IPv6";
    }

    // conver the IP to a string and print it:
    inet_ntop(p -> ai_family, addr, ipstr, sizeof(ipstr));
    printf(" %s: %s\n", ipver, ipstr);
  }

  freeaddrinfo(res); // free the linked list

  return 0;
}
