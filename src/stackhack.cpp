#include "liblame/config.h"
#include "liblame/stackhack.h"
#include "liblame/log.h"
#include "assert.h"
#include "stack"
#include "stdint.h"
#include "string.h"

#if USE_STACK_HACK

/**
 * Stack Hack: We move some big variables to our custom stack
 */
class VariableStack {
 public:
  void setup(int size) { 
    current_data = start_data = new uint8_t[size]; 
    end_data = start_data + size;
    assert(current_data != nullptr);
  }

  void end() {
    delete[] start_data;
    start_data = end_data = current_data = nullptr;
  }

  void* allocate(int size) {
    void* result = current_data;
    current_data += size;
    if (current_data >= end_data) {
      // increase STACKHACK_SIZE
      lame_msgf(NULL,"stack-size: %d / requested %d", current_data - start_data, size);
      assert(false);
      return nullptr;
    }
    variable_stack.push(size);
    memset(result, 0, size);
    return result;
  }

  void free(void* ptr) {
    int len = variable_stack.top();
    variable_stack.pop();
    current_data -= len;
  }

 protected:
  std::stack<size_t> variable_stack;
  uint8_t* start_data;
  uint8_t* end_data;
  uint8_t* current_data;
};

VariableStack variable_stack;

void stackhack_setup(int size) { variable_stack.setup(size); }
void stackhack_end() { variable_stack.end(); }
void* stackhack_alloc(int size) { return variable_stack.allocate(size); }
void stackhack_free(void* ptr) { return variable_stack.free(ptr); }

#endif