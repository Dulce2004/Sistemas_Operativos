#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {

    pid_t pid = fork();

    if (pid < 0) {
        perror("Error en fork");
        return 1;
    }

    if (pid == 0) {
        // PROCESO HIJO
        for (long i = 1; i <= 4000000; i++) {
            printf("%ld\n", i);
        }
    } 
    else {
        // PROCESO PADRE
        while (1) {
            // ciclo infinito
        }
    }

    return 0;
}
