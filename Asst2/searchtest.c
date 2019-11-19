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


void printArray(int*array, int length){
    int counter = 0;
     while(counter<length){
        printf("%d, ", *(array + counter));
        counter += 1;
    }
}

//CREATES ORDERED ARRAY OF LENGTH "newLen"
int* fillArr(int newLen){
    int* retVal = (int*)malloc(sizeof(int)*newLen);
    int counter;
    printf("This is an ordered array: ");
    for(counter = 0; counter<newLen; counter += 1){
        *(retVal+counter) = counter;
        printf("%d, ", *(retVal + counter));
    }
    return retVal;
}

int main (int argc, char** argv){
    srand(time(0));
    // VARIABLES
    int counter = 0;
    int arrLen;
    int* arrPtr =(int*) malloc(sizeof(int)*10);
    
    // FILLING IN "arr"    
    int *arr = fillArr(10);

    // SCRAMBLE
    scramble(arr, 10);
  

    // EXPAND ARRAY LENGTH
    int* newPtr;
    int reallocSize = 0; //current size after hard coded 10
    for(counter = 0; counter<3; counter += 1){
        reallocSize += 20;//incremented amount idk u choose whats a good stable number ????
        
        arr = fillArr(reallocSize);
            
        arrPtr  = (int*) realloc(arrPtr, sizeof(int) * reallocSize);
        scramble(arr,reallocSize);
    }
    
    return 0;
}
