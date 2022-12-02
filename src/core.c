#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libs/array.h"
#include "../libs/memory.h"

enum typeword{
    TW_NONE =    0x00,
    TW_CALL =    0x01,
    TW_VAR =     0x02
};
array output;
struct _vars{
    array  *names;
    size_t *addresses;
    size_t  size;
} vars;
size_t size_virtual_stack = 0;

void run(array command, enum typeword typecommand, array *args, size_t argssize){
    printf("command: %s\n", command.string);
    puts("args:");
    for(size_t pos = 0; pos < argssize; pos++)
        printf("   arg %lu: %s\n", pos, args[pos].string);
    switch((char) typecommand){
        case TW_VAR:
            if(!strcmp(command.string, "string")){
                arrayPush(&output, 0x10);
                arrayPush(&output, 0x00);
                size_virtual_stack++;
                for(size_t pos=args[2].size-1; args[2].string[pos]; pos--){
                    arrayPush(&output, 0x10);
                    arrayPush(&output, args[2].string[pos]);
                    size_virtual_stack++;
                }
            }
            vars.names =                  ralloc(vars.names, (++vars.size) * sizeof(array));
            vars.addresses =              ralloc(vars.addresses, (vars.size) * sizeof(size_t));
            vars.names[vars.size-1] =     args[0];
            vars.addresses[vars.size-1] = size_virtual_stack-1;
            break;
        case TW_CALL:
            if(!strcmp(command.string, "printvarstr")){
                arrayPush(&output, 0x20);
                for(size_t pos=0; pos < vars.size; pos++){
                    if(!strcmp(vars.names[pos].string, args[0].string)){
                        if(vars.addresses[pos] < 0xffff)
                            arrayPush(&output, 0x00);
                        if(vars.addresses[pos] < 0x0fff)
                            arrayPush(&output, 0x00);
                        if(vars.addresses[pos] < 0x00ff)
                            arrayPush(&output, 0x00);
                        arrayPush(&output, (char)vars.addresses[pos]);
                    }
                }
            }
            break;
    }
}

array runcode(array code){
    arrayInit(&output);
    vars.names =     alloc(0);
    vars.addresses = alloc(0);
    short begin =               1;
    short strskip =             0;
    enum typeword typecommand = TW_NONE; 
    array *args =               alloc(0);
    size_t argssize =           0;
    array command;
    array word;
    arrayInit(&command);
    arrayInit(&word);          
    for(size_t pos=0; pos < code.size; pos++){
        char ch = code.string[pos];
        if(ch == '\'' || ch == '"'){
            strskip = !strskip;
            continue;
        }
        if(typecommand != TW_NONE && !strskip){
            if((typecommand == TW_VAR && ch == ' ') || (typecommand == TW_CALL && ch == ',') || ch == '\n'){
                if(word.size == 0)
                    continue;
                args = ralloc(args, (++argssize) * sizeof(array));
                args[argssize-1] = word;
                arrayInit(&word);
            }
        }
        if((ch == ':' || ch == ' ') && begin){
            typecommand = (ch == ':') ? TW_CALL : TW_VAR;
            arrayCopy(&command, word);
            begin = 0;
            arrayFree(&word);
            arrayInit(&word);
            continue;
        } else if(ch == '\n' && !strskip){
            run(command, typecommand, args, argssize);

            arrayFree(&command);
            arrayInit(&command);
            free(args);
            args =        alloc(0);
            argssize =    0;
            begin =       1;
            typecommand = TW_NONE;
            continue;
        }
        if(ch == ' ' && !strskip)
            continue;
        arrayPush(&word, ch);
    }
    puts("output code:");
    size_t step = 1;
    for(size_t pos = 0; pos < output.size; pos++, step++){
        printf("%c", (output.string[pos] < 0x10) ? '0' : '\0');
        printf("%X ", output.string[pos]);
        if(step == 10){
            step = 0;
            putchar('\n');
        }
    }
    if(step < 10)
        putchar('\n');
    return output;
}