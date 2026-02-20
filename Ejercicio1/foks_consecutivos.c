#include <stdio.h>
#include <unistd.h>

int main() {

    fork();
    fork();
    fork();
    fork();

    printf("Proceso PID: %d\n", getpid());

    return 0;
}