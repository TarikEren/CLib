/**
 * @file    Stack.c
 * @author  Tarık Eren Tosun
 * @date    18 Apr 2025
 * @brief   Stack implementation
 */

#include <stdio.h>
#include <stdlib.h>

#include "Stack.h"
#include "../log/Log.h"


Stack *StackCreate(size_t size) {
    //Heap allocation for the stack object
    Stack *new_stack = malloc(sizeof(Stack));
    //Set the stack size as the provided size value
    new_stack->size = size;
    //Initialise the top pointer as -1
    new_stack->top = -1;
    //Heap allocate the stack elements array (Double pointer)
    new_stack->elements = malloc(sizeof(void*) * size);
    //Return the stack object
    return new_stack;
}

void StackPush(Stack *stack, void *item) {
    //If the stack is full
    if (StackIsFull(stack)) {
        //Log message out to the terminal
        char message_buffer[100];
        sprintf(message_buffer, "Cannot push to stack at address %p, stack is full\n", stack);
        Log(ERROR, message_buffer);
        return;
    }
    //Otherwise increment the top pointer by one
    stack->top++;
    //Assign the item to the top of the stack
    stack->elements[stack->top] = item;
}

void *StackPop(Stack *stack) {
    //If the stack is empty
    if (StackIsEmpty(stack)) {
        //Log message out to the terminal
        char message_buffer[100];
        sprintf(message_buffer, "Cannot pop from stack at address %p, stack is empty\n", stack);
        Log(ERROR, message_buffer);
        return NULL;
    }
    //Otherwise, decrease the top pointer by one
    stack->top -= 1;
    //Return the element that was pointed by the top pointer prior to the decrementation
    return stack->elements[stack->top + 1];
}

void *StackPeek(Stack *stack) {
    //If the stack is empty
    if (StackIsEmpty(stack)) {
        //Log message out to the terminal
        char message_buffer[100];
        sprintf(message_buffer, "Cannot peek from stack at address %p, stack is empty\n", stack);
        Log(ERROR, message_buffer);
        return NULL;
    }
    //Otherwise, return the top element
    return stack->elements[stack->top];
}

int StackIsEmpty(Stack *stack) {
    //If the top pointer value is -1
    if (stack->top == -1)
        //Return 1
        return 1;
    //Otherwise, return 0
    return 0;
}

int StackIsFull(Stack *stack) {
    //If the top pointer is pointing to size - 1
    if (stack->top == stack->size-1)
        //Return 1
        return 1;
    //Otherwise, return 0
    return 0;
}

void StackDelete(Stack *stack) {
    //While the stack is not empty
    while (!StackIsEmpty(stack)) {
        //Pop from stack and free the popped element
        free(StackPop(stack));
    }
    //Free the elements pointer
    free(stack->elements);
    //Set the pointer to NULL for handling dangling pointers
    stack->elements = NULL;
    //Set the stack size to 0
    stack->size = 0;
    //Set the stack top to 0
    stack->top = 0;
    //Free the stack object
    free(stack);
    //Set the stack object to NULL for handling dangling pointers
    stack = NULL;
}

void StackDump(Stack *stack) {
    //If the stack is empty
    if (StackIsEmpty(stack)) {
        //Log message out to the terminal
        char message_buffer[100];
        sprintf(message_buffer, "Cannot dump stack at address %p, stack is empty\n", stack);
        Log(ERROR, message_buffer);
        return;
    }
    //Otherwise, print out the stack
    printf("===== Stack Start =====\n");
    for (size_t i = stack->top; i == 0; i++) {
        printf("%p\n", stack->elements[i]);
    }
    printf("===== Stack End =====\n");
}