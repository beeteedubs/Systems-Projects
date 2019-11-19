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
    return;
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
    
    return;
}

//use just 1 thread to run search
int main (int argc, char** argv){
    srand(time(0));
    // VARIABLES
    int counter = 0;
    int arrLen;
    int* arrPtr =(int*) malloc(sizeof(int)*10);
    pthread_t t1;
    struct thread_vars vars;
    int* retVal;
    
    // FILLING IN "arr"    
    fillArr(arrPtr, 10);

    // SCRAMBLE
    scramble(arrPtr, 10);
  
    int reallocSize = 0; //current size after hard coded 10
    for(counter = 0; counter<1; counter += 1){
        reallocSize += 20;
            
        arrPtr  = (int*) realloc(arrPtr, sizeof(int) * reallocSize);
        fillArr(arrPtr, reallocSize);
        scramble(arrPtr,reallocSize);
        
        printf("creating thread\n");
        pthread_create(&t1, NULL, search, (void*)&vars);

        printf("calling join on thread\n");
        pthread_join(&t1, (void**)&retVal);
    }
    
    return 0;
}
