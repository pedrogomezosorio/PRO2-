/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Samuel Mouriño Cernadas LOGIN 1: samuel.mourino@udc.es
 * AUTHOR 2: Pedro Gómez Osorio LOGIN 2: **********
 * GROUP: 2.3
 * DATE: 01 / 04 / 2025
 */

#ifndef BID_STACK_H
#define BID_STACK_H

#include "types.h"
#include "console_list.h"

#define MAX_BIDS 25
#define SNULL -1

typedef struct {
    tUserId bidder;       // Usuario que realiza la puja
    tConsolePrice amount; // Monto de la puja
} tItemS;

typedef struct tStack {
    tItemS items[MAX_BIDS]; // Array de pujas
    int top;                // Índice del último elemento
} tStack;

void createEmptyStack(tStack *S);
/*
 *  Objetivo: inicializar la pila
 *  Entradas: una pila
 *  Salida: pila inicializada
 */
bool isEmptyStack(tStack S);
/*
 *  Objetivo: comprobar si la pila está vacía
 *  Entradas: una pila
 *  Salida: true si la pila está vacía, false en caso contrario
 */
bool push(tItemS item, tStack *S);
/*
 *  Objetivo: añadir un elemento a la pila
 *  Entradas: - Item: elemento a añadir
 *            - Stack: pila donde añadir el elemento
 *  Salida: pila con el elemento añadido, true si se pudo realizar, false en caso contrario
 *  Precondición: la pila no está llena
 */
void pop(tStack *S);
/*
 *  Objetivo: eliminar el último elemento de la pila
 *  Entradas: una pila
 *  Salida: pila con el último elemento eliminado
 *  Precondición: la pila no está vacía
 */
tItemS peek(tStack S);
/*
 *  Objetivo: obtener el último elemento de la pila
 *  Entradas: una pila
 *  Salida: último elemento de la pila
 *  Precondición: la pila no está vacía
 */
#endif
