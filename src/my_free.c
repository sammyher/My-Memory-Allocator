#include <stdio.h>
#include <stdlib.h>
#include "m.h"

static void merge_next_block(t_block *block){
  t_block *next_block = block->next;

  if(block && next_block && next_block->is_free){
    block->size += sizeof(t_block) + next_block->size;
    block->next = next_block->next;
    if(next_block->next){
      next_block->next->prev = block;
    }

    if(g_heap_anchor){
      g_heap_anchor->block_count--;
      g_heap_anchor->free_size += sizeof(t_block);
    }
  }
}

static void merge_prev_block(t_block *block){
  t_block *prev_block = block->prev;

  if(block && prev_block && prev_block->is_free){
    prev_block->size += sizeof(t_block) + block->size;
    prev_block->next = block->next;
    if(block->next){
      block->next->prev = prev_block;
    }

    if(g_heap_anchor){
      g_heap_anchor->block_count--;
      g_heap_anchor->free_size += sizeof(t_block);
    }
  }
}

void merge_blocks(t_block *block){
  merge_next_block(block);
  merge_prev_block(block);
}

void my_free(void *ptr){
  t_block *block;

  if(!ptr || !g_heap_anchor){
    return;
  }

  block = (t_block*)((char*)ptr - sizeof(t_block));
  block->is_free = TRUE;

  g_heap_anchor->free_size += block->size + sizeof(t_block);

  merge_blocks(block);
}
