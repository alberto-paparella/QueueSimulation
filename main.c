/*  Simulazione di un Sistema a Coda M/M/Y/Y
    Progetto svolto per il Corso di Reti di Telecomunicazioni
    Tenuto dal Professor Andrea Conti
    Corso di Laurea in Informatica, A.A. 2019-2020

    Gruppo 06 - Martina Tenani, Alberto Paparella   */

//----- Include files -------------------------------------------------------
#include "servitore.h"
#include "coda.h"
#include "poisgen.h"

//----- MACROS --------------------------------------------------------------
#define SEED 500
#define Y 4         // numero servitori
#define NRIP 100    // cicli
#define SEED 500    // Seme per la generazione di numeri pseudo-casuali
                    // e per la ripetibilita' dell'esperimento

//===== Main program ========================================================
int main(int argc, char* argv[]) {

    // Variabili
    int ii, t;              // Iteratori
    int k = 0;              // Numero pacchetti nel sistema
    int nextArrivo = 0;     // Fra quanto tempo arrivera' il prossimo pacchetto
    int sommaK = 0;         // Utile per exp
    double eK = 0.0;        // Utile per exp
    double lambda = 0.05;   // Tasso di nascita
    double mu = 0.025;      // Tasso di morte
    double lmbk, muk;       // Parametri istantanei di lambda e mu

    Pacchetto pkt;          // Il record di pacchetto
    Servitore servitori[Y]; // Array di servitori di dimensione Y (numero di servitori del sistema)
    Coda c1;                // La coda del sistema
    pkt.id = 0;             // Per come e' strutturato il simulatore
                            // il primo pkt ad entrare avra' id 1

    nuovaCoda(&c1);         // Init della coda
    srand(SEED);            // Imposto il seme dell'esperimento

    // Init dei Servitori
    for (ii = 0; ii < Y; ii++) {
        servitori[ii].pacchetto.id = 0;
        servitori[ii].Occupato = 0;
        servitori[ii].tServizio = 0;
    }


    /* Salvataggio risultati esperimento */
    FILE *fp;   // file su cui salvero' i risultati del mio esperimento
    fp = fopen("risultati.txt", "wt");
    if (fp == NULL) {
        printf("Errore apertura file\n");
        return(-1);
    }

    fprintf("NOME ESPERIMENTO ATTUALE\n");

    // eventuale cilcazione esterna per esperimenti al variare di parametri, come lambda
    for (ii = 0; ii < NRIP; ii++) {
        // esperimento
    }

    fclose(fp);

    return 0;
}
