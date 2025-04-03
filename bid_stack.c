/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Samuel Mouriño Cernadas LOGIN 1: samuel.mourino@udc.es
 * AUTHOR 2: Pedro Gómez Osorio LOGIN 2: pedro.gomez.osorio@udc.es
 * GROUP: 2.3
 * DATE: 01 / 04 / 2025
 */

#include "bid_stack.h"

void createEmptyStack(tStack *S) {
    S->top = SNULL;
}

bool push(tItemS item, tStack *S) {
    if (S->top == MAX_BIDS - 1) {
        return false;
    }else {
        S->top++;
        S->items[S->top] = item;
        return true;
    }
}

void pop(tStack *S) {
    S->top--;
}

tItemS peek(tStack S) {
    return S.items[S.top];
}

bool isEmptyStack(tStack S) {
    return S.top == -1;
}

