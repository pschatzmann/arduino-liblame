#pragma once
#include <stdint.h>

enum AllocType { A_FLOAT=1, A_INT=2, A_BYTE=3 };

#ifdef __cplusplus

#include <stdio.h>

#include <vector>

#include "lame.h"
#include "lame_log.h"
#include "liblame/config.h"

#ifdef ARDUINO
#include "Arduino.h"
#endif


extern "C" {

/**
 * @brief Base Class for different memory allocation strategies
 */
class LameHeapBase {
 public:
  virtual void *calloc(int count, int size, AllocType type) = 0;
  virtual bool free(void *ptr) = 0;
  void abort() {
#ifdef ARDUINO
    // enless loop!
    while (1) delay(1000);
#else
    exit(-1);
#endif
  }
};
/**
 * @brief Allocator which just forwards the calls to the standard implementations of
 * malloc and free
 */
class LameHeapStandardAllocator : public LameHeapBase {
 public:
  void *calloc(int count, int size, AllocType type) {
    void *result = NULL;
    result = ::calloc(count, size);

    char mem_info[120] = {""};
    if (result != NULL) {
      LOG_LAME(LAMEInfo, "==> calloc(%d,%d) -> %p - %s", count, size, result,
               mem_info);
    } else {
      LOG_LAME(LAMEError, "==> calloc(%d,%d) -> %p - %s", count, size, result,
               mem_info);
      // assert(result!=NULL);  // -> generate
      abort();
    }

    return result;
  }

  bool free(void *ptr) {
    LOG_LAME(LAMEInfo, "==> free (%p)", ptr);
    ::free(ptr);
    return true;
  }
};

#ifdef ESP32

/**
 * @brief Allocator which uses the functionality of the ESP32. Any memory > psram_limit 
 * will be allocated in psram. Int32 bytes will be allocated with MALLOC_CAP_32BIT. 
 * Anything else will be allocated with MALLOC_CAP_8BIT!
 */
class LameESP32HeapAllocator : public LameHeapBase {
 public:
  LameESP32HeapAllocator(int psram = ESP_PSRAM_ENABLE_LIMIT) {
    psram_limit = psram;
  }
  void *calloc(int count, int size, enum AllocType type) {
    void *result = NULL;
    const char* method = "";
    // try to allocate from psram
    if ((psram_limit > 0) && (count * size > psram_limit)) {
      method = "ps_calloc";
      result = ps_calloc(count, size);  // use psram
    }

    if (size==4 && type==A_INT) {
      method = "heap_caps_calloc(32)";
      result = heap_caps_calloc(count, size, MALLOC_CAP_32BIT);  // use psram
    }


    if (result == NULL) {
      method = "heap_caps_calloc(8)";
      result = heap_caps_calloc(count, size, MALLOC_CAP_8BIT);
    }

    char mem_info[120] = {""};
    sprintf(mem_info,
            "- available MALLOC_CAP_8BIT: %d / MALLOC_CAP_32BIT: %d  / "
            "MALLOC_CAP_SPIRAM: %d",
            heap_caps_get_largest_free_block(MALLOC_CAP_8BIT),
            heap_caps_get_largest_free_block(MALLOC_CAP_32BIT),
            heap_caps_get_largest_free_block(MALLOC_CAP_SPIRAM));
    if (result != NULL) {
      LOG_LAME(LAMEInfo, "==> %s(%d,%d) -> %p - %s",method, count, size, result,
               mem_info);
    } else {
      LOG_LAME(LAMEError, "==> %s(%d,%d) -> %p - %s",method, count, size, result,
               mem_info);
      // assert(result!=NULL);  // -> generate
      abort();
    }

    return result;
  }

  bool free(void *ptr) {
    LOG_LAME(LAMEInfo, "==> free (%p)", ptr);
    ::free(ptr);
    return true;
  }

 protected:
  int psram_limit;
};

#endif

void set_lame_heap(LameHeapBase *heap);

#endif


void *lamex_calloc(int count, int size, int type);
void lamex_free(void *mem);
void lame_abort();
void memset32(void *data, int value, int bytes);

#ifdef __cplusplus
}
#endif
