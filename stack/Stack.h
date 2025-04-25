/**
 * @file    Stack.h
 * @author  Tarık Eren Tosun
 * @date    18 Apr 2025
 * @brief   Stack implementation
 */
#ifndef STACK_H
#define STACK_H

#include <stddef.h>

/**
 * @brief               Stack struct which holds the relevant data
 */
typedef struct Stack {
    size_t top;         //Top pointer to denote the last element's position
    size_t size;        //The size of the stack
    void **elements;    //A double pointer which acts like an array to hold the stack values.
}Stack;

/**
 * @brief               Stack creation.
 * @param size          Size of the stack to be created
 * @return              A stack object
 */
Stack *StackCreate(size_t size);

/**
 * @brief               Push operation for the stack.
 * @param stack         Which stack to push to
 * @param item          The item to be pushed
 */
void StackPush(Stack *stack, void *item);

/**
 * @brief               Pop operation for the stack.
 * @param stack         Stack to pop from
 * @return              The popped item
 */
void *StackPop(Stack *stack);

/**
 * @brief               Returns the top of a given stack. If a heap allocated element was popped, it should be
 *                      freed by hand.
 * @param stack         Stack to view
 * @return              The top of the stack
 */
void *StackPeek(Stack *stack);

/**
 * @brief               Checks whether a given stack is empty.
 * @param stack         Stack to check
 * @return              1 for empty 0 for not
 */
int StackIsEmpty(Stack *stack);

/**
 * @brief               Checks whether a given stack is full.
 * @param stack         Stack to check
 * @return              1 for full 0 for not
 */
int StackIsFull(Stack *stack);

/**
 * @brief               Frees the stack and it's elements.
 * @param stack         Stack to delete
 */
void StackDelete(Stack *stack);

/**
 * @brief               Prints out the values in the stack.
 * @param stack         Stack to print out
 */
void StackDump(Stack *stack);

#endif //STACK_H
