#include "poisgen.h"

int poisson(double x) {
    int genVal;
    double u = 0.0;         // numero pseudo-casuale compreso fra 0.0 e 1.0
                            // generato da una distribuzione uniforme di valori
    u = (double)rand() / (double)RAND_MAX;
    genVal = (int) ((-log(1.0 - u) / (double)x) + 1.0);
    return genVal;
}
