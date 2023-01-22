#include <stdlib.h>
#include <stdio.h>

void initVector(int *vec, int len, int min, int max) {
  for (int i = 0; i < len; i++) {
    vec[i] = min + rand() % (max - min);
  }
}
void printVector(int *vec, int len) {
  printf("[");
  for (int i = 0; i < len - 1; i++) {
    printf("%d,", vec[i]);
  }
  printf("%d]\n", vec[len - 1]);
}
