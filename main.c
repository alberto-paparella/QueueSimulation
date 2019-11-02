/*  Simulazione di un Sistema a Coda M/M/Y/Y
    Progetto svolto per il Corso di Reti di Telecomunicazioni
    Tenuto dal Professor Andrea Conti
    Corso di Laurea in Informatica, A.A. 2019-2020

    Gruppo 06 - Martina Tenani, Alberto Paparella   */

//----- Include files --
#include "coda.h"
#include "poisgen.h"

int main(int argc, char* argv[]) {

    double lambda = 0.001;
    double mu = 0.095;

    int ii = 0;
    for (ii = 0; ii < 50; ii++)
        printf("%d ", poisson(lambda));

    printf("\n\n");

    for (ii = 0; ii < 50; ii++)
        printf("%d ", poisson(mu));

    return 0;
}
