#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <signal.h>
int main()
{
    pid_t pid;
    int fd;
    char buffer[1024];
    time_t cur_time;
    struct sigaction act;

    fd = open("curtime.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);

    for (int i = 0; i < 60; i++) {
        sleep(10);
        pid = fork();
		setsid();
        if (pid == 0) {
            time_t result = time(NULL);
            strcpy(buffer,asctime(localtime(&result)));
			write(fd,buffer,strlen(buffer));
            exit(0);
        }
    }

    return 0;
}
