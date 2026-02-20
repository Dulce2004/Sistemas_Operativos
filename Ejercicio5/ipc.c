#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>

#define SHM_NAME "/mi_memoria"
#define SIZE 100

int main(int argc, char *argv[]) {

    if (argc != 3) {
        fprintf(stderr, "Uso: %s <n> <x>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int n = atoi(argv[1]);
    char x = argv[2][0];

    if (n <= 0) {
        fprintf(stderr, "n debe ser mayor que 0\n");
        exit(EXIT_FAILURE);
    }

    int fd;
    int creado = 0;

    /* Intentar crear memoria compartida */
    fd = shm_open(SHM_NAME, O_CREAT | O_EXCL | O_RDWR, 0666);

    if (fd >= 0) {
        creado = 1;
        printf("Memoria creada por esta instancia.\n");

        if (ftruncate(fd, SIZE) == -1) {
            perror("ftruncate");
            exit(EXIT_FAILURE);
        }
    }
    else {
        if (errno == EEXIST) {
            printf("Memoria ya existe, abriendo...\n");
            fd = shm_open(SHM_NAME, O_RDWR, 0666);
            if (fd == -1) {
                perror("shm_open existente");
                exit(EXIT_FAILURE);
            }
        } else {
            perror("shm_open");
            exit(EXIT_FAILURE);
        }
    }

    /* Mapear memoria */
    char *ptr = mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    /* Pipe para comunicación padre-hijo */
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {
        /* PADRE */
        close(pipefd[0]); // cerrar lectura

        for (int i = 0; i < SIZE; i++) {
            if (i % n == 0) {
                if (write(pipefd[1], &x, 1) == -1) {
                    perror("write");
                }
            }
        }

        close(pipefd[1]);
        wait(NULL);

        printf("Contenido de memoria compartida:\n");
        for (int i = 0; i < SIZE; i++) {
            printf("%c", ptr[i]);
        }
        printf("\n");

    } else {
        /* HIJO */
        close(pipefd[1]); // cerrar escritura

        char buffer;
        int index = 0;

        while (read(pipefd[0], &buffer, 1) > 0) {
            if (index < SIZE) {
                ptr[index++] = buffer;
            }
        }

        close(pipefd[0]);
        exit(0);
    }

    /* Limpieza */
    munmap(ptr, SIZE);
    close(fd);

    if (creado) {
        shm_unlink(SHM_NAME);
    }

    return 0;
}