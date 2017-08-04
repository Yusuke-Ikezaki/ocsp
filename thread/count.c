#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

char str[] = "Hello World";

void *thread_test(void *arg);

int main(void){
  pthread_t th1, th2;
  void *rval;

  srand((unsigned int) time(NULL));

  if(pthread_create(&th1, NULL, thread_test, (void *) "th1") != 0){
    perror("Thread creation failed.\n");
    exit(EXIT_FAILURE);
  }

  if(pthread_create(&th2, NULL, thread_test, (void *) "th2") != 0){
    perror("Thread creation failed.\n");
    exit(EXIT_FAILURE);
  }

  printf("the process joins with thread th1\n");
  if(pthread_join(th1, &rval) != 0){
    perror("Failed to join with th1.\n");
  } else{
    printf("finished th1 (thread ID = %p)\n", (void *) *(pthread_t *) rval);
    free(rval);
  }

  printf("the process joins with thread th2\n");
  if(pthread_join(th2, &rval) != 0){
    perror("Failed to join with th2.\n");
  } else{
    printf("finished th2 (thread ID = %p)\n", (void *) *(pthread_t *) rval);
    free(rval);
  }

  return 0;
}

void *thread_test(void *arg){
  pthread_t *thread_id = (pthread_t *) malloc(sizeof(pthread_t));
  *thread_id = pthread_self();
  printf("[%s] str = %s\n", (char *) arg, str);
  sleep(rand() % 5);
  pthread_exit((void *) thread_id);
}
