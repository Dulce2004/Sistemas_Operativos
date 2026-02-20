#include <stdio.h>
#include <time.h>

int main() {

    clock_t inicio, fin;
    double tiempo;

    inicio = clock();

    for(int i = 0; i < 1000000; i++) {
        printf("%d\n", i);
    }

    for(int i = 0; i < 1000000; i++) {
        printf("%d\n", i);
    }

    for(int i = 0; i < 1000000; i++) {
        printf("%d\n", i);
    }

    fin = clock();

    tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;

    printf("Tiempo secuencial: %f segundos\n", tiempo);

    return 0;
}
