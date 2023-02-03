#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define N 160000

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

__global__ void vecadd(int *a, int *b, int *c) {
  int tid = threadIdx.x + blockIdx.x * blockDim.x;
  int i;
  for (i=tid; i<N; i += blockDim.x * gridDim.x)
    c[i] = a[i] + b[i];
}

int main(void) {
  srand(time(NULL));
  int a[N], b[N], c[N];
  int *ad, *bd, *cd;
  cudaMalloc ((void **)&ad, N * sizeof(int));
  cudaMalloc ((void **)&bd, N * sizeof(int));
  cudaMalloc ((void **)&cd, N * sizeof(int));
  initVector(a, N, 1, 5);
  printVector(a, N);
  initVector(b, N, 1, 5);
  printVector(b, N);
  cudaMemcpy(ad, a, N*sizeof(int), cudaMemcpyHostToDevice);
  cudaMemcpy(bd, b, N*sizeof(int), cudaMemcpyHostToDevice);
  vecadd<<<100,160>>>(ad, bd, cd);
  cudaMemcpy(c, cd, N*sizeof(int), cudaMemcpyDeviceToHost);
  printVector(c, N);
  cudaFree(ad); cudaFree(bd); cudaFree(cd);
  return 0;
}
