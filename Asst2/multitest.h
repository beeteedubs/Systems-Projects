#ifndef KITTENS_H
#define KITTENS_H

#define search(x) search(x)
void* search(void*vars);
   
struct thread_vars{
    int* array;
    int target;
    int arrayLen;
};
#endif
