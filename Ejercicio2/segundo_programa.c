#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {

    pid_t p1, p2, p3;
    clock_t inicio, fin;
    double tiempo;

    inicio = clock();

    p1 = fork();

    if (p1 == 0) {

        p2 = fork();

        if (p2 == 0) {

            p3 = fork();

            if (p3 == 0) {
                // Bisnieto
                for (int i = 0; i < 1000000; i++);
            } else {
                // Nieto
                for (int i = 0; i < 1000000; i++);
                wait(NULL);
            }

        } else {
            // Hijo
            for (int i = 0; i < 1000000; i++);
            wait(NULL);
        }

    } else {
        // Padre
        wait(NULL);
        fin = clock();
        tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
        printf("Tiempo concurrente: %f segundos\n", tiempo);
    }

    return 0;
}
