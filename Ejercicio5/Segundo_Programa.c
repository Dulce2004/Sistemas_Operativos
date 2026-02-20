#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main() {

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        execl("./ipc", "ipc", "4", "X", NULL);
    } else {
        execl("./ipc", "ipc", "6", "O", NULL);
    }

    return 0;
}