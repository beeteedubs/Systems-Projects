#include <stdio.h>
#include <string.h>
#include "header.h"

static char arr[4096];

void* mymalloc(int x){
    // ------------------ CHANGE LATER
    // - use magicNum once
    
    // metadata composed of 6 bytes: 4 bytes for magicNum, 2 bytes for how much user data
    
    if(x<0 || x>4090){
        return NULL;
    }

    struct meta data;
    data.magicNum = 10001;
    data.used = (unsigned short) x;
    
    int freeSpace = 0;
    int i = 0;
   while(freeSpace <= x + 6) {

        // loop until finds empty space 
        if(arr[i] == data.magicNum){//should be true after first time
            freeSpace = 0;
            i = i + arr[i + 4] + 6;
            continue;
        }else{
            freeSpace++;
        }
        i++;
    }
    // copies metadata into arr
    memcpy(&arr[i-x-7], (void *) &data, sizeof(data));
    printf("\nmetadata index: %p\n", &arr[i-x-7]);
    printf("This is i: %d\n",i);
    // creates ptr to 6 bytes after metadata
    if (i >  4097){
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

    // if -6, should be magic number
    int metaNum = * (char*)(ptr-6);
    unsigned short metaUsed = *(char*)(ptr - 2);
    printf("This is metaNum: %d\n", metaNum);
    printf("This is metaUsed: %hi\n", metaUsed);

    if (metaNum == 10001){
        // set previous 6 and next shorts to 'a's'
        int i;
        for (i = -6; i < metaUsed;i++){
            arr[i]='a';
        }
    }else{
        return;
    }
    
    return;
}
