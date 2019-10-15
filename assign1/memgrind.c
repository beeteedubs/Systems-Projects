#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mymalloc.h"

int main(){
   /*
    
    //A:
    int i = 0;
    char *ptr;
    while (i<150){
        ptr = (char*) malloc(1);
        printf("ptr is: %x\n", ptr);
        free(ptr);
        i++;
    }
    printf("success for A:\n\n\n\n  ");
    
*/

    //B:
    char*ptr = 0x60160 - 1;
    free(ptr);
    ptr = 0x60160 + 4096;
    free(ptr);
    
    int counter2 = 0;
    char *ptr2;
    char* array[50];
    int indexCounter = 0;
    while (counter2 < 150){
        ptr2 = (char*)malloc(1);
        printf("Pointer at %p\n", ptr2);
        array[indexCounter] = ptr2;
        int freeCounter = 49;
        if(indexCounter == 49){
            printf("Freeing now\n");
            while(freeCounter>=0){
                printf("Freeing %p\n", array[freeCounter]);
                free(array[freeCounter]);
                freeCounter--;
            }
            printf("\n\n\n");

            indexCounter = 0;
            continue;
        }
        indexCounter++;
        counter2++;
       // printf("counter2: %d\n", counter2);
        //printf("indexCounter: %d\n", indexCounter);
    }   
    printf("success for B:\n\n\n\n  ");

/*
    
    //C:
    int numMalls = 0;
    char* array2[50];
    char* ptr3;
    int indexCounter2 = 0;
    int timez = 0;
    srand(time(0));
    int rando;
    while(numMalls < 50){ 
       
        //if random number is even, we malloc
        //if random number is odd, we free
        rando = rand() % 2;
        printf("rando: %d\n", rand());
        if(rando == 0) {
            ptr3 = (char*) malloc(1);
            array2[indexCounter2] = ptr3;
            numMalls++;
            indexCounter2++;
        }
        else {
            free(&array2[indexCounter2]);
            if(array2[indexCounter2] != NULL) {
                indexCounter2--;
            }
        }
        timez++;
    }
    int counterTemp = 0;
    while(counterTemp < 50) {
        free(&array2[counterTemp]);
        counterTemp++;
    }
    
    char* element;
    int loopC = 0;
    while(loopC<350){
        element = (char*) &arr[loopC];
        printf("arr's 1st 350 elements: %c\n", *element);
        loopC++;
    }
    //printf("array2's 0th index: %c\n", *array2[0]);
   // printf("number of times really ran: %d\n", timez);
   // printf("success for C: \n\n\n\n ");


        */

    return 1;
}
