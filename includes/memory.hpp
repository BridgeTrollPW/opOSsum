#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <stddef.h>
#include <stdint.h>

typedef struct free_block
{
    size_t size;
    struct free_block *next;
} free_block;

static uintptr_t current_break; // Some global variable for your application.
                         // This would probably be properly tracked by the OS for the process

static free_block free_block_list_head = {0, 0};
static const size_t overhead = sizeof(size_t);
static const size_t align_to = 16;

void *sbrk(intptr_t incr);
void *malloc(size_t size);
void free(void *ptr);



#endif