#include<stdio.h>
#include<signal.h>
#include<errno.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<signal.h>
#include<string.h>



int*  scramble(int*array, int arrayLen){
    srand(time(0));
    int counter2, randoNum;
    int* retVal = array;
    int temp = 0;
    for(counter2 = 0; counter2 < arrayLen; counter2+=1){
        randoNum = rand()%9 + 1; //randomNum = [1,100]
        /*
        *(retVal + randoNum) = *(array+counter2);
        *(retVal + counter2) = *(array+randoNum);
        */
        printf("This is randoNum: %d\n", randoNum);
        temp = *(retVal + counter2);
        *(retVal + counter2) = *(retVal + randoNum);
        *(retVal + randoNum) = temp;
    }
    
    return retVal;
}

int* fillArr(int newLen){
    int* retVal = (int*)malloc(sizeof(int)*newLen);
    int counter;
    for(counter = 0; counter<newLen; counter += 1){
        *(retVal+counter) = counter;
    }
    return retVal;
}

int main (int argc, char** argv){
    // VARIABLES
    int counter = 0;
    int arrLen;
    int* arrPtr =(int*) malloc(sizeof(int)*10);
    
    // FILLING IN "arr"    
    int *arr = fillArr(10);

    // SCRAMBLE
    arrPtr = scramble(arr, 10);

    // CONFIRM RANDOMNESS
  

    // EXPAND ARRAY LENGTH
    int* newPtr;
    int reallocSize = 0; //current size after hard coded 10
    for(counter = 0; counter<10; counter += 1){
        reallocSize += 20;//incremented amount idk u choose whats a good stable number ????
        
        arr = fillArr(reallocSize);
            
        arrPtr  = (int*) realloc(arrPtr, sizeof(int) * reallocSize);
        arrPtr = scramble(arr,reallocSize);
    }
    return 0;
}
