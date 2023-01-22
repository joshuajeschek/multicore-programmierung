#include <omp.h>
#include <stdio.h>

int x = 0;
int y = 0;

void fun1();
void fun2();
void fun3();
void fun4();

void fun1() {
#pragma omp critical(one)
  {
    fun2();
    x += 1;
  }
}
void fun2() {
#pragma omp critical(two)
    y += 1;
}

void fun3() {
#pragma omp critical(two)
  {
    y -= 1;
    fun4();
  }
}

void fun4() {
#pragma omp critical(one)
  {
    x += 1;
  }
}

// deadlocks
int main() {
  int i;
#pragma omp parallel private(i)
  {
    int j = omp_get_thread_num();
    for (i=0; i < 10; i++) {
      fun1();
      fun3();
    }
  }
  printf("%d %d\n ", x, y);
}
