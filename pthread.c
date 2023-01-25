#include <pthread.h>
#include <stdio.h>

typedef struct _thrarg_t {
  int rows, cols;
} thrarg_t;

void *loopthread(void *arg) {
  int j, k;
  thrarg_t *thrarg = (thrarg_t*)arg;
  for (j = 0; j < thrarg->rows; j++) {
    for (k = 0; k < thrarg->cols; k++) {
      printf("loop iteration %d\t%d\n", j, k);
    }
  }
  return NULL;
}

int main() {
  pthread_t tid;
  thrarg_t thrarg;
  thrarg.rows = 10;
  thrarg.cols = 20;
  pthread_create(&tid, NULL, loopthread, &thrarg);
  pthread_join(tid, NULL);
}
