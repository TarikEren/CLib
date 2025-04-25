#include <stdio.h>
#include <stdlib.h>

#include "Arena.h"
#include "../log/Log.h"

Arena *CreateArena(const size_t size) {
    //Heap allocate the arena object
    Arena *new_arena = malloc(sizeof(Arena));

    //Allocate size amount of bytes and set the base of the arena as the arena's start address
    new_arena->base = malloc(size);

    //Set the arena's size as the provided size value
    new_arena->size = size;

    //Set the offset value as 0 for the arena has just been initialised.
    new_arena->offset = 0;

    //Create the message buffer
    char message_buffer[100];

    //Create formatted message string
    sprintf(message_buffer,"Arena with size %lu created at address %p\n", size, new_arena->base);

    //Log onto the console
    Log(INFO, message_buffer);

    //Return the arena.
    return new_arena;
}

void *ArenaAllocate(Arena *arena, const size_t n) {
    //Padding operation for establishing better control over the arena and getting rid of undefined behaviour
    const size_t aligned = BIT_ALIGNMENT_8(n);

    //If the existing offset and the result of the alignment is greater than the size, return NULL
    //i.e. if an overflow were to happen return NULL
    if (arena->offset + aligned > arena->size) {
        char message_buffer[100];
        sprintf(message_buffer,
            "Arena overflow detected. Last offset: %lu, assignee size: %lu, size of arena: %lu\n",
            arena->offset,
            n,
            arena->size);
        Log(ERROR, message_buffer);
        return NULL;
    }

    //Set the pointer to be returned as the head of the nearest free memory block
    void *return_pointer = arena->base + arena->offset;

    //Increase the offset of the arena as the aligned value
    arena->offset += aligned;

    //Setup message buffer
    char message_buffer[100];

    //Write formatted string
    snprintf(
        message_buffer, sizeof message_buffer,
        "Arena at %p allocated %zu bytes to %p (requested %zu, padded to %zu)\n",
        arena,
        aligned,
        return_pointer,
        n,
        aligned
    );
    //Log the message
    Log(INFO, message_buffer);

    //Return the pointer pointing to the free memory
    return return_pointer;
}

void FlushArena(Arena *arena) {
    arena->offset = 0;
}

void DestroyArena(Arena *arena) {
    //Create the message buffer
    char message_buffer[100];

    //Create formatted string
    sprintf(message_buffer,"Debug: Destroying arena at address %p\n", arena->base);

    //Log onto the console
    Log(INFO, message_buffer);

    //Free the arena base and the arena objects
    free(arena->base);
    free(arena);
}