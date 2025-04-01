/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Samuel Mouriño Cernadas LOGIN 1: samuel.mourino@udc.es
 * AUTHOR 2: Pedro Gómez Osorio LOGIN 2: **********
 * GROUP: *.*
 * DATE: ** / ** / **
 */

#include <stdbool.h>
#include "bid_stack.h"

#include "bid_stack.h"

// Crea una pila vacía
void createEmptyStack(tStack *S) {
    S->top = SNULL;  // Inicializamos la pila como vacía
}

// Verifica si la pila está vacía
bool isEmptyStack(tStack S) {
    return S.top == -1;
}

// Inserta una puja en la cima de la pila
bool push(tItemS item, tStack *S) {
    if (S->top == MAX_BIDS - 1) {
        return false; // La pila está llena, no se puede apilar más elementos
    }else {
        S->top++;              // Mover la cima al siguiente índice
        S->items[S->top] = item; // Insertar la puja
        return true;
    }
}

// Elimina la puja en la cima de la pila
void pop(tStack *S) {
    if (!isEmptyStack(*S)) {
        S->top--; // Mover la cima hacia abajo si la pila no está vacía
    }
}
// Devuelve la puja en la cima sin eliminarla
tItemS peek(tStack S) {
    return S.items[S.top]; // Devolvemos el elemento en la cima
}

