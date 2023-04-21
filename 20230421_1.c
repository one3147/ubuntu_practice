#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#define NUM 5
int main()
{
	pid_t pid[NUM];
	for (int i = 0; i < NUM; i++)
	{
		pid[i] = fork();
		if (pid[i] < 0)
		{
			printf("error : fork failed.\n");
			exit(1);
		}
		else if(pid[i] == 0)
		{
			printf("child process, PID : %d and PPID : %d",getpid(),getppid());

		}
		else
		{
			printf("Parent process with PID %d\n", getpid());
		}
	}
}
