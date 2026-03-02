#include "m.h"

void *ft_memcpy(void *dst, const void *src, size_t n) {
    char *d = dst;
    const char *s = src;
    while (n--)
        *d++ = *s++;
    return (dst);
}

void *my_realloc(void *ptr, size_t new_size){
  t_block *old_block;
  void *new_ptr; 

  if(!ptr){
    return (my_malloc(new_size));
  }

  if(new_size == 0){
    my_free(ptr);
    return NULL;
  }

  old_block = (t_block*)((char*)ptr - sizeof(t_block));

  if(new_size == old_block->size){
    return ptr;
  }

  new_ptr = my_malloc(new_size);
  if(!new_ptr){
    return NULL;
  }

  ft_memcpy(new_ptr, ptr, old_block->size < new_size ? old_block->size : new_size);

  my_free(ptr);

  return (new_ptr);
}
