#include <stdio.h>
#include <string.h>
#include "header.h"

static char arr[4096];

void* mymalloc(int x){
    // ------------------ CHANGE LATER
    // - use magicNum once
    
    // metadata composed of 6 bytes: 4 bytes for magicNum, 2 bytes for how much user data
    //
    struct meta data;
    data.magicNum = 70;
    data.used = (short) x;
    int sumArr[4];
    int freeSpace = 0;
    int i = 0;
    while(arr[i] != data.magicNum && freeSpace <= x+6) {

        // loop until finds empty space 
                
        if(arr[i] == data.magicNum){//should be true after first time
            freeSpace = 0;
        }else{
            freeSpace++;
        }

        // just dupm struct inside use memcopy 
        memcpy(sumArr, &arr[i], sizeof(data.magicNum));
        i++;
    }
    // copies metadata into arr
    memcpy(&arr[i-x-6], (void *) &data, sizeof(data));
    printf("\narr = %p\n", &arr[i-x-6]);

    // creates ptr to 6 bytes after metadata
    char* ptr = ((char *) &arr[i-x]);
    
    return (void*) ptr;

    
}

void  myfree(int x){
    printf("\nThis is x + 2: \n");
   
}
