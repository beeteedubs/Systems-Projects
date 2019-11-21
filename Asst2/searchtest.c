#include<stdio.h>
#include<signal.h>
#include<errno.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<signal.h>
#include<string.h>
#include"multitest.h"


//PRINTS ARRAY "array" OF LENGTH "length"
void printArray(int*array, int length){
    int counter = 0;
     while(counter<length){
        printf("%d, ", *(array + counter));
        counter += 1;
    }
}


//CREATES AN ORDERED ARRAY OF LENGTH "newLen"
void* fillArr(int* array, int newLen){
    int counter;
    printf("This is an ordered array: ");
    for(counter = 0; counter<newLen; counter += 1){
        *(array + counter) = counter;
        printf("%d, ", *(array + counter));
    }
}


//SCRAMBLES ARRAY "array"
void* scramble(int*array, int arrayLen){
    
    int counter2, randoNum;
    int temp = 0;

    printf("These is a scrambled array: ");
    for(counter2 = 0; counter2 < arrayLen; counter2+=1){

        //CREATE RANDOM INDEX VALUE TO SWAP
        randoNum = rand()%arrayLen; //randomNum = [0,arrayLen -1]
        
        //Swap values
        temp = *(array + counter2);
        *(array + counter2) = *(array + randoNum);
        *(array + randoNum) = temp;
    }
    
    //Print the scrambled array
    printArray(array,arrayLen);
    printf("\n");
}

void* rescramble(int prevTarget, int* array, int arrayLen){
    int randoNum = rando()%arrayLen;
    int temp = *(array + prevTarget);
    *(array + prevTarget) = *(array + randoNum);
    *(array + randoNum) = *(array + prevTarget);

}
//use just 1 thread to run search
int main (int argc, char** argv){
    srand(time(0));
    // VARIABLES
    int counter = 0;
    int arrLen = 1; //this will change as oppropriate in future
    int target = 7; //hardcode to always be the case
    int* arrPtr =(int*) malloc(sizeof(int)*arrLen);

    pthread_t t1;
    struct thread_vars vars;
    vars.array = arrPtr;
    vars.target = 7;
    int* retVal;
    
    // FILLING IN "arrPtr"    
    fillArr(arrPtr, arrLen);

    // SCRAMBLE
    scramble(arrPtr, arrLen);
  
    int reallocSize = 0; //current size after hard coded 10
    for(counter = 0; counter<1; counter += 1){
        reallocSize += 20;
        vars.arrayLen = reallocSize;

            
        arrPtr  = (int*) realloc(arrPtr, sizeof(int) * reallocSize);
        fillArr(arrPtr, reallocSize);
        scramble(arrPtr,reallocSize);
        
        printf("creating thread\n");
        pthread_create(&t1, NULL, search, (void*)&vars);

        printf("calling join on thread\n");
        pthread_join(t1, (void**)&retVal);

        printf("thread exited with return val: %d\n", *retVal);
    }
    
    return 0;
}
