#ifndef M_H
#define M_H

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>


#define MEGABYTES 1024 * 1024
#define HEAP_SIZE 10 MEGABYTES

extern t_heap *g_heap_anchor;

void my_free(void *ptr);
void merge_blocks(t_block *block);
void my_malloc(size_t size);


typedef enum e_bool{
  FALSE = 0; 
  TRUE = 1;
}t_bool;

typedef struct s_block{
  size_t size;
  t_bool is_free;
  struct s_block *next;
  struct s_block *prev;
}t_block;

typedef struct s_heap{
  size_t total_size;
  size_t free_size;
  size_t block_count;
}t_heap;



#endif /* M_H */
