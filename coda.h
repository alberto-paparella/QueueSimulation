//----- Preprocessor Directives ---------------------------------------------
#ifndef CODA_H
#define CODA_H

//----- Include files -------------------------------------------------------
#include <stdio.h>      // Needed for printf()
#include <malloc.h>     // Needed for malloc()

#include "pacchetto.h"

//----- Typedefs ---------- -------------------------------------------------
typedef struct nodo {
    Pacchetto pacchetto;
    struct nodo* next;  // Puntatore all'elemento successivo
} Nodo;

typedef Nodo* Coda;

//----- Function prototypes -------------------------------------------------
void nuovaCoda(Coda* pc);               // inizializzazione coda

void enqueue(Coda* pc, Pacchetto p);    // Inserimento in coda

void dequeue(Coda* pc);                 // Eliminazione elemento in testa alla coda

void getHead(Coda c);                   // Stampa il prossimo pacchetto che verra' servito
                                        // il pacchetto in testa alla coda ("head")

void getTail(Coda c);                   // Stampa l'ultimo elemento della coda, la "tail"

int getStato(Coda c);                   // Conta il numero degli elementi nella coda

void stampaCoda(Coda c);                // Stampa la coda dalla testa alla coda (operazione di debug)
                                        // dal prossimo pacchetto che sta per essere servito fino
                                        // all'ultimo che verra' servito

#endif // CODA_H
