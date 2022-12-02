#include <stdio.h>
#include <stdlib.h>

void *alloc(size_t size){
    void *mem = malloc(size);
    if(!mem)
        perror("memory");
    return mem;
}
void *ralloc(void *pointer, size_t size){
    void *mem = realloc(pointer, size);
    if(!mem)
        perror("memory");
    return mem;
}