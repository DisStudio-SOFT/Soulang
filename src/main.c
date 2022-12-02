#include <stdio.h>
#include "../libs/file.h"
#include "core.h"

int main(int argc, char **argv){
    array code = fileRead(argv[1]);
    array output = runcode(code);
    FILE *outfile = fopen("a.svm", "w");
    for(size_t pos = 0; pos < output.size; pos++)
        fputc(output.string[pos], outfile);
    arrayFree(&output);
    arrayFree(&code);
    return 0;
}