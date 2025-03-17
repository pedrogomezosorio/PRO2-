/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Samuel Mouriño Cernadas LOGIN 1: samuel.mourino@udc.es
 * AUTHOR 2: Pedro Gomez Osorio LOGIN 2: pedro.gomez.osorio@udc.es
 * GROUP: 2.3
 * DATE: 14 / 03 / 2025
 */


#include "dynamic_list.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void createEmptyList(tList *L) {
    *L = LNULL;
}

bool createNode(tPosL *p) {
    *p = malloc(sizeof(struct tNode));
    return *p != LNULL;
}

bool insertItem(tItemL d, tPosL p, tList *L) {
    tPosL q, r;

    if (!createNode(&q))
        return false;
    
    q->data = d;
    q->next = LNULL;
    if (*L == LNULL) {
        *L = q;
    } else if (p == LNULL) {
        for (r = *L; r->next != LNULL; r = r->next);
        r->next = q;
    } else if (p == *L) {
        q->next = p;
        *L = q;
    } else {
        q->data = p->data;
        p->data = d;
        q->next = p->next;
        p->next = q;
    }
    return true;
}

void updateItem(tItemL d, tPosL p, tList *L) {
    p->data = d;
}

void deleteAtPosition(tPosL p, tList *L) {
    tPosL q;

    if (p == *L) {
        *L = p->next;
    } else if (p->next == LNULL) {
        for (q = *L; q->next != p; q = q->next);
        q->next = LNULL;
    } else {
        q = p->next;
        p->data = q->data;
        p->next = q->next;
        p = q;
    }
    free(p);
}

tPosL findItem(tConsoleId n, tList L) {
    tPosL p;
    for (p = L; (p != LNULL) && (strcmp(p->data.consoleId, n) != 0); p = p->next);
    return p;
}

bool isEmptyList(tList L) {
    return L == LNULL;
}

tItemL getItem(tPosL p, tList L) {
    return p->data;
}

tPosL first(tList L) {
    return L;
}

tPosL last(tList L) {
    tPosL p;
    for (p = L; p->next != LNULL; p = p->next);
    return p;
}

tPosL next(tPosL p, tList L) {
    return p->next;
}

tPosL previous(tPosL p, tList L) {
    tPosL q;

    if (p == L) {
        return LNULL;
    } else {
        for (q = L; q->next != p; q = q->next);
        return q;
    }
}
