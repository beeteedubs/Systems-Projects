#ifndef KITTENS_H
#define KITTENS_H
#include <time.h>

struct data {
  int targetIndex;
  suseconds_t timer;
};
struct thread_vars{
    int* array;
    int target;
    int arrayLen;
    int* j;
    int blockSize;
};
#define search(x,y,z,a) search(x,y,z, a)
struct data search(int*arrary, int target, int size, int blockSize);

#endif
