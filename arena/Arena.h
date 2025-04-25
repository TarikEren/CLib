/**
 * @file    Arena.h
 * @author  Tarık Eren Tosun
 * @date    9 Apr 2025
 * @brief   Arena allocator implementation in C
 */

#ifndef ARENA_H
#define ARENA_H


/**
 * @defgroup ALIGNMENT_OPERATIONS
 * @{
 * @brief Operations for handling the bit alignment issues
 */
#define BIT_ALIGNMENT_8(n)    (n+7) & ~7
#define BIT_ALIGNMENT_16(n)   (n+15) & ~15
#define BIT_ALIGNMENT_64(n)   (n+63) & ~63
/**
 * @}
 */

/**
 *
 * @brief           Struct for the arena allocator
 */
typedef struct arena {
    char *base;
    size_t size, offset;
}Arena;

/**
 * @brief           Arena creation using the provided size
 * @param size      Size of the arena to be created
 * @return          Heap allocated arena object
 */
Arena *CreateArena(size_t size);

/**
 * @brief           Allocation to a given arena object
 * @param arena     Arena to be allocated to
 * @param n         Size of bytes to be allocated
 * @return          The starting address of the allocated memory or NULL on failure
 */
void *ArenaAllocate(Arena *arena, size_t n);

/**
 * @brief           Clears a given arena
 * @param arena     Arena to be flushed
 */
void FlushArena(Arena *arena);

/**
 * @brief           Frees a given arena and it's contents
 * @param arena     Arena to be freed
 */
void DestroyArena(Arena *arena);


#endif