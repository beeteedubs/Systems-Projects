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
#include <limits.h>


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
    printf("Target index is: %d\n", randoNum);

    //Swap values
    int temp = *(array + prevTarget);
    *(array + prevTarget) = *(array + randoNum);
    *(array + randoNum) = temp;
    //printf("*(array+randoNum): %d\n", *(array+randoNum));
 }

//TEST SEARCHING THROUGH ARRAYS OF LENGTH [0:250:10000] AND 20,000 (41 SEARCHES TOTAL), EACH THREAD HANDLES [1,250] ELEMENTS
void testOne(int* array, int arrLen, int targ){
    printf("Running test case 1\n");
    int blockSize = 250;
    int reallocSize = 250;
    int oldSize = 0;
    struct data indexVal;
    int minimum = INT_MAX;
    int maximum = 0;
    int average = 0;
    int target = targ;
    //searches once to find the first target index.
    indexVal = search(array, target, reallocSize, blockSize);
    average += indexVal.timer;
    if(indexVal.timer > maximum) {
      maximum = indexVal.timer;
    }
    else if (indexVal.timer < minimum) {
      minimum = indexVal.timer;
    }
    while(reallocSize < arrLen){
        //reassign oldSize
        oldSize = reallocSize;

        //change reallocSize
        reallocSize += blockSize;

        array = (int*)realloc(array, sizeof(int)*reallocSize);
        //realloc array to size reallocSize

        //fill in rest of array
        fillArr(array,reallocSize,oldSize);

        //changes index of previous target
        rescramble(indexVal.targetIndex, array, reallocSize);

        //yeaaa searches
        indexVal = search(array, target, reallocSize, blockSize);
        average += indexVal.timer;
        if(indexVal.timer > maximum) {
          maximum = indexVal.timer;
        }
        else if (indexVal.timer < minimum) {
          minimum = indexVal.timer;
        }
	//printf("indexVal: %d\n", indexVal);
        //printf("*(array+indexVal): %d\n", *(array+indexVal));
    }
    printf("The minimum runtime for test case 1 was %d\n", minimum);
    printf("The maximum runtime for test case 1 was %d\n", maximum);
    printf("The mean runtime for test case 1 was %d\n", (average / 40));
}

void testThree(int* array, int arrLen, int targ) {
  printf("Running test case 3\n");
  int blockSize = 250;
  int reallocSize = 250;
  int oldSize = 0;
  struct data indexVal;
  indexVal.timer = 0;
  indexVal.targetIndex = 0;
  int minimum = INT_MAX;
  int maximum = 0;
  int average = 0;
  int target = targ;
  //searches once before it enters the loop, reallocs before because of test case one
  array = (int*) realloc(array, sizeof(int) * reallocSize);
  fillArr(array, reallocSize, oldSize);
  scramble(array, 250);
  indexVal = search(array, target, reallocSize, blockSize);
  average += indexVal.timer;
  if(indexVal.timer > maximum) {
    maximum = indexVal.timer;
  }
  else if (indexVal.timer < minimum) {
    minimum = indexVal.timer;
  }
  printf("This is blockSize 250, resulting in 40 processes/threads\n");
  while(reallocSize < arrLen) {
    oldSize = reallocSize;

    reallocSize += blockSize;

    array = (int*) realloc (array, sizeof(int) * reallocSize);

    fillArr(array,reallocSize,oldSize);

    rescramble(indexVal.targetIndex, array, reallocSize);

    indexVal = search(array, target, reallocSize, blockSize);

    average += indexVal.timer;
    if(indexVal.timer > maximum) {
      maximum = indexVal.timer;
    }
    else if (indexVal.timer < minimum) {
      minimum = indexVal.timer;
    }
  }
  printf("The minimum runtime for test case 3 was %d\n", minimum);
  printf("The maximum runtime for test case 3 was %d\n", maximum);
  printf("The mean runtime for test case 3 was %d\n", (average / 40));
  printf("\n");

  printf("This is blockSize 200. resulting in 50 processes/threads\n");
  blockSize = 200;
  reallocSize = 200;
  oldSize = 0;
  indexVal.timer = 0;
  indexVal.targetIndex = 0;
  minimum = INT_MAX;
  maximum = 0;
  average = 0;
  array = (int*) realloc(array, sizeof(int) * reallocSize);
  fillArr(array, reallocSize, oldSize);
  scramble(array, 200);
  indexVal = search(array, target, reallocSize, blockSize);
  average += indexVal.timer;
  if(indexVal.timer > maximum) {
    maximum = indexVal.timer;
  }
  else if (indexVal.timer < minimum) {
    minimum = indexVal.timer;
  }
  while(reallocSize < arrLen) {
    oldSize = reallocSize;

    reallocSize += blockSize;

    array = (int*) realloc (array, sizeof(int) * reallocSize);

    fillArr(array,reallocSize,oldSize);

    rescramble(indexVal.targetIndex, array, reallocSize);
    indexVal = search(array, target, reallocSize, blockSize);

    average += indexVal.timer;
    if(indexVal.timer > maximum) {
      maximum = indexVal.timer;
    }
    else if (indexVal.timer < minimum) {
      minimum = indexVal.timer;
    }
  }
  printf("The minimum runtime for test case 3 was %d\n", minimum);
  printf("The maximum runtime for test case 3 was %d\n", maximum);
  printf("The mean runtime for test case 3 was %d\n", (average / 50));
  printf("\n");

  printf("This is blockSize 100, resulting in 100 processes/threads\n");
  blockSize = 100;
  reallocSize = 100;
  oldSize = 0;
  minimum = INT_MAX;
  indexVal.timer = 0;
  indexVal.targetIndex = 0;
  maximum = 0;
  average = 0;
  array = (int*) realloc(array, sizeof(int) * reallocSize);
  fillArr(array, reallocSize, oldSize);
  scramble(array, 100);
  indexVal = search(array, target, reallocSize, blockSize);
  average += indexVal.timer;
  if(indexVal.timer > maximum) {
    maximum = indexVal.timer;
  }
  else if (indexVal.timer < minimum) {
    minimum = indexVal.timer;
  }
  while(reallocSize < arrLen) {
    oldSize = reallocSize;

    reallocSize += blockSize;

    array = (int*) realloc (array, sizeof(int) * reallocSize);

    fillArr(array,reallocSize,oldSize);

    rescramble(indexVal.targetIndex, array, reallocSize);

    indexVal = search(array, target, reallocSize, blockSize);

    average += indexVal.timer;
    if(indexVal.timer > maximum) {
      maximum = indexVal.timer;
    }
    else if (indexVal.timer < minimum) {
      minimum = indexVal.timer;
    }
  }
  printf("The minimum runtime for test case 3 was %d\n", minimum);
  printf("The maximum runtime for test case 3 was %d\n", maximum);
  printf("The mean runtime for test case 3 was %d\n", (average / 100));
}


int main (int argc, char** argv){
    struct data targetIndex;
    srand(time(0));
    int arrLen = 250; //this will change as oppropriate in future
    int target = 7; //hardcode to always be the case
    int* array =(int*) malloc(sizeof(int)*arrLen);
    // FILLING IN "arrPtr"
    fillArr(array, arrLen, 0);
    // SCRAMBLE
    scramble(array, arrLen);

    testOne(array, 10000,target);//make 10,000 and then 20,000

    testThree(array, 10000,target);

    return 0;
}
