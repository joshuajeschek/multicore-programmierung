#include <omp.h>
#include <stdint.h>
#include <stdio.h>

int64_t i = 0;
int64_t N = 100;

void function(int64_t v) { printf("executing %ld\n", v); }

int getNext() {
  int64_t n;
#pragma omp critical
  n = i++;
  return n;
}

int main() {
#pragma omp parallel
  {
    int64_t next = getNext();
    while (next < N) {
      function(next);
      next = getNext();
    }
  }
}
