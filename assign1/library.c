#include <stdio.h>
#include <string.h>
#include "header.h"

static char arr[4096];
/*
 * test cases:
 *
 * malloc(4096): y
 * malloc(4097): n
 * malloc(0): n
 * malloc(1) 100 times: y
 * malloc(4000) 2 times
 */





void* mymalloc(int x){
    
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
    int *ptrTemp;

    // 'usedTemp' reads short from arr, used to check for amt of user data and to jump
    unsigned short *usedTemp;
    
    // run until found enough free space for metadata and userdata, and did not have to traverse out of bounds
    while(freeSpace <= x + 6 && i<=4097){
        
        // assigns 'ptrTemp' to int pointer casted to arr at index i
        ptrTemp = (int*)&arr[i];
        
        if(*ptrTemp == data.magicNum){//should be true after first time
            freeSpace = 0;
            usedTemp = (unsigned short*)&arr[i+4];
            i = i + *usedTemp + 6;
            continue;
        }else{
            freeSpace++;
        }
        i++;
    }
    // copies magicNum into arr
    memcpy(&arr[i-x-7], (void *) &data, sizeof(data));
    printf("\nmetadata index: %p\n", &arr[i-x-7]);
    printf("This is i: %d\n",i);
    // creates ptr to 6 bytes after metadata
    if (i >  4097){
        printf("\n------------null-----\n");
        return NULL;
    }
    char* ptr = ((char *) &arr[i-x-1]);
    
    return (void*) ptr;

}

void  myfree(void* ptr){
    // check if pointer, equal to NULL, beginning of memory, 
    // check pointer points to our array
    if(ptr == NULL) {
        return;
    }

    if(!((char*)ptr<=&arr[4095] && (char*)ptr>=&arr[0])){
        return;
    }

    // if -6, should be magic number
    int *metaNum =  (int*)(ptr-6);
    unsigned short* metaUsed = (unsigned short*)(ptr - 2);
    printf("This is .magicNum: %d\n", *metaNum);
    printf("This is .Used: %hi\n", *metaUsed);

    if (*metaNum == 10001){
        // set previous 6 and next shorts to 'a's'
        char *i;
        int loop = 0;
        int stop = *metaUsed + 5;
        for (i = (char*)(ptr-6); loop <= stop;i++){
            *i='a';
            loop++;
        }
        printf("success");
    }else{
        return;
    }
    
    return;
}
