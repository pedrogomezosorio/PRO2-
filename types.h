#ifndef PRO2_2025_P2_TYPES_H
#define PRO2_2025_P2_TYPES_H


#define NAME_LENGTH_LIMIT 10

// Identificadores
typedef char tUserId[NAME_LENGTH_LIMIT];
typedef char tConsoleId[NAME_LENGTH_LIMIT];

// Marca de la consola
typedef enum {nintendo, sega} tConsoleBrand;

// Precio de la consola
typedef float tConsolePrice;

// Contador de pujas
typedef int tBidCounter;

typedef struct tStack tStack;

// Estructura de una consola
typedef struct {
    tConsoleId id;
    tConsoleBrand brand;
    tConsolePrice price;
    tBidCounter bidCounter;
    tStack bidStack;
} tConsole; // Tipo de dato para la lista de consolas

// Estructura de una puja
typedef struct {
    tUserId userId;
    tConsoleId consoleId;
    tConsolePrice bid;
} tBid; // Tipo de dato para la lista de pujas

#endif //PRO2_2025_P2_TYPES_H
