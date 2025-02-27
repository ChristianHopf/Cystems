#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <ctype.h>
#include <errno.h>

#define MAX_THREADS 4

void *count_words(void *arg);
char *read_file(char *filename, size_t *size);

typedef struct {
  char *text;
  size_t len;
  int *word_count;
  pthread_mutext_t *mutex;
} CounterThread;

int main(int argc, char *argv[]){

}
