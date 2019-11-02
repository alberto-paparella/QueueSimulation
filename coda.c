//----- Include files -------------------------------------------------------
#include "coda.h"

// Inizializzazione coda
void nuovaCoda(Coda* pc) {
    *pc = NULL;
}

/* Inserimento in coda (sfrutta funzioni di ricerca e di inserimento in testa
                        nascoste al cliente) */
void insTesta(Coda* pc, Pacchetto pacchetto) {
    Nodo* aux = (Nodo*)malloc(sizeof(Nodo));
    aux->pacchetto = pacchetto;
    aux->next = *pc;
    *pc = aux;
}

Coda* ricerca(Coda* pc, Pacchetto p) {
    while(*pc)
        pc = &(*pc)->next;
    return pc;              // per il mio utilizzo, *pc == NULL sempre
}

void enqueue(Coda* pc, Pacchetto p) {
    pc = ricerca(pc, p);
    insTesta(pc, p);
}

// Eliminazione in testa
void dequeue(Coda* pc) {
    Nodo* aux = *pc;
    *pc = (*pc)->next;
    free(aux);
}

void getHead(Coda c) {
    if(c)   // Eccezione: coda vuota
        printf("Head: %d\n", c->pacchetto.id);
}

void getTail(Coda c) {
    while(c && c->next)
        c = c->next;
    if(c)   // Eccezione: coda vuota
        printf("Tail: %d\n", c->pacchetto.id);
}

int getStato(Coda c) {
    int i = 0;
    while(c) {
        i++;
        c = c->next;
    }
    return i;
}

void stampaCoda(Coda c) {
    while(c) {
        printf("%d ", c->pacchetto.id);
        c = c->next;
    }
    printf("\n");
}

