#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include "m.h"

t_heap *g_heap_anchor = NULL;

void *t_heap init_heap(void){
  t_heap *heap;

  heap (t_heap *) = mmap(
    NULL,
    HEAP_SIZE,
    PROT_READ | PROT_WRITE, 
    MAP_ANONYMOUS | MAP_PRIVATE,
    -1,
    0
  );

  if(heap == MAP_FAILED){
    return NULL;
  }

  heap->total_size = HEAP_SIZE;
  heap->free_size = HEAP_SIZE - sizeof(t_heap);
  heap->block_count = 0;

  return heap;
}

t_heap *heap_get(size_t size){

  if(g_heap_anchor == NULL)
  {
    g_heap_anchor = init_heap();
  }

  if(g_heap_anchor && g_heap_anchor->free_size >= (size + sizeof(t_heap)))
  {
    return g_heap_anchor;
  }
   
  return NULL;
  
}


