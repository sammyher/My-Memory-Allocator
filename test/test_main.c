#include <stdio.h>
#include <string.h>
#include "m.h"

void print_heap_stats() {
    if (g_heap_anchor) {
        printf("[Heap Stats] Total: %zu, Free: %zu, Blocks: %zu\n", 
                g_heap_anchor->total_size, 
                g_heap_anchor->free_size, 
                g_heap_anchor->block_count);
    } else {
        printf("[Heap Stats] Heap not initialized.\n");
    }
}

int main() {
    printf("--- Starting Memory Allocator Tests ---\n");

    printf("\nTest 1: Basic Allocation\n");
    char *ptr1 = (char *)my_malloc(100);
    if (ptr1) {
        printf("Allocated 100 bytes at %p\n", (void*)ptr1);
        strcpy(ptr1, "Hello Memory Allocator!");
        printf("Data stored: %s\n", ptr1);
    }
    print_heap_stats();

    printf("\nTest 2: Alignment Check\n");
    void *ptr2 = my_malloc(17);
    printf("Allocated 17 bytes at %p\n", ptr2);
    // size = (17 + 15) & ~15 = 32
    print_heap_stats();

    printf("\nTest 3: Multiple Allocations\n");
    void *ptr3 = my_malloc(512);
    void *ptr4 = my_malloc(1024);
    print_heap_stats();

    printf("\nTest 4: Free and Block Merging\n");
    printf("Freeing ptr2 and ptr3...\n");
    my_free(ptr2);
    my_free(ptr3);
    // my_free calls merge_blocks which should join adjacent free blocks
    print_heap_stats();

    printf("\nTest 5: Re-allocating Freed Space\n");
    void *ptr5 = my_malloc(200);
    printf("Allocated 200 bytes at %p\n", ptr5);
    print_heap_stats();

    printf("\nTest 6: Stressing Capacity\n");
    void *too_big = my_malloc(HEAP_SIZE * 2);
    if (too_big == NULL) {
        printf("Correctly refused allocation larger than heap.\n");
    }

    printf("\nFinal Cleanup\n");
    my_free(ptr1);
    my_free(ptr4);
    my_free(ptr5);
    print_heap_stats();

    printf("\n--- Tests Complete ---\n");
    return 0;
}
