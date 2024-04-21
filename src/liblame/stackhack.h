#pragma once

#ifdef __cplusplus
extern "C" {
#endif

void stackhack_setup(int size);
void stackhack_end();
void* stackhack_alloc(int size);
void stackhack_free(void* ptr);

#ifdef __cplusplus
}
#endif
