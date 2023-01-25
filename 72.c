#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define PW 2
#define CW 1

int buffer;
char data_ready = 0;

void consume_item(int item) {
  for (int i = 0; i <= item; i++) {
    printf(".....%d..c\n", i);
    sleep(1);
  }
  printf("CONSUMED: %d\n", item);
}
int produce_item() {
  int think = 1*PW + rand() % 4*PW;
  for (int i = 0; i <= think; i++) {
    printf("..%d.....p\n", i);
    sleep(1);
  }
  int temp = 1*CW + rand() % 4*CW;
  printf("PRODUCED: %d\n", temp);
  return temp;
}

void *consumer() {
  while (1) {
    while (data_ready == 0)
      ; // <- aktives Warten, verschwendete CPU-Zyklen
    int temp = buffer;
    data_ready = 0;
    consume_item(temp);
  }
}

void *producer() {
  while (1) {
    buffer = produce_item();
    data_ready = 1;
    while (data_ready == 1)
      ; // <- aktives Warten, verschwendete CPU-Zyklen
  }
}

// better implementation
pthread_cond_t c = PTHREAD_COND_INITIALIZER;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

void *myConsumer() {
  while (1) {
    int temp;
    pthread_mutex_lock(&m);
    {
      if (data_ready == 0) {
        printf("consumer waiting...\n");
        pthread_cond_wait(&c, &m);
      }
      temp = buffer;
      data_ready = 0;
      pthread_cond_signal(&c);
    }
    pthread_mutex_unlock(&m);
    consume_item(temp);
  }
}

void *myProducer() {
  while (1) {
    int temp = produce_item();
    pthread_mutex_lock(&m);
    {
      if (data_ready == 1) {
        printf("producer waiting...\n");
        pthread_cond_wait(&c, &m);
      }
      buffer = temp;
      data_ready = 1;
      pthread_cond_signal(&c);
    }
    pthread_mutex_unlock(&m);
  }
}

int main() {
  pthread_t pid;
  pthread_t cid;
  pthread_create(&pid, NULL, myProducer, NULL);
  pthread_create(&cid, NULL, myConsumer, NULL);

  pthread_join(pid, NULL);
  pthread_join(cid, NULL);
}
