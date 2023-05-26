#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "sys/types.h"
#include "sys/wait.h"

int main() {
    int pipes[3][2];
    int i;
    pid_t child_pid;

    for (i = 0; i < 3; i++) 
    {
        if (pipe(pipes[i]) == -1) 
	{
		printf("failed to call pipe");
		exit(1);
        }
    }

    for (i = 0; i < 3; i++) 
    {
        child_pid = fork();

        if (child_pid == -1) 
	{
            printf("failed to call fork");
            exit(1);

        } 
	else if (child_pid == 0) 
	{
            close(pipes[i][1]); 
            char message[30];
            read(pipes[i][0], message, sizeof(message));
            printf("Child %d : %s\n", i, message);
            close(pipes[i][0]); 
            exit(1);
        }
    }

    for (i = 0; i < 3; i++) {
        close(pipes[i][0]); 
        char message[] = "leaf{y0u_c4n_pr1nt_f1Ag!}";
        write(pipes[i][1], message, sizeof(message));
        close(pipes[i][1]);  
    }
    for (i = 0; i < 3; i++)
    {
	wait(NULL);
    }	
    return 0;
}

