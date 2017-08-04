#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

int value = 50;

void *calc1(void *arg);
void *calc2(void *arg);

typedef struct{
  char name[64];
  pthread_mutex_t *mlock;
} mythread_args_t;

int main(void){
  pthread_t th1, th2;
  void *rval;
  pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
  mythread_args_t args1 = {"th1", &mutex};
  mythread_args_t args2 = {"th2", &mutex};

  srand((unsigned int) time(NULL));
  
  if(pthread_create(&th1, NULL, calc1, (void *) &args1) != 0){
    perror("Thread_creation failed.\n");
    exit(EXIT_FAILURE);
  }

  if(pthread_create(&th2, NULL, calc2, (void *) &args2) != 0){
    perror("Thread creation failed.\n");
    exit(EXIT_FAILURE);
  }

  printf("the process joins with thread th1\n");
  if(pthread_join(th1, &rval) != 0){
    perror("Failed to join with th1.\n");
  }

  printf("the process joins with thread th2\n");
  if(pthread_join(th2, &rval) != 0){
    perror("Failed to join with th2.\n");
  }

  return 0;
}

void *calc1(void *arg){
  mythread_args_t *targs = (mythread_args_t *) arg;
  int prev;

  sleep(rand() % 3);
  printf("[%s] trying to lock...\n", targs -> name);
  pthread_mutex_lock(targs -> mlock);
  
  printf("[%s] locked\n", targs -> name);
  prev = value;
  sleep(rand() % 5);
  value = prev + 10;
  printf("[%s] %d -> %d\n", targs -> name, prev, value);

  pthread_mutex_unlock(targs -> mlock);
  printf("[%s] unlock\n", targs -> name);
  pthread_exit(NULL);
}

void *calc2(void *arg){
  mythread_args_t *targs = (mythread_args_t *) arg;
  int prev;

  sleep(rand() % 3);
  printf("[%s] trying to lock...\n", targs -> name);
  pthread_mutex_lock(targs -> mlock);

  printf("[%s] locked\n", targs -> name);
  prev = value;
  sleep(rand() % 5);
  value = prev * 5;
  printf("[%s] %d -> %d\n", targs -> name, prev, value);
  
  pthread_mutex_unlock(targs -> mlock);
  printf("[%s] unlock\n", targs -> name);
  pthread_exit(NULL);
}
