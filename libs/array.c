#include <stdlib.h>
#include <string.h>
#include "memory.h"
#include "array.h"
#define getcharsize(size) (size) * sizeof(char)

void arrayInit(array *arr){
    arr->string = alloc(0);
    arr->size = 0;
}
void arrayPush(array *arr, char ch){
    arr->string =              ralloc(arr->string, getcharsize((++arr->size)));
    arr->string[arr->size-1] = ch;
}
void arrayCopy(array *destarr, array srcarr){
    arrayFree(destarr);
    destarr->size =   srcarr.size;
    destarr->string = alloc(getcharsize(destarr->size));
    strcpy(destarr->string, srcarr.string);
}
void arrayFree(array *arr){
    free(arr->string);
    arr->size = 0;
}