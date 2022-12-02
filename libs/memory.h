#ifndef libmemory
    #define libmemory
    #include <stddef.h>

    void *alloc(size_t size);
    void *ralloc(void *pointer, size_t size);
#endif