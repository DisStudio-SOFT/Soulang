#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "core_settings.h"
#define MAX_ADDRESS_SIZE 4

struct _stack {
    uint8_t *arr;
    size_t pos;
    size_t size;
} stack;

void stack_push(uint8_t value){
    if(stack.pos >= stack.size){
        stack.size += 32;
        stack.arr = realloc(stack.arr, stack.size * sizeof(uint8_t));
        if(!stack.arr)
            perror("memory");
    }
    stack.arr[stack.pos++] = value;
}

void error(char *msg){
    printf("error: %s\n", msg);
    exit(EXIT_FAILURE);
}
size_t getaddress(uint8_t *code, size_t pos){
    size_t address = 0;
    size_t column = 1;
    for(size_t posSize = 0; posSize < MAX_ADDRESS_SIZE; posSize++){
        address += code[pos+MAX_ADDRESS_SIZE-posSize] * column;
        column *= 10;
    }
    return address;
}

void run(size_t size, uint8_t *code){
    stack.arr =  malloc(STACK_INITSIZE * sizeof(uint8_t));
    stack.pos =  0;
    stack.size = STACK_INITSIZE;
    size_t address;
    for(size_t pos=0; pos < size; pos++){
        switch(code[pos]){
            case STACK_PUSH:
                stack_push(code[pos+1]);
                break;
            /*case STACK_POP:
                stack.arr[--stack.pos] = 0;
                break;*/
            case STACK_CLEAR:
                free(stack.arr);
                stack.arr =  malloc(STACK_INITSIZE * sizeof(uint8_t));
                stack.pos =  0;
                stack.size = STACK_INITSIZE;
                break;
            case STACK_PRINT: 
                address = getaddress(code, pos);
                if(address >= stack.pos)
                    error("Out of stack.");
                for(size_t stackPos = address; stack.arr[stackPos]; stackPos--)
                    printf("%c", stack.arr[stackPos]);
                pos += MAX_ADDRESS_SIZE-1;
                break;
        }
    }
    free(stack.arr);
}