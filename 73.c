#include <pthread.h>

int cond;
pthread_cond_t c;
pthread_mutex_t m;

void *thread_1(void *arg) {
  //...
  cond = 1;                // signal geht verloren,
  pthread_cond_signal(&c); // wenn diese zwei zeilen ausgeführt werden, nach
  //...
  return NULL;
}

void *thread_2(void *arg) {
  //...
  if (!cond)                   // dieser zeile, dann hier thread switch
    pthread_cond_wait(&c, &m); // signal lost wenn gewartet wird nachdem
                               // signalisiert wurde -> thread wartet ewig
  pthread_mutex_lock(&m);
  //...
  pthread_mutex_unlock(&m);
  return NULL;
}

// finde keine weiteren fehler oder ist das doppelte falsch anwenden
// von mutex (bzw nicht anwnden) zwei fehler?

void *my_thread_1(void *arg) {
  //...
  pthread_mutex_lock(&m);
  cond = 1;
  pthread_cond_signal(&c);
  pthread_mutex_unlock(&m);
  //...
  return NULL;
}

void *my_thread_2(void *arg) {
  //...
  pthread_mutex_lock(&m);
  if (!cond)
    pthread_cond_wait(&c, &m);
  //...
  pthread_mutex_unlock(&m);
  return NULL;
}
