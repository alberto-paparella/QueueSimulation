//----- Preprocessor Directives ---------------------------------------------
#ifndef SERVITORE_H
#define SERVITORE_H

//----- Include files -------------------------------------------------------
#include "pacchetto.h"

//----- Typedefs ---------- -------------------------------------------------
typedef struct {
    Pacchetto pacchetto;
    int Occupato;           // Valore boolean settato a 1 se il servitore sta
                            // servendo un pacchetto e 0 altrimenti

    int tServizio;          // Indica fra quanti cicli il Servitore tornera' libero
} Servitore;

#endif // SERVITORE_H
