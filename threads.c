#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <sys/time.h>

#define NUM_HILOS 4 

typedef struct {
    long inicio, fin;
    double h;
    double suma;
} ThreadData;

double f(double x) {
    return sqrt(1 - x * x);
}

void* calcular_parcial(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    double h = data->h;
    double suma = 0.0;

    for (long i = data->inicio; i < data->fin; i++) {
        double x = (i + 0.5) * h;
        suma += f(x);
    }

    data->suma = suma;
    return NULL;
}

double calcular_pi_threads(long num_trapecios, int num_hilos) {
    pthread_t hilos[num_hilos];
    ThreadData datos[num_hilos];
    double h = 1.0 / num_trapecios;
    long tramo = num_trapecios / num_hilos;
    double suma_total = 0.0;

    for (int i = 0; i < num_hilos; i++) {
        datos[i].inicio = i * tramo;
        datos[i].fin = (i == num_hilos - 1) ? num_trapecios : (i + 1) * tramo;
        datos[i].h = h;
        datos[i].suma = 0.0;
        pthread_create(&hilos[i], NULL, calcular_parcial, &datos[i]);
    }

    for (int i = 0; i < num_hilos; i++) {
        pthread_join(hilos[i], NULL);
        suma_total += datos[i].suma;
    }

    return 4.0 * suma_total * h;
}

int main() {
    struct timeval inicio, fin;
    long num_trapecios = 100000000; 

    gettimeofday(&inicio, NULL);
    double pi = calcular_pi_threads(num_trapecios, NUM_HILOS);
    gettimeofday(&fin, NULL);

    double tiempo = (fin.tv_sec - inicio.tv_sec) + (fin.tv_usec - inicio.tv_usec) / 1000000.0;

    printf("Valor estimado de PI: %.10f\n", pi);
    printf("Tiempo de ejecución (paralelo): %.6f segundos\n", tiempo);

    return 0;
}
