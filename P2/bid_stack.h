/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: ***************************** LOGIN 1: **********
 * AUTHOR 2: ***************************** LOGIN 2: **********
 * GROUP: *.*
 * DATE: ** / ** / **
 */

#ifndef BID_STACK_H
#define BID_STACK_H

#include "types.h"

#ifndef STATIC_STACK_H
#define STATIC_STACK_H

#define SMAX 100
#define SNULL (-1)

typedef int tItemS;
typedef int tPosS;

typedef struct {

    tItemS data[SMAX];
    tPosS top;

} tStack;


void createEmtpyStack(tStack *stack);
void pop(tStack *stack);
void peek(tStack stack);
void push(tItemS d, tStack *stack);


#endif
#endif STATIC_STACK_H
