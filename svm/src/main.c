#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "core.h"

int main(int argc, char **argv){
    FILE *file = fopen(argv[1], "r");
    uint8_t *content = malloc(0 * sizeof(uint8_t));
    size_t contentsize = 0;
    uint8_t ch;
    while((ch = fgetc(file)) != (uint8_t) EOF){
        content = realloc(content, (++contentsize) * sizeof(uint8_t));
        content[contentsize-1] = ch;
    }

    run(contentsize, content);

    free(content);
    fclose(file);
    return 0;
}