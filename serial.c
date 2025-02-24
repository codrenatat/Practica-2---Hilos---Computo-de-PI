#include <stdio.h>
#include <math.h>
#include <sys/time.h>

double f(double x) {
    return sqrt(1 - x * x);
}

double calcular_pi_serial(long num_trapecios) {
    double h = 1.0 / num_trapecios;
    double suma = 0.0;

    for (long i = 0; i < num_trapecios; i++) {
        double x = (i + 0.5) * h; 
        suma += f(x);
    }

    return 4.0 * suma * h; 
}

int main() {
    struct timeval inicio, fin;
    long num_trapecios = 100000000; 

    gettimeofday(&inicio, NULL);
    double pi = calcular_pi_serial(num_trapecios);
    gettimeofday(&fin, NULL);

    double tiempo = (fin.tv_sec - inicio.tv_sec) + (fin.tv_usec - inicio.tv_usec) / 1000000.0;

    printf("Valor estimado de PI: %.10f\n", pi);
    printf("Tiempo de ejecución (serial): %.6f segundos\n", tiempo);

    return 0;
}


