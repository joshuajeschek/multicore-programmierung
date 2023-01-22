#include <omp.h>
#include <stdio.h>

#define N 5

void f(int i) { printf("f(%d) from %d\n", i, omp_get_thread_num()); }

void parF() {
  int i;
#pragma omp parallel for private(i)
  for (i = 0; i < N; i++) {
    f(i);
  }
}

void secF() {
  int i;
#pragma omp parallel sections
  {
#pragma omp section
    f(0);
#pragma omp section
    f(1);
#pragma omp section
    f(2);
#pragma omp section
    f(3);
#pragma omp section
    f(4);
  }
}

int main() {
  parF();
  secF();
  return 0;
}
