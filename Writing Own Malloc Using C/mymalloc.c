#include <stdio.h>
#include <assert.h>
#include <pthread.h>
#include <stdbool.h>
#include <string.h>

#define HEAP_CAPACITY 640000
char heap[HEAP_CAPACITY] = {0};
size_t heap_size = 0;

void *heap_alloc(size_t size) {
  assert(heap_size + size <= HEAP_CAPACITY); 
  void *result = heap + size;
  heap_size += size;
  return result;
}

void heap_free(void *ptr) {
  assert(false && "TODO: heap_free is not implemented.");
}
void heap_collect() {
  assert(false && "TODO: heap_free is not implemented.");
}

int main() {
  char *root = heap_alloc(26);
  for(int i = 0; i < 26; ++i) {
    root[i] = i + 'A';
  }
  return 0;
}
