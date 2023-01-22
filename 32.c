#include "util.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100

void parVecMult(int *a, int *b, int *c, int len) {
  int i = 0;
#pragma omp parallel shared(a, b, c, i) firstprivate(len)                      \
    num_threads(8) default(none)
  {
    int j = 0;
    while (i < len) {
#pragma omp critical
      j = i++;
      c[j] = a[j] * b[j];
    }
  }
}

void forVecMult(int *a, int *b, int *c, int len) {
  int i;
#pragma omp parallel for private(i) schedule(static)
  for (i = 0; i < len; i++) {
    c[i] = a[i] * b[i];
  }
}

int main() {
  srand(time(NULL));
  int a[N], b[N], x[N], y[N];
  initVector(a, N, 1, N);
  initVector(b, N, 1, N);

  double parStart = omp_get_wtime();
  parVecMult(a, b, x, N);
  double parEnd = omp_get_wtime();
  double forStart = omp_get_wtime();
  forVecMult(a, b, y, N);
  double forEnd = omp_get_wtime();

  printf("\n  a: ");
  printVector(a, N);
  printf("+ b: ");
  printVector(b, N);
  printf("= x: ");
  printVector(x, N);
  printf("= y: ");
  printVector(y, N);

  printf("\npar took: %.10f\n", parEnd - parStart);
  printf("for took: %.10f\n", forEnd - forStart);

  return 0;
}
