/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: ***************************** LOGIN 1: **********
 * AUTHOR 2: ***************************** LOGIN 2: **********
 * GROUP: *.*
 * DATE: ** / ** / **
 */

#include <stdbool.h>
#include "bid_stack.h"

void createEmptyStack(tStack *stack)
{
    stack->top = SNULL;
}


void pop(tStack *stack)
{
    stack->top--;
}


void peek(tStack stack)
{
    return stack.data[stack.top];
}


bool push(tItemS d, tStack *stack) {
    if (stack->top == MAX - 1) {    // pila llena

        return false;

    } else {

        stack->top++;

        stack->data[stack->top] = d;

        return true;

    }

}


void isEmptyStack(tStack stack)
{
    return (stack.top == SNULL);
}



