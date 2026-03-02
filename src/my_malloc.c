#include <stdio.h>
#include <stdlib.h>
#include "m.h"

void *my_malloc(size_t size){
  t_heap *heap;
  t_block *block;

  if(size == 0){
    return NULL;
  }

  size = (size + 15) & ~15;

  heap = heap_get(size);
  if(!heap){
    return NULL;
  }

  if(heap->block_count == 0){
    block = (t_block*)(HEAP_SHIFT(heap));
    block->size = heap->free_size - sizeof(t_block);
    block->is_free = TRUE;
    block->next = NULL;
    block->prev = NULL;
    heap->block_count++;
  }

  block = find_free_block(size);
  if(block){
    heap->free_size -= (block->size + sizeof(t_block));
    return BLOCK_SHIFT(block);
  }

  return NULL;
}
