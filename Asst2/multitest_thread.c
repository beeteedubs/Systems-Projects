#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include"multitest.h"
#include<stdlib.h>
#include"pthread.h" //-lpthread :gcc -o thread threadPlay.c lpthread
#include<time.h>
#include<sys/time.h>


//IF FOUND RETURN INDEX VALUE, ELSE RETURN -1
void* searchHelper (void* vars){
    
    struct thread_vars* var = (struct thread_vars*)vars;
    int* array = var->array;
    int target = var->target;
    int arrayLen = var->arrayLen;

    int* found = (int*)malloc(sizeof(int)*1);

    int counter;
    for(counter = 0; counter<arrayLen; counter += 1){
        if(*(array + counter) == target){
            *found = counter;
            printf("This thread found it!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
            pthread_exit((void*)found);
        }
    }
    *found = -1;
    pthread_exit((void*)found);    
}

//RETURN INT OF INDEX, OR -1 IF FAILED
int search (int* array, int target, int size){
    
    printf("We are using threads.");
    struct thread_vars vars;
    int* retVal;
    int foundIndex = -1;
    
    int remainder = size%250;
    int threadAmt = size/250;
    if(remainder != 0){
        threadAmt += 1;
    }

    printf("\nnumThreads: %d, size: %d\n", threadAmt, size);
    
    int i = 0;
    struct timeval start;
    struct timeval end;
    suseconds_t timer = 0;
    gettimeofday(&start,0);

    for(i = 0; i < threadAmt; i += 1){ 

        if(remainder != 0 && i == (threadAmt -1)){
            vars.arrayLen = remainder;
        }else{
            vars.arrayLen = 250; 
        }
        printf("\ncreating thread of size: %d\n", vars.arrayLen);
        
        vars.array = array + 250*i;
        vars.target = target;
        
        pthread_t t1;
       
        pthread_create(&t1, NULL, searchHelper, (void*)&vars);
        pthread_join(t1, (void**)&retVal);
        
        
        if (*retVal != -1){
            foundIndex = *retVal;
        }
    } 
        gettimeofday(&end,0);
        timer = end.tv_usec - start.tv_usec;
        printf("Time alloted is %ld\n", timer); 

        printf("thread exited with return val: %d\n\n", foundIndex);
    return foundIndex;
}



//pthread_create(pthread_t* handle, pthread_attr_t* attr, (void*) (*func)(void*), void*args)

/*
struct thread_arg{
    int x;
    int y;
};
*/

/*
void*sum(void*args){
    
    printf("thread created\n");
    struct thread_arg* arg = (struct thread_arg*)args;
    int x = arg->x;//(*arg).x
    int y = arg->y;
    
    int* result = (int*)malloc(sizeof(int));
    *result = x + y;
    pthread_exit((void*)result);

}
*/

/*
int main(int argc, char** argv){
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
*/

