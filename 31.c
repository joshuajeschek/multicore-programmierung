#include "util.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LEN 100

void parVecAdd(int *a, int *b, int *c, int len) {
#pragma omp parallel firstprivate(a, b) shared(c) num_threads(len)
  {
    int i = omp_get_thread_num();
    c[i] = a[i] + b[i];
  }
}

void parForVecAdd(int *a, int *b, int *c, int len) {
#pragma omp parallel for
  for (int i = 0; i < len; i++) {
    c[i] = a[i] + b[i];
  }
}

void seqVecAdd(int *a, int *b, int *c, int len) {
  for (int i = 0; i < len; i++) {
    c[i] = a[i] + b[i];
  }
}

int main() {
  srand(time(NULL));
  int a[LEN], b[LEN], c[LEN], d[LEN], e[LEN];
  initVector(a, LEN, 1, LEN);
  initVector(b, LEN, 1, LEN);

  double parStart = omp_get_wtime();
  parVecAdd(a, b, c, LEN);
  double parEnd = omp_get_wtime();
  double parForStart = omp_get_wtime();
  parForVecAdd(a, b, e, LEN);
  double parForEnd = omp_get_wtime();

  double seqStart = omp_get_wtime();
  seqVecAdd(a, b, d, LEN);
  double seqEnd = omp_get_wtime();

  printf("\n  a: ");
  printVector(a, LEN);
  printf("+ b: ");
  printVector(b, LEN);
  printf("= c: ");
  printVector(c, LEN);
  printf("= d: ");
  printVector(d, LEN);
  printf("= e: ");
  printVector(d, LEN);

  printf("\npar    took: %.10f\n", parEnd - parStart);
  printf("parFor took: %.10f\n", parForEnd - parForStart);
  printf("seq    took: %.10f\n", seqEnd - seqStart);
  return 0;
}
