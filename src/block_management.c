##include <stdio.h>
#include <stdlib.h>
#include "m.h" 

t_block *find_free_block(size_t size){
  t_block *block;

  if(!g_heap_anchor){
    return NULL;
  }

  block = (t_block*)HEAP_SHIFT(g_heap_anchor);

  while(block){
    if(block->is_free && block->size >= size){
      if(block->size >= size + sizeof(t_block) + 16){
        split_block(block, size);
      }
      else{
        block->is_free = FALSE;
      }
      return block;
    }
    block = block->next;
  }

  return NULL;
}

t_block *split_block(t_block *block, size_t size){
  t_block *new_block;

  new_block = (t_block*)(BLOCK_SHIFT(block) + size);

  new_block->size = block->size - size - sizeof(t_block);
  new_block->is_free = TRUE;
  new_block->next = block->next;
  new_block->prev = block;

  if(block->next){
    block->next->prev = new_block;
  }

  block->size = size;
  block->is_free = FALSE;
  block->next = new_block;

  if(g_heap_anchor){
    g_heap_anchor->block_count++;
  }

  return block;
}
