#include "memory.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void arena_init(Arena *arena, unsigned char *buffer, size_t buffer_size) {
  arena->buffer = buffer;
  arena->buffer_size = buffer_size;
  arena->allocated = 0;
}

static uintptr_t arena_align(uintptr_t pointer, uintptr_t align) {
  // alignment must be a power of 2
  assert((align & (align - 1)) == 0);

  uintptr_t aligned = pointer;
  uintptr_t mod = aligned & (align - 1);
  if (mod != 0) {
    aligned += align - mod;
  }
  return aligned;
}

void *arena_allocate(Arena *arena, size_t size, size_t align) {
  uintptr_t end = (uintptr_t)arena->buffer + (uintptr_t)arena->allocated;
  uintptr_t offset = arena_align(end, (uintptr_t)align);
  offset -= (uintptr_t)arena->buffer;

  if (offset + size > arena->buffer_size) {
    fprintf(stderr, "Unable to allocate memory in arena, exiting.\n");
    exit(EXIT_FAILURE);
  }

  void *pointer = &arena->buffer[offset];
  arena->allocated = offset + size;
  memset(pointer, 0, size);
  return pointer;
}

void arena_reset(Arena *arena) { arena->allocated = 0; };

void *reallocate(void *ptr, size_t old_size, size_t new_size) {
  if (new_size == 0) {
    free(ptr);
    return NULL;
  }

  void *res = realloc(ptr, new_size);
  if (res == NULL) {
    exit(1);
  }

  return res;
}
