#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mymalloc.h"

int main(){
     srand(time(0));
   
    
    //A:
    int i = 0;
    char *ptr;
    while (i<150){
        ptr = (char*) malloc(1);
        printf("ptr is: %p\n", ptr);
        free(ptr);
        i++;
    }
    printf("success for A:\n\n\n\n  ");
    

/*
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
*/
/*
    
    //C:
    int numMalls = 0;
    char* array2[50];
    char* ptr3;
    int indexCounter2 = 0;
    int timez = 0;
   
    int rando;
    while(numMalls < 50){ 
       
        //if random number is even, we malloc
        //if random number is odd, we free
        rando = rand() % 2;
        if(rando == 0) {
            ptr3 = (char*) malloc(1);
            printf("Malloc'ed: %p\n", ptr3);
            array2[indexCounter2] = ptr3;
            numMalls++;
            indexCounter2++;
        }
        else {
            if(indexCounter2 > 0 && array2[indexCounter2 - 1] != NULL) {
                printf("Freeing: %p\n", array2[indexCounter2 - 1]);
                free(array2[indexCounter2 - 1]);
                indexCounter2--;
            }
        }
        timez++;
    }
    int counterTemp = 0;
    while(counterTemp < 50) {
        free(&array2[counterTemp]);
        counterTemp++;
    }*//*
    
    char* element;
    int loopC = 0;
    while(loopC<350){
        element = (char*) &arr[loopC];
        printf("arr's 1st 350 elements: %c\n", *element);
        loopC++;
    }
    //printf("array2's 0th index: %c\n", *array2[0]);
   // printf("number of times realuly ran: %d\n", timez);
   // printf("success for C: \n\n\n\n ");
    */
  /*  
    //D:
   int counterD = 0;//counts number of mallocs
   int amtMal;
    int memCap = 0;//should add up no more than 4096 bytes
    int malOrFree = 0; // 0 malloc, 1 free
    int arrDCounter = 0;// index of arrayD
    char* arrD[50];

    int junkCounter = 0;
    while(junkCounter<50){
        arrD[junkCounter] = NULL;
        junkCounter ++;
    }
   while(counterD < 50 && memCap < 4096){
        malOrFree = rand()%2;
        if (malOrFree == 0){
            amtMal = (rand()%64) + 1; //gives [1,64]
            arrD[arrDCounter] = (char*)malloc(amtMal);
            printf("Malloc'ed: %p\n", arrD[arrDCounter]);
            counterD++;
            arrDCounter++;
            memCap = memCap + amtMal + sizeof(struct meta); 
        }else{

            if(arrDCounter > 0){
              arrDCounter--;
            printf("Freeing: %p\n", arrD[arrDCounter]);
            free(arrD[arrDCounter]);
            }     
        }
   }
   int freeEverything = 0;
   while(freeEverything < 50)
   {         
       printf("\n\nBomb: Freeing: %p\n", arrD[freeEverything]);
        free(arrD[freeEverything]);
       freeEverything++;
   }*/
   /* 
    //E
   //free from a random index in the array
    char* arrE[50];
    int counterE = 0;
    int freeCounter = 0;
    while(counterE < 50){ //loop runs 25 times, but mallocs 50 times, and frees 25 to show 
    

        arrE[counterE] = (char*)malloc(5);
        printf("Malloc'ed: %p\n", arrE[counterE]);
        counterE++;
     
        arrE[counterE] = (char*)malloc(5);
        printf("Malloc'ed: %p\n", arrE[counterE]);

        printf("Freeing: %p\n", arrE[freeCounter]);
        free(arrE[freeCounter]);
        counterE++;
        freeCounter++;
    }*/
    //F
    /*
    int f = 0;
    char *ptrF;
    while (f<150){
        ptrF = (char*) malloc(1);
        printf("ptrf is: %p\n", ptrF);
       // *ptrF = 'F';
        free(ptrF);
        f++;
    }
    printf("success for f:\n\n\n\n  ");*/
    return 1;
}
