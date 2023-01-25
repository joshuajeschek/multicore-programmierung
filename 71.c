#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

/* #define INTERVALS 1000000000 */
#define INTERVALS 1000

typedef struct _pi_payload_t {
  int j;
  double delta;
  double *pi;
  pthread_mutex_t *m;
} pi_payload_t;

void *calcPi(void *arg) {
  pi_payload_t *payload = (pi_payload_t*) arg;
  double x = ((double)payload->j - 0.5) * payload->delta;

  pthread_mutex_lock(payload->m);
  {
    *payload->pi += 4.0 / (1.0 + (x * x));
  }
  pthread_mutex_unlock(payload->m);
  return NULL;
}

int main() {
  int intervals = INTERVALS;
  double pi = 0.0;
  double delta = 1.0 / (double)intervals;
  pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;


  pthread_t thread[INTERVALS];
  for (int j = 0; j <= intervals; j++) {
    pi_payload_t *payload = (pi_payload_t*) malloc(sizeof(pi_payload_t));
    payload->j = j;
    payload->delta = delta;
    payload->pi = &pi;
    payload->m = &m;
    pthread_create(&thread[j], NULL, calcPi, payload);
  }

  for (int j = 0; j <= intervals; j++)
    pthread_join(thread[j], NULL);

  pi /= intervals;

  printf("pi: %.10f", pi);
}
