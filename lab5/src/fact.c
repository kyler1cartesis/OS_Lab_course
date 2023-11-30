#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "utils.h"

#include <pthread.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>

pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

struct MultyArgs {
  int *array, begin, end, mod;
};
uint64_t factorial = 1;

uint64_t Multy(const struct MultyArgs *args) {
  uint64_t prod = 1;
  for(int i=args->begin; i < args->end; i++) {
    if (args->array[i] % args->mod != 0)
      prod *= args->array[i] % args->mod;
  }
  // prod = prod % args->mod;
  {
  pthread_mutex_lock(&mut);
  factorial *= prod;
  factorial %= args->mod;
  pthread_mutex_unlock(&mut);
  }
  printf("Partial fact from thread: %ld\n", prod);
  return prod;
}

void* ThreadSum(void *args) {
  struct MultyArgs *multy_args = (struct MultyArgs*)args;
  return Multy(multy_args);
}

int main(int argc, char **argv) {
  int32_t k = 0;
  int32_t pnum = 0;
  int32_t mod = 0;

  while (true)
  {
    int current_optind = optind ? optind : 1;
    static struct option options[] = {{"k", required_argument, 0, 0},
                                      {"pnum", required_argument, 0, 0},
                                      {"mod", required_argument, 0, 0},
                                      {0, 0, 0, 0}};

    int option_index = 0;
    int c = getopt_long(argc, argv, "", options, &option_index);
    if (c == -1) break;
    switch (c) {
      case 0:
        switch (option_index) {
          case 0:
            k = atoi(optarg);
            if (k <= 0) {
              perror("Wrong pnum value! Defaulting to 30");
              k = 30;
            }
            break;
          case 1:
            pnum = atoi(optarg);
            if (pnum <= 0) {
              perror("Wrong pnum value! Defaulting to 4");
              pnum = 4;
            }
            break;
          case 2:
            mod = atoi(optarg);
            if (mod <= 0) {
              perror("Wrong mod value! Defaulting to 10000");
              mod = 10000;
            }
            break;

          default:
            printf("Index %d is out of options\n", option_index);
        }
        break;
    
      case '?':
        break;

      default:
        printf("getopt returned character code 0%o?\n", c);
    }
  }
  if (optind < argc) {
    printf("Has at least one no option argument\n");
    return 1;
  }

  if (k == 0 || pnum == 0 || mod == 0) {
    printf("Usage: %s -k num --pnum=num --mod=num \n",
           argv[0]);
    return 1;
  }

  pthread_t threads[pnum];

  int *array = malloc(sizeof(int) * (k));
  for(int i = 0; i < k; i++)
    array[i] = i + 1;

  struct timeval start_time;
  gettimeofday(&start_time, NULL);

  struct MultyArgs args[pnum];
  for (uint32_t i = 0; i < pnum; i++) {
    args[i].array = array;
    args[i].begin = i * k / pnum;
    args[i].end = (i + 1) * k / pnum ;
    args[i].mod = mod;
    if (pthread_create(&threads[i], NULL, ThreadSum, &args[i])) {
      printf("Error: pthread_create failed!\n");
      return 1;
    }
  }

  // uint64_t total_sum = 1;
  for (uint32_t i = 0; i < pnum; i++) {
    // int sum = 1;
    pthread_join(threads[i], NULL);
    // total_sum *= sum;
    // total_sum %= mod;
  }
  printf("Factorial mod = %ld\n",factorial);

  struct timeval finish_time;
  gettimeofday(&finish_time, NULL);

  double elapsed_time = (finish_time.tv_sec - start_time.tv_sec) * 1000.0;
  elapsed_time += (finish_time.tv_usec - start_time.tv_usec) / 1000.0;
  printf("Elapsed time: %fms\n", elapsed_time);

  return 0;
}