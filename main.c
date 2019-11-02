/*  Simulazione di un Sistema a Coda M/M/Y/Y
    Progetto svolto per il Corso di Reti di Telecomunicazioni
    Tenuto dal Professor Andrea Conti
    Corso di Laurea in Informatica, A.A. 2019-2020

    Gruppo 06 - Martina Tenani, Alberto Paparella   */

//----- Include files --
#include "coda.h"
#include "poisgen.h"

#define SEED 500

int main(int argc, char* argv[]) {

    double lambda = 0.05;
    double mu = 0.025;
    int sum = 0;
    int num;

    srand(SEED);

    int ii = 0;
    for (ii = 0; ii < 5000; ii++) {
        num = poisson(lambda);
        printf("%d ", num);
        sum += num;
    }
    printf("\n%d\n", sum / 5000);

    printf("\n\n");

    sum = 0;
    for (ii = 0; ii < 5000; ii++) {
        num = poisson(mu);
        printf("%d ", num);
        sum += num;
    }
    printf("\n%d\n", sum/5000);

    return 0;
}
