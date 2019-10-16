#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mymalloc.h"
suseconds_t A() {
    struct timeval start;
    struct timeval end;
    suseconds_t timer = 0;
    gettimeofday(&start, 0);
    int i = 0;
    char *ptr;
    while (i<150){
        ptr = (char*) malloc(1);
        *ptr = 'a';
        //printf("ptr is: %p\n", ptr);
        free(ptr);
        i++;
    }
    gettimeofday(&end,0);
    timer = timer + ((end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec)); 
    return timer;
};
suseconds_t B() {
    struct timeval start;
    struct timeval end;
    suseconds_t timer = 0;
    gettimeofday(&start, 0);
    int counter2 = 0;
    char *ptr2;
    char* array[50];
    int indexCounter = 0;
    while (counter2 < 150){
        ptr2 = (char*)malloc(1);
        //printf("Pointer at %p\n", ptr2);
        array[indexCounter] = ptr2;
        int freeCounter = 49;
        if(indexCounter == 49){
            //printf("Freeing now\n");
            while(freeCounter>=0){
                //printf("Freeing %p\n", array[freeCounter]);
                free(array[freeCounter]);
                freeCounter--;
            }
            indexCounter = 0;
            continue;
        }
        indexCounter++;
        counter2++;
    }   
    gettimeofday(&end, 0);
    timer = timer + ((end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec));
    return timer;
};

suseconds_t C() {
    struct timeval start;
    struct timeval end;
    suseconds_t timer = 0;
    gettimeofday(&start,0);
    int numMalls = 0;
    char* array2[50];
    char* ptr3;
    int indexCounter2 = 0;
    int rando;
    while(numMalls < 50){ 
       
        //if random number is even, we malloc
        //if random number is odd, we free
        rando = rand() % 2;
        if(rando == 0) {
            ptr3 = (char*) malloc(1);
            //printf("Malloc'ed: %p\n", ptr3);
            array2[indexCounter2] = ptr3;
            numMalls++;
            indexCounter2++;
        }
        else {
            if(indexCounter2 > 0 && array2[indexCounter2 - 1] != NULL) {
                //printf("Freeing: %p\n", array2[indexCounter2 - 1]);
                free(array2[indexCounter2 - 1]);
                indexCounter2--;
            }
        }
    }
    
    int counterTemp = 0;
    while(counterTemp < 50) {
        free(array2[counterTemp]);
        counterTemp++;
    }
    
    gettimeofday(&end,0);
    timer = timer + ((end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec));
    return timer;
};

suseconds_t D() {
    struct timeval start;
    struct timeval end;
    suseconds_t timer = 0;
    gettimeofday(&start,0);
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
       //printf("Running for the %dth time\n", counterD);
        malOrFree = rand()%2;
        if (malOrFree == 0){
            amtMal = (rand()%64) + 1; //gives [1,64]
            //printf("amtMalloc for the %dth time: %d\n", p, amtMal);
            arrD[arrDCounter] = (char*)malloc(amtMal);
            counterD++;
            arrDCounter++;
            memCap = memCap + amtMal + sizeof(struct meta); 
        }else{
            if(arrDCounter > 0){
            //printf("Freeing: %p\n", arrD[arrDCounter]);
            free(arrD[arrDCounter - 1]);
            arrDCounter--;
            }     
        }
   }
   int freeEverything = 0;
   while(freeEverything < 50)
   {
       //printf("\n\nBomb: Freeing: %p\n", arrD[freeEverything]);
        free(arrD[freeEverything]);
       freeEverything++;
   } 
   gettimeofday(&end,0);
   timer = timer + ((end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec));
    return timer;
};
suseconds_t E() {
    struct timeval start;
    struct timeval end;
    suseconds_t timer = 0;
    gettimeofday(&start,0);
    char* arrE[50];
    int counterE = 0;
    int freeCounter = 0;
    while(counterE < 50){ //loop runs 25 times, but mallocs 50 times, and frees 25 to show 
    

     arrE[counterE] = (char*)malloc(5);
     //printf("Malloc'ed: %p\n", arrE[counterE]);
     counterE++;
     
        arrE[counterE] = (char*)malloc(5);
        //printf("Malloc'ed: %p\n", arrE[counterE]);

        //printf("Freeing: %p\n", arrE[freeCounter]);
        free(arrE[freeCounter]);
        counterE++;
        freeCounter++;
    }
    int freeEverything = 0;
    while(freeEverything < 50) {
        free(arrE[freeEverything]);
        freeEverything++;
    }
    gettimeofday(&end, 0);
    timer = timer + ((end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec));
    return timer;
};

suseconds_t F() {
    struct timeval start;
    struct timeval end;
    suseconds_t timer = 0;
    gettimeofday(&start,0);
    int f = 0;
    char *ptr;
    while (f<150){
         ptr = (char*) malloc(1);
        //printf("ptrf is: %p\n", ptrF);
        *ptr = 'F';
        free(ptr);
        f++;
    }
    gettimeofday(&end,0);
    timer = timer + ((end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec));
    return timer;
};
int main(){
    
    srand(time(0));
    
    suseconds_t aa = 0;
    suseconds_t bb = 0;
    suseconds_t cc = 0;
    suseconds_t dd = 0;
    suseconds_t ee = 0;
    suseconds_t ff = 0;
    int i = 0;
    while(i < 100) {
        aa += A();
        i++;
    }
    printf("Success for A\n");
    i = 0;
    while(i < 100) {
        bb += B();
        i++;
    }
    printf("Success for B\n");
    i = 0;
    while(i < 100) {
        cc += C();
        i++;
    }
    printf("Success for C\n");
    i = 0;
    while(i < 100) {
        dd += D();
        i++;
    }
    printf("Success for D\n");
    i = 0;
    while(i < 100) {
        ee += E();
        i++;
    }
    printf("Success for E\n");
    i = 0;
    while(i < 100) {
        ff += F();
        i++;
    }
    printf("Success for F\n");
    printf("Avg runtime for A: %ld microseconds\n", (aa / 100));
    printf("Avg runtime for B: %ld microseconds\n", (bb / 100));
    printf("Avg runtime for C: %ld microseconds\n", (cc / 100));
    printf("Avg runtime for D: %ld microseconds\n", (dd / 100));
    printf("Avg runtime for E: %ld microseconds\n", (ee / 100));
    printf("Avg runtime for F: %ld microseconds\n", (ff / 100));
    return 0;
}   
