#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// A normal C function that is executed as a thread
// when its name is specified in pthread_create()
void* myThreadFun(void* vargp)
{
  static int invo = 0;
  int n = 0;
  printf("--------INVO %d----------", invo);
  while (n < 10)
  {
    printf("Invo %d Printing Abhishek from Thread %d\n", invo, n);
    n++;
  }
  invo++;
  return NULL;
}

int main(void)
{
  pthread_t tid;
  printf("Before thread\n");
  pthread_create(&tid, NULL, myThreadFun, NULL);
  /* pthread_join(tid, NULL); */
  for(int i = 0; i < 1000; i++)
  {
    printf("Hello from main thread %d\n", i);
     pthread_create(&tid, NULL, myThreadFun, NULL);
  }
  exit(0);
}
