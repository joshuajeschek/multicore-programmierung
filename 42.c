#include <omp.h>
#include <stdio.h>

#define N 100

int parFib(int n) {
  if (n < 2)
    return n;
  int x, y;
#pragma omp taskgroup
  {
#pragma omp task shared(x)
    x = parFib(n - 1);
#pragma omp task shared(y)
    y = parFib(n - 2);
  }
  return x + y;
}

int seqFib(int n) {
  if (n < 2)
    return n;
  int x, y;
  x = seqFib(n - 1);
  y = seqFib(n - 2);
  return x + y;
}

void benchmark(int n) {
  double parStart = omp_get_wtime();
  int parf;
#pragma omp parallel
  {
#pragma omp single
    parf = parFib(n);
  }
  double parEnd = omp_get_wtime();
  printf("parFib(%d) = %d (%f s)\n", n, parf, parEnd - parStart);

  double seqStart = omp_get_wtime();
  int seqf;
  seqf = seqFib(n);
  double seqEnd = omp_get_wtime();
  printf("seqFib(%d) = %d (%f s)\n", n, seqf, seqEnd - seqStart);
}

int main() {
  for (int n = 0; n <= N; n++) {
    benchmark(n);
  }
  return 0;
}
