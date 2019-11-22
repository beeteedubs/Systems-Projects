#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<errno.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<signal.h>
#include<time.h>
#include<string.h>
#include"multitest.h"



//ORDERS "array" FROM "start" TO "newLen" WITH CORRESPONDING VALUES
void fillArr(int* array, int newLen, int start){
    int counter;
    for(counter = start; counter<newLen; counter += 1){
        *(array + counter) = counter;
    }
}

//SCRAMBLES ARRAY "array"
void scramble(int*array, int arrayLen){
    
    int counter, randoNum, temp;

    for(counter = 0; counter < arrayLen; counter += 1){

        randoNum = rand()%arrayLen;
           
        //Swap values
        temp = *(array + counter);
        *(array + counter) = *(array + randoNum);
        *(array + randoNum) = temp;
    } 
}

//SWAPS PREVIOUS TARGET INDEX "prevTarget" WITH RANDOM INDEX IN TNEW ARRAY "array"
void rescramble(int prevTarget, int* array, int arrayLen){

    int randoNum = rand()%arrayLen;

    //Swap values
    int temp = *(array + prevTarget);
    *(array + prevTarget) = *(array + randoNum);
    *(array + randoNum) = temp;
 }

//TEST SEARCHING THROUGH ARRAYS OF LENGTH [0:250:10000] AND 20,000 (41 SEARCHES TOTAL), EACH THREAD HANDLES [1,250] ELEMENTS
void testOne(int* array, int arrLen, int index, int targ){
    
    
    int reallocSize = 0;
    int oldSize = arrLen;
    int indexVal = index;
    int target = targ;
    while(reallocSize <= 1000){
        //reassign oldSize 
        oldSize = reallocSize;

        //change reallocSize
        reallocSize += 250;

        //realloc array to size reallocSize
        array = (int*)realloc(array, sizeof(int)*reallocSize);

        //fill in rest of array
        fillArr(array,reallocSize,oldSize);

        //changes index of previous target
        rescramble(indexVal, array, reallocSize);

        //yeaaa searches
        indexVal = search(array, target, reallocSize);
    }
    
}


int main (int argc, char** argv){

    srand(time(0));
    int arrLen = 250; //this will change as oppropriate in future
    int target = 7; //hardcode to always be the case
    int* array =(int*) malloc(sizeof(int)*arrLen);

    // FILLING IN "arrPtr"    
    fillArr(array, arrLen,0);

    // SCRAMBLE
    scramble(array, arrLen);

    // CALLING SEARCH ONCE
    int indexVal = search(array, target, arrLen);

    testOne(array, arrLen, indexVal, target); 

    return 0;
}
