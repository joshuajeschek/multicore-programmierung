#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define INTERVALS 1000000000
#define THREADS 100

typedef struct _pi_payload_t {
  int start, end;
  double delta;
  double *pi;
  /* pthread_mutex_t *m; */
} pi_payload_t;

void *calcPiThread(void *arg) {
  pi_payload_t *payload = (pi_payload_t *)arg;
  for (int j = payload->start; j <= payload->end; j++) {
    double x = ((double)j - 0.5) * payload->delta;
    /* pthread_mutex_lock(payload->m); */
    /* { */
    *payload->pi += 4.0 / (1.0 + (x * x));
    /* } */
    /* pthread_mutex_unlock(payload->m); */
  }
  return NULL;
}

double calcPi(int threads, int intervals) {
  double pi = 0.0;
  double pis[threads];
  double delta = 1.0 / (double)intervals;
  /* pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER; */

  pthread_t thread[threads];
  int increment = intervals / threads;
  for (int j = 0; j < threads; j++) {
    pi_payload_t *payload = (pi_payload_t *)malloc(sizeof(pi_payload_t));
    payload->start = j * increment;
    int end = (j + 1) * increment;
    payload->end = (end < intervals) ? end : intervals;
    payload->delta = delta;
    pis[j] = 0;
    payload->pi = &pis[j];
    /* payload->m = &m; */
    pthread_create(&thread[j], NULL, calcPiThread, payload);
  }

  for (int j = 0; j < threads; j++) {
    pthread_join(thread[j], NULL);
    pi += pis[j];
  }

  return pi / intervals;
}

int main() {

  for (int threads = 1; threads <= THREADS; threads++) {
    double start = omp_get_wtime();
    double pi = calcPi(threads, INTERVALS);
    double end = omp_get_wtime();
    printf("%d threads: pi=%.10f (%.10fs)\n", threads, pi, end-start);
  }
}
