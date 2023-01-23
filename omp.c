#include <omp.h>
#include <stdio.h>

int main(int argc, char **argv) {
  const int n = 1000;
  int array[1000];

#pragma omp parallel for
  for (int i = 1; i < n; ++i) {
    printf("%d:%d\n", omp_get_thread_num(), i);
    array[i] = i;
  }
  return 0;
}

