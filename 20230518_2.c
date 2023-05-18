#include <stdio.h>
#include <unistd.h>
#include <signal.h>


void handler() {
    printf("부모 프로세스 종료\n");
}

int main() {
    struct sigaction act;
    sigfillset(&(act.sa_mask));
    act.sa_handler = handler;
    sigaction(SIGINT, &act, NULL);
    pid_t pid;
    if ((pid = fork()) == 0) {
        printf("자식 프로세스 시작\n");
        kill(getppid(), SIGINT);
        printf("자식 프로세스 종료\n");
    } else if (pid > 0) {
        printf("부모 프로세스 시작\n");
        pause();
    }
}
