#include "util.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 2

typedef struct matrix_type_t {
  int row, col;
  int(*MA), (*MB), (*MC);
} matrix_type_t;

void *thread_mult(void *arg) {
  matrix_type_t *work = (matrix_type_t *)arg;
  int i;
  int r = work->row;
  int c = work->col;
  int rc = r * SIZE + c;
  work->MC[rc] = 0.0;
  for (i = 0; i < SIZE; i++) {
    int ri = r * SIZE + i;
    int ic = i * SIZE + c;
    work->MC[rc] += work->MA[ri] * work->MB[ic];
  }
  return NULL;
}

int main() {
  srand(time(NULL));
  int *MA, *MB, *MC;
  MA = calloc(sizeof(int), SIZE * SIZE);
  MB = calloc(sizeof(int), SIZE * SIZE);
  MC = calloc(sizeof(int), SIZE * SIZE);

  initMatrix(MA, SIZE, 10, 20);
  initMatrix(MB, SIZE, 10, 20);
  printf("MA:\n");
  printMatrix(MA, SIZE);
  printf("MB:\n");
  printMatrix(MB, SIZE);
  matrix_type_t *work;
  pthread_t thread[SIZE][SIZE];
  for (int row = 0; row < SIZE; row++) {
    for (int col = 0; col < SIZE; col++) {
      work = (matrix_type_t *)malloc(sizeof(matrix_type_t));
      work = (matrix_type_t *)malloc(sizeof(matrix_type_t));
      work->row = row;
      work->col = col;
      work->MA = MA;
      work->MB = MB;
      work->MC = MC;
      pthread_create(&thread[row][col], NULL , thread_mult, work);
    }
  }

  for (int row = 0; row < SIZE; row++)
    for (int col = 0; col < SIZE; col++)
      pthread_join(thread[row][col], NULL);

  printf("MC:\n");
  printMatrix(MC, SIZE);
}
