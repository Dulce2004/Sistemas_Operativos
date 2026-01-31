#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    int fd_origen, fd_destino;
    char buffer[1024];
    int bytes_leidos;

    // Verificar que se pasaron 2 argumentos
    if (argc != 3) {
        printf("Uso: %s archivo_origen archivo_destino\n", argv[0]);
        return 1;
    }

    // Abrir archivo origen en modo lectura
    fd_origen = open(argv[1], O_RDONLY);
    if (fd_origen < 0) {
        perror("Error al abrir archivo origen");
        return 1;
    }

    // Crear / abrir archivo destino en modo escritura
    fd_destino = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_destino < 0) {
        perror("Error al abrir archivo destino");
        close(fd_origen);
        return 1;
    }

    // Leer y escribir hasta que ya no haya datos
    while ((bytes_leidos = read(fd_origen, buffer, sizeof(buffer))) > 0) {
        write(fd_destino, buffer, bytes_leidos);
    }

    // Cerrar archivos
    close(fd_origen);
    close(fd_destino);

    return 0;
}
