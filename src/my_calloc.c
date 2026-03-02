#include <stddef.h>
#include <string.h>
#include "m.h"

void *my_calloc(size_t num, size_t size) {
    size_t total_size = num * size;
    void *ptr;

    if(num != 0 && total_size / num != size) {
        return NULL;
    }

    ptr = my_malloc(total_size);

    if (ptr) {
        memset(ptr, 0, total_size);
    }

    return ptr;
}
