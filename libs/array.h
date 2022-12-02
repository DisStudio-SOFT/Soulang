#ifndef libarray
    #define libarray
    #include <stddef.h>

    typedef struct array {
        char *string;
        size_t size;
    } array;
    void arrayInit(array *arr);
    void arrayPush(array *arr, char ch);
    void arrayCopy(array *destarr, array srcarr);
    void arrayFree(array *arr);
#endif