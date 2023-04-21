#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_FILE_NUM 3

int main(int argc, char *argv[])
{
    pid_t pid;
    int i, status;
    char *wc_argv[3] = {"wc", NULL, NULL};

    if (argc - 1 > MAX_FILE_NUM)
    {
        printf("Too many files!\n");
        exit(1);
    }

    for (i = 1; i < argc; i++)
    {
        pid = fork();
        if (pid == 0) // 자식 프로세스
        {
            wc_argv[1] = argv[i];
            execvp("wc", wc_argv);
            printf("Error: execvp() failed\n");
            exit(1);
        }
        else if (pid > 0) // 부모 프로세스
        {
            waitpid(pid, &status, 0);
        }
        else
        {
            printf("Error: fork() failed\n");
            exit(1);
        }
    }

    return 0;
}

