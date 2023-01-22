#include <omp.h>
#include <stdio.h>

#define intervals 1000000000

double seqPi() {
  double delta, x, pi = 0.0;
  delta = 1.0 / (double)intervals;
  for (int j = 0; j <= intervals; j++) {
    x = ( (double)j - 0.5 ) * delta;
    pi += 4.0 / (1.0 + (x * x));
  }
  return pi / intervals;
}

double parPi() {
  double delta, x, pi = 0.0;
  delta = 1.0 / (double)intervals;
#pragma omp parallel for reduction(+:pi) private(x)
  for (int j = 0; j <= intervals; j++) {
    x = ( (double)j - 0.5 ) * delta;
    pi += 4.0 / (1.0 + (x * x));
  }
  return pi / intervals;
}

int main() {
  double seqStart = omp_get_wtime();
  printf("seqPi: %.10f", seqPi());
  double seqEnd = omp_get_wtime();
  printf(" (%f s)\n", seqEnd - seqStart);
  double parStart = omp_get_wtime();
  printf("parPi: %.10f", parPi());
  double parEnd = omp_get_wtime();
  printf(" (%f s)\n", parEnd - parStart);
}
