#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "sys/types.h"
#include "sys/wait.h"

#define SIZE 512

int main() {
    int fileDes[2];

    char *msg = "leaf{D0_y0u_kn0w_P1p3?_g0D_D4mmmmmm}";

    pid_t pid;
    if (pipe(fileDes) == -1) {
        printf("fail to call pipe()\n");
        exit(1);
    }

    if ((pid = fork()) == -1) {
        printf("fail to call fork()\n");
        exit(1);

    } else if (pid > 0) {
        close(fileDes[0]);
        write(fileDes[1], msg, SIZE);
        printf("[parent] %s\n", msg);
    } else {
        sleep(1);
        close(fileDes[1]);
        read(fileDes[0], msg, SIZE);
        printf("[child] %s\n", msg);
    }
}
