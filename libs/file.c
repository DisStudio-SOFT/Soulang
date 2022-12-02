#include <stdio.h>
#include "array.h"

array fileRead(char *path){
    array content;
    arrayInit(&content);

    FILE *file =     fopen(path, "r");
    char readChar =  0;
    if(ferror(file))
        perror("file");

    while((readChar = fgetc(file)) != EOF)
        arrayPush(&content, readChar);
    arrayPush(&content, '\n');
    
    return content;
}