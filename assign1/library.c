#include <stdio.h>
#include <string.h>
#include "header.h"

//x is # of bytes
//one given, scan array
//how scan?
//  start at beginning of array, check for magic number
//      if magic number, that means metadata so skip ahead appropriately and check progress
//      else scan next x bytes checking for magic number
//          if can't scan x bytes by hitting magic number, skip ahead appropriately
//          else create the metadata and throw in user data
//skip ahead appropriately:
//  traverse until see the short "use", and then jump ahead that much + 2
//throw in user data:
//  returning a pointer should be a memory address of arr

static char arr[4096];

void* mymalloc(int x){
    struct meta data;
    data.magicNum = 1000000;
    data.used = (short) x;

    /*
// loop until finds empty space 
    int i = 0;
    while (arr[i] == data.magicNum){
        i++;
    }
// finds enough free space
    int freeSpace = 0;
    while (freeSpace <= x+6){
        if(arr[i] != data.magicNum){
            freeSpace++;
        }
        else{
            printf("fucked up, not enough free space\n");
            break;
        }
    }

// insert struct into arr
    int* magicNumPtr = (int*)arr;
    short* usePtr = (int*)arr;

   */// just dupm struct inside use memcopy 
    memcpy(arr, (void *) &data, sizeof(data));
    char* ptr = ((char *) &arr + 6);
    
    // printf("This is the value at  ptr: %s\n", *ptr);

    printf("arr = %p, ptr = %p\n", &arr, ptr);

    *ptr = 'a';
    *(ptr + 1) = 'b';
    *(ptr + 2) = 'c';
    *(ptr + 3) = '\0';

    printf("arr: %s\n", arr + 6);
    
    return (void*) ptr;

    
/*
    char *ptr = &arr[0];
    printf("*ptr's value %c\n", *ptr);
    printf("ptr's value %p\n", ptr);

    return ptr;
    */
}


void  myfree(int x){
    printf("\nThis is x + 2: \n");
   
}
