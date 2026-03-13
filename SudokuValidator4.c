#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <omp.h>

int sudoku[9][9];

int checkRow(int row) {
    int seen[10] = {0};
    for(int i = 0; i < 9; i++) {
        int num = sudoku[row][i];
        if(num < 1 || num > 9 || seen[num]) return 0;
        seen[num] = 1;
    }
    return 1;
}

int checkColumn(int col) {
    int seen[10] = {0};
    for(int i = 0; i < 9; i++) {
        int num = sudoku[i][col];
        if(num < 1 || num > 9 || seen[num]) return 0;
        seen[num] = 1;
    }
    return 1;
}

int checkSubgrid(int startRow, int startCol) {
    int seen[10] = {0};
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            int num = sudoku[startRow+i][startCol+j];
            if(num < 1 || num > 9 || seen[num]) return 0;
            seen[num] = 1;
        }
    }
    return 1;
}

void* columnThread(void* arg) {
    // Permitir anidamiento y definir los hilos exactos para 9 columnas
    omp_set_nested(1); 
    omp_set_num_threads(9);

    printf("El thread que ejecuta el metodo de revision de columnas es: %ld\n", syscall(SYS_gettid));
    
    #pragma omp parallel for // schedule(dynamic)
    for(int i = 0; i < 9; i++) {
        printf("En la revision de columnas el siguiente es un thread en ejecucion: %ld\n", syscall(SYS_gettid));
        if(!checkColumn(i)) {
            printf("Columna %d inválida\n", i);
        }
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    // Permitir anidamiento y definir hilos para las funciones del main
    omp_set_nested(1);
    omp_set_num_threads(9); 

    if(argc < 2) {
        printf("Uso: ./SudokuValidator archivo\n");
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);
    if(fd == -1) { perror("Error al abrir"); return 1; }
    
    char *data = mmap(NULL, 81, PROT_READ, MAP_PRIVATE, fd, 0);

    int k = 0;
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            sudoku[i][j] = data[k++] - '0';
        }
    }

    int j;
    #pragma omp parallel for private(j)
    for(int i = 0; i < 9; i += 3) {
        for(j = 0; j < 9; j += 3) {
            checkSubgrid(i, j);
        }
    }

    pid_t pid_padre = getpid();
    pid_t child1 = fork();
    if(child1 == 0) {
        char pid_str[10];
        sprintf(pid_str, "%d", pid_padre);
        printf("\n--- PS ANTES DEL PTHREAD ---\n");
        execlp("ps", "ps", "-p", pid_str, "-lLf", NULL);
        exit(0);
    }
    wait(NULL);

    pthread_t tid;
    pthread_create(&tid, NULL, columnThread, NULL);
    pthread_join(tid, NULL);

    #pragma omp parallel for
    for(int i = 0; i < 9; i++) {
        checkRow(i);
    }

    printf("\nID del hilo Main: %ld\n", syscall(SYS_gettid));
    printf("Sudoku resuelto!\n");

    pid_t child2 = fork();
    if(child2 == 0) {
        char pid_str[10];
        sprintf(pid_str, "%d", pid_padre);
        printf("\n--- PS AL FINALIZAR ---\n");
        execlp("ps", "ps", "-p", pid_str, "-lLf", NULL);
        exit(0);
    }
    wait(NULL);

    munmap(data, 81);
    close(fd);
    return 0;
}