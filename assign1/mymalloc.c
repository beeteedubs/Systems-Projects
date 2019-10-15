#include <stdio.h>
#include <string.h>
#include "mymalloc.h"


/*
 * test cases:
 *
 * malloc(4096): y
 * malloc(4097): n
 * malloc(0): n
 * malloc(1) 100 times: y
 * malloc(4000) 2 times
 */

static char arr[4096];

void* mymalloc(int x, const char* file, int line){

    //printf("mymallocing ------: ");
    
    // metadata composed of 6 bytes: 4 bytes for magicNum, 2 bytes for how much user data
    // x is out of range, -6 for metadata
    if(x<=0 || x>4090){
        return NULL;
    }
    
    // declaring metadata
    struct meta data;
    data.magicNum = 10001;
    data.used = (unsigned short) x;
    
    //'fresSpace' keeps track potential space for user data, also used for loop condition
    int freeSpace = 0;

    // 'i' iterates/jumps along arr, also used for loop condition, [0,4095]
    int i = 0;
    
    // 'ptrTemp' reads an int from arr, used to check for magicNum
   // int *ptrTemp;

    // 'usedTemp' reads short from arr, used to check for amt of user data and to jump
    unsigned short usedTemp;
    
    struct meta metaData;
    // run until found enough free space for metadata and userdata, and did not have to traverse out of bounds
    while(freeSpace < x + sizeof(metaData) && i<=4096){
        
        // assigns 'ptrTemp' to int pointer casted to arr at index i
       // ptrTemp = (int*)&arr[i];
        
        memcpy(&metaData, &arr[i], sizeof(struct meta));
        if( metaData.magicNum == data.magicNum){//should be true after first time
            freeSpace = 0;
            usedTemp = metaData.used;
            i = i + usedTemp + sizeof(struct meta);
            continue;
        }else{
            freeSpace++;
        }
        i++;
    }
    
    // copies magicNum into arr
    memcpy(&arr[i-x-sizeof(data)], (void *) &data, sizeof(data));
    //printf("\nmetadata index: %p\n", &arr[i-x-7]);
    //printf("This is i: %d\n",i);
    // creates ptr to 6 bytes after metadata
    if (i >  4096){
        printf("\n------------null-----\n");
        return NULL;
    }
    char* ptr = ((char *) &arr[i-x]);
    printMal();
    return (void*) ptr;

}
void printMal(){
    printf("This is arr: %s\n", arr);
}


void  myfree(void* ptr, const char* file, int line){
    // check if pointer, equal to NULL, beginning of memory, 
    // check pointer points to our array
    //printf("myfreeing----: ");
    if(ptr == NULL) {
        return;
    }

    if(!((char*)ptr<=&arr[4095] && (char*)ptr>=&arr[0])){
        printf("you goofed out of range");
        return;
    }

    // if -6, should be magic number
    int metaSize = sizeof(struct meta);
    int *metaNum =  (int*)(ptr-metaSize);
    struct meta info;
    memcpy(&info, ptr-sizeof(info) , sizeof(info));
    //printf("This is .magicNum: %d\n", *metaNum);
    //printf("This is .Used: %hi\n", *metaUsed);
    
    if (*metaNum == 10001){
        // set previous 6 and next shorts to 'a's'
    
        memset(ptr-sizeof(info), 0, sizeof(info) + info.used);
        // for (i = (char*)(ptr-metaSize); loop <= stop;i++){
        //    *i='a';
         //   loop++;
       // }
    }else{
        return;
    }
    
    return;
}
