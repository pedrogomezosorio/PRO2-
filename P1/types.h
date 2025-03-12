/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Samuel Mouriño Cernadas LOGIN 1: samuel.mourino@udc.es
 * AUTHOR 2: Pedro Gomez Osorio LOGIN 2: pedro.gomez.osorio@udc.es
 * GROUP: 2.3
 * DATE: 06/03/2025
*/

#ifndef PRO2_2024_P1_TYPES_H
#define PRO2_2024_P1_TYPES_H

#define NAME_LENGTH_LIMIT 10

typedef char tUserId[NAME_LENGTH_LIMIT];
typedef char tConsoleId[NAME_LENGTH_LIMIT];
typedef enum {nintendo, sega} tConsoleBrand;
typedef float tConsolePrice;
typedef int tBidCounter;

typedef struct tItemL {
    tUserId seller;
    tConsoleId consoleId;
    tConsoleBrand consoleBrand;
    tConsolePrice consolePrice;
    tBidCounter bidCounter;
} tItemL;


#endif

