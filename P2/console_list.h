/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Samuel Mouriño Cernadas  LOGIN 1: samuel.mourino@udc.es
 * AUTHOR 2: Pedro Gómez Osorio LOGIN 2: pedro.gomez.osorio@udc.es
 * GROUP: 2.3
 * DATE: 01 / 04 / 2025
 */

#ifndef CONSOLE_LIST_H
#define CONSOLE_LIST_H

#include <stdbool.h>
#include "types.h"
#include "bid_stack.h"


// Definición de la estructura de un elemento de la lista
typedef struct {
    tUserId seller;
    tConsoleId consoleId;
    tConsoleBrand consoleBrand;
    tConsolePrice consolePrice;
    tBidCounter bidCounter;
    tStack bidStack; // Pila con las pujas recibidas
} tItemL;


// Definición del nodo de la lista
typedef struct tNode *tPosL;
struct tNode {
    tItemL item;
    tPosL next;
};

typedef tPosL tList;
#define LNULL NULL
typedef struct tNode *tPosL;


void createEmptyList(tList *L);
/*
 *  Objetivo: inicializar la lista
 *  Entradas: una lista
 *  Salida: lista inicializada
 */

bool isEmptyList(tList L);
/*
 *  Objetivo: comprobar si la lista está vacía
 *  Entradas: una lista
 *  Salida: true si la lista está vacía, false en caso contrario
 */

bool insertItem(tItemL d, tList *L);
/*
 *  Objetivo: añadir un elemento a la lista
 *  Entradas: - Item: elemento a añadir
 *            - List: lista donde añadir el elemento
 *  Salida: lista con el elemento añadido, true si se pudo realizar, false en caso contrario
 *  Precondición: la lista no está llena
 */

void deleteAtPosition(tPosL p, tList *L);
/*
 *  Objetivo: eliminar un elemento de la lista
 *  Entradas: - Position: posición del elemento a eliminar
 *            - List: lista donde se encuentra el elemento
 *  Salida: lista con el elemento eliminado
 *  Precondición: la lista no está vacía y la posición es válida
 */

tPosL findItem(tConsoleId id, tList L);
/*
 *  Objetivo: buscar un elemento en la lista
 *  Entradas: - Id: id del elemento a buscar
 *            - List: lista donde buscar el elemento
 *  Salida: posición del elemento encontrado, LNULL si no se encuentra
 *  Precondición: la lista no está vacía
 */

tItemL getItem(tPosL p, tList L);
/*
 *  Objetivo: obtener un elemento de la lista
 *  Entradas: - Position: posición del elemento a obtener
 *            - List: lista donde se encuentra el elemento
 *  Salida: elemento encontrado
 *  Precondición: la lista no está vacía y la posición es válida
 */

void updateItem(tItemL d, tPosL p, tList *L);
/*
 *  Objetivo: actualizar un elemento de la lista
 *  Entradas: - Item: elemento a actualizar
 *            - Position: posición del elemento a actualizar
 *            - List: lista donde se encuentra el elemento
 *  Salida: lista con el elemento actualizado
 *  Precondición: la lista no está vacía y la posición es válida
 */

tPosL first(tList L);
/*
 *  Objetivo: obtener la primera posición de la lista
 *  Entradas: una lista
 *  Salida: posición del primer elemento de la lista, LNULL si la lista está vacía
 */

tPosL last(tList L);
/*
 *  Objetivo: obtener la última posición de la lista
 *  Entradas: una lista
 *  Salida: posición del último elemento de la lista, LNULL si la lista está vacía
 */

tPosL next(tPosL p, tList L);
/*
 *  Objetivo: obtener la siguiente posición de la lista
 *  Entradas: - Position: posición del elemento actual
 *            - List: lista donde se encuentra el elemento
 *  Salida: posición del siguiente elemento, LNULL si no hay siguiente
 *  Precondición: la lista no está vacía y la posición es válida
 */

tPosL previous(tPosL p, tList L);
/*
 *  Objetivo: obtener la posición anterior de la lista
 *  Entradas: - Position: posición del elemento actual
 *            - List: lista donde se encuentra el elemento
 *  Salida: posición del elemento anterior, LNULL si no hay anterior
 *  Precondición: la lista no está vacía y la posición es válida
 */


#endif // PRO2_2025_P2_CONSOLE_LIST_H
