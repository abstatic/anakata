#include <sys/unistd.h>
#include <stdio.h>

int main(int argc, const char *argv[])
{
  char hostname[128];
  gethostname(hostname, sizeof(hostname));
  printf("My hostname: %s\n", hostname);
  return 0;
}
