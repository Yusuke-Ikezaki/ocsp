#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

int count = 0;

void *_count(void *arg);

typedef struct{
  char name[64];
  pthread_mutex_t *mlock;
} mythread_args_t;

int main(void){
  pthread_t th1, th2, th3;
  void *rval;
  pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
  mythread_args_t args1 = {"th1", &mutex};
  mythread_args_t args2 = {"th2", &mutex};
  mythread_args_t args3 = {"th3", &mutex};

  srand((unsigned int) time(NULL));
  
  if(pthread_create(&th1, NULL, _count, (void *) &args1) != 0){
    perror("Thread_creation failed.\n");
    exit(EXIT_FAILURE);
  }

  if(pthread_create(&th2, NULL, _count, (void *) &args2) != 0){
    perror("Thread creation failed.\n");
    exit(EXIT_FAILURE);
  }

  if(pthread_create(&th3, NULL, _count, (void *) &args3) != 0){
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

  printf("the process joins with thread th3\n");
  if(pthread_join(th3, &rval) != 0){
    perror("Failed to join with th3.\n");
  }

  return 0;
}

/* countに1を10回加算する関数 */
void *_count(void *arg){
  mythread_args_t *targs = (mythread_args_t *) arg;
  int prev;
  int i;

  /* 3秒以内のスリープ */
  sleep(rand() % 3);

  for(i = 0; i < 10; i++){
    /* 3秒以内のスリープ */
    sleep(rand() % 3);
    
    /* ロック */
    pthread_mutex_lock(targs -> mlock);

    /* クリティカルセクション */
    /* 元の値を表示 */
    prev = count;
    printf("[%s] %d -> ", targs -> name, prev);
    /* 4秒以内のスリープ */
    sleep(rand() % 5);
    /* countに1を加算 */
    count = prev + 1;
    /* 加算後のcountを表示 */
    printf("%d\n", count);

    /* ロック解除 */
    pthread_mutex_unlock(targs -> mlock);
  }

  pthread_exit(NULL);
}
