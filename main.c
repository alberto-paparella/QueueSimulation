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
#define Y 4         // numero servitori
#define PKTGEN 50  // pacchetti generati a ogni sperimentazione
#define SEED 5647   // Seme per la generazione di numeri pseudo-casuali
                    // e per la ripetibilita' dell'esperimento

//===== Main program ========================================================
int main(int argc, char* argv[]) {

    // Variabili
    int ii, t;              // Iteratori
    int kGen = PKTGEN;        // Pacchetti che verranno generati nel corso della simulazione
    int k = 0;              // Numero pacchetti nel sistema
    int kRif = 0;           // Pacchetti rifiutati dal sistema
    int nextArrivo = 0;     // Fra quanto tempo arrivera' il prossimo pacchetto
    int sommaK = 0;         // Utile per exp
    int sommaKcoda = 0;
    double eK = 0.0;        // Utile per exp
    double eKq = 0.0;
    double lambda;          // Tasso di nascita
    double mu;              // Tasso di morte
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

    fprintf(fp, "Andamento di E{K} in funzione di A\nA\t\tE{K}\n");

    //lambda = 0.1; // Per il DEBUG commentando il ciclo
    mu = 0.01;
    for (lambda = 0.001; lambda < 0.2; lambda += 0.001) {

        sommaK = 0;
        sommaKcoda = 0;
        kGen = PKTGEN;
        kRif = 0;
        t = 0;  // per quanti cicli va la sim
        while (kGen) {

                /* Decremento di tutti i contatori diversi da 0 */
                if (nextArrivo > 0)
                    nextArrivo--;
                for (ii = 0; ii < Y; ii++) {
                    if (servitori[ii].tServizio) {
                        servitori[ii].tServizio--;
                        if (servitori[ii].tServizio == 0) {
                            servitori[ii].Occupato = 0;
                            k--;
                        }
                    }
                }

                // Stampa a video l'istante attuale (utile per il DEBUG)
                // printf("PKT nel sistema: %d\tProssimo PKT: %d\nStato Servitori:\n", k, nextArrivo);
                // for (ii = 0; ii < Y; ii++)
                //   printf("Servitore: %d\tSta servendo: %d\tOccupato: %d\tLibero fra: %d\nCoda:\n", ii+1, servitori[ii].pacchetto.id, servitori[ii].Occupato, servitori[ii].tServizio);
                // stampaCoda(c1);
                // printf("PKT in coda: %d\n", getStato(c1));
                // printf("PKT scartati dall'inizio della simulazione: %d\n, kRif);

                /* Gestione parametro lambda */
                if (k < Y)
                    lmbk = lambda;
                else
                    lmbk = 0;   // se lmbk e' uguale a 0, significa che non mi aspetto arrivi
                                // in quanto non posso avere piu' di k pacchetti nel sistema

                /* Gestione arrivi */
                if (nextArrivo == 0 && lmbk) {
                    kGen--;
                    k++;

                    pkt.id++;
                    enqueue(&c1,pkt);
                    nextArrivo = poisson(lmbk);

                    // SPOILER: quanto segue per il mio Sistema avverra' SEMPRE, vale a dire la coda sara' sempre vuota
                    // Controllo se ho un servitore disponibile, in caso affermativo faccio la dequeue
                    // e metto il pacchetto in quel servitore generando il tempo che impieghera' ad essere servito
                    ii = 0;
                    while (servitori[ii].Occupato && ii < Y - 1)
                        ii++;
                    if (servitori[ii].Occupato == 0) {
                        servitori[ii].pacchetto.id = c1->pacchetto.id;  // Copio l'indirizzo del pacchetto in testa alla coda
                                                                        // nel servitore; S ora sta servendo quel pkt
                        servitori[ii].Occupato = 1;
                        muk = k * mu;   // nb: muk e' a livello di sistema, non la uso nella simulazione
                        servitori[ii].tServizio = poisson(mu);
                        dequeue(&c1);    // ATTENZIONE: in realta' prima viene effettuata la dequeue e poi il pacchetto
                                        // entra nel servitore, ovviamente. Cio' e' invertito per semplificare
                                        // l'implementazione della simulazione
                    }

                }

                // Se un pacchetto e' stato scartato, genera tempo prossimo arrivo
                if (nextArrivo == 0) {
                    nextArrivo = poisson(lambda);
                    kGen--;
                    kRif++;
                }

                sommaK += k;
                sommaKcoda += getStato(c1);
                t++;

        }

        eK = (double)sommaK / (double)t;
        eKq = (double)sommaKcoda / (double)t;
        fprintf(fp, "%f\t%f\n", lambda/mu, eK);    // stampo i valori istantanei di A e E{K}
        printf("A: %f\tE{K}: %f\tE{Kq}: %f\tPKT scartati: %d\n", lambda/mu, eK, eKq, kRif);
    }

    fclose(fp);

    return 0;
}
