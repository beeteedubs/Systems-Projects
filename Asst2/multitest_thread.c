#include <stdio.h>
#include <fcntl.h>
#include "multitest.h"
#include<stdlib.h>
#include "pthread.h" //-lpthread :gcc -o thread threadPlay.c lpthread

struct thread_arg{
    int x;
    int y;
};



//pthread_create(pthread_t* handle, pthread_attr_t* attr, (void*) (*func)(void*), void*args)

void*sum(void*args){
    
    printf("thread created\n");
    struct thread_arg* arg = (struct thread_arg*)args;
    int x = arg->x;//(*arg).x
    int y = arg->y;
    
    int* result = (int*)malloc(sizeof(int));
    *result = x + y;
    pthread_exit((void*)result);

}

int rando(int argc, char** argv){
    pthread_t t1, t2;
    struct thread_arg t1_arg,t2_arg;
    int*retval1, *retval2;
    t1_arg.x = 3;
    t1_arg.y = 4;

    t2_arg.x = 5;
    t2_arg.y = 6;

    printf("creathing thread 1\n");
    pthread_create(&t1, NULL, sum, (void*)&t1_arg);
    printf("creating thread 2\n");
    pthread_create(&t2, NULL, sum, (void*)&t2_arg);
    
    printf("calling join on thread 1\n");;
    pthread_join(t1, (void**)&retval1);
    printf("thread 1 exited with return val%d\n", *retval1);

    printf("calling join on thread 2\n");;
    pthread_join(t2, (void**)&retval2);
    printf("thread 2 exited with return val%d\n", *retval2);
}


int search (int* array, int target){
    
}
