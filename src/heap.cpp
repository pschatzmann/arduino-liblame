#include "heap.h"

#if defined(ESP32)
//LameHeapCustomAllocator lameHeap(8000, 2000);
LameESP32HeapAllocator lameHeap;
#else
LameHeapStandardAllocator lameHeap;
#endif

LameHeapBase *p_lame_heap = &lameHeap;

void *lamex_calloc(int num, int size, int type) {
  return p_lame_heap->calloc(num, size, (AllocType) type);
}

void lamex_free(void *mem) { p_lame_heap->free(mem); }

void lame_abort() { p_lame_heap->abort(); }

void set_lame_heap(LameHeapBase *heap) { p_lame_heap = heap; }

void memset32(void *data,int value, int bytes){
  int32_t* p_data32 = (int32_t*)data; 
  int count = bytes / sizeof(int32_t);
  for (int j=0;j<count;j++){
    p_data32[j] = value;
  }
}

