#include <sys/syscall.h>
#include <unistd.h>
#include <stdio.h>
#define __NR_mycall 470  // El número que registraste

int main() {
    long res = syscall(__NR_mycall, 50);
    printf("Resultado devuelto por kernel: %ld\n", res);
    return 0;
}