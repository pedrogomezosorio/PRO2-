/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: ***************************** LOGIN 1: **********
 * AUTHOR 2: ***************************** LOGIN 2: **********
 * GROUP: *.*
 * DATE: ** / ** / **
 */

#ifndef CONSOLE_LIST_H
#define CONSOLE_LIST_H

#include "types.h"
#include "bid_stack.h"

#include <stdbool.h>
#define LNULL (-1)
#define MAX 25

typedef int tPosL;
typedef struct {
    tItemL data[MAX];
    tPosL lastPos;
} tList;

// en todas las funciones, excepto createEmptyList, que la lista esté inicializada es una precondición

void createEmptyList(tList* L);
/*
 *  Objetivo: crear una lista vacía e inicializarla
 *  Salida: una lista vacía
*/
bool insertItem(tItemL d, tPosL p, tList *L);
/*
 *  Objetivo: - Posición NULL -> añade el elemento al final de la lista
 *            - Otra posición -> el elemento queda insertado antes del que ocupa la posición indicada
 *  Entradas: - Item: elemento a insertar
 *            - Position: posición donde realizar la inserción
 *            - List: lista donde insertaremos el elemento
 *  Salida: lista con la inserción, true si se pudo realizar, false en caso contrario
 *  Precondición: Position es una posición válida o NULL
 *  Postcondición: Las posiciones de los elementos existentes antes de la inserción pudieron haber variado
 */
void updateItem(tItemL d, tPosL p, tList *L);
/*
 *  Objetivo: modificar el contenido de un elemento de la lista
 *  Entradas: - Item -> nuevo contenido a asignar al elemento en Position
 *            - Position -> posición del elemento que queremos modificar
 *            - List -> lista a modificar
 *  Salida: lista con el elemento modificado
 *  Precondición: Position es una posición válida de la lista
 */
void deleteAtPosition(tPosL p, tList *L);
/*
 *  Objetivo: eliminar de la lista un elemento en una posición
 *  Entradas: - Position -> posición del elemento a eliminar
 *            - List -> lista a modificar
 *  Salida: List sin el elemento a eliminar
 *  Precondición: Position es una posición válida
 *  Postcondición: las posiciones de los elementos de la lista pudieron haber variado
 */
tPosL findItem(tConsoleId n, tList L);
/*
 *  Objetivo: buscar la posición de cierto elemento
 *  Entradas: - Item -> elemento a buscar
 *            - List -> lista donde realizar la búsqueda
 *  Salida: posición del elemento encontrado o LNULL si no se encuentra
 */
bool isEmptyList(tList L);
/*
 *  Objetivo: determinar si la lista está vacía
 *  Entrada: lista a comprobar
 *  Salida: true si la lista está vacía, false si no lo está
 */
tItemL getItem(tPosL p, tList L);
/*
 *  Objetivo: recuperar el contenido de un elemento de la lista
 *  Entradas: - Position -> posición del elemento buscado
 *            - List -> lista donde realizar la búsqueda
 *  Salida: contenido del elemento en Position
 *  Precondición: Position es una posición válida de la lista
 */
tPosL first(tList L);
/*
 *  Objetivo: devolver la posición del primer elemento de la lista
 *  Entrada: lista donde buscarlo
 *  Salida: posición del primer elemento
 *  Precondición: la lista no está vacía
 */
tPosL last(tList L);
/*
 *  Objetivo: devolver la posición del último elemento de la lista
 *  Entrada: lista donde buscarlo
 *  Salida: posición del último elemento
 *  Precondición: la lista no está vacía
 */
tPosL previous(tPosL p, tList L);
/*
 *  Objetivo: devolver la posición del elemento anterior al dado
 *  Entradas: - Position -> posición del elemento dado
 *            - List -> lista donde buscarlo
 *  Salida: posición del elemento anterior o LNULL si el dado es el primero
 *  Precondición: Position es una posición válida de la lista
 */
tPosL next(tPosL p, tList L);
/*
 *  Objetivo: devolver la posición del elemento siguiente al dado
 *  Entradas: - Position -> posición del elemento dado
 *            - List -> lista donde buscarlo
 *  Salida: posición del elemento siguiente o LNULL si el dado es el último
 *  Precondición: Position es una posición válida de la lista
 */


#endif
