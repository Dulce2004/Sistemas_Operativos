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
        printf("Soy el proceso hijo. PID: %d\n", getpid());
    } 
    else {
        // PROCESO PADRE
        printf("Soy el proceso padre. PID: %d\n", getpid());

        while (1) {
            // ciclo infinito
        }
    }

    return 0;
}
