#include <stdio.h>
#include <stdlib.h>
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


int main(){
    
    int i = 99;
    char *ptr;
    while (i<100){
        ptr = (char*) malloc(4090);
        printf("String is %p\n", ptr);
        i++;
    }
    printf("This is ptr's used: %hi\n", *(short*)ptr)
    free(ptr);
    /*
    int i;
    for (i = 0; i<=3; i++) {
        printf("These are the values of arr at index %d: %c\n", i, *(ptr + i));
    }

    printf("This is ptr's val: %c\n", *ptr);
    */

    return 1;
}
