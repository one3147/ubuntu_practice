#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
int main(int argc, char **argv)
{
	if(argc!=2) exit(0);
	filei(argv[1]);
	fileo(argv[1]);
}

void filei(char *filename)
{
	int fd = open(filename, O_RDWR | O_CREAT, 0644);
	char flag[1024] = {};
	scanf("%s",flag);
	write(fd, flag, 25);
	printf("%s\n",flag);
	close(fd);
}

void fileo(char *filename)
{
	int fd = open(filename, O_RDWR | O_CREAT, 0644);
	char String[1024] = {};
	read(fd,String,1024);
	int count[26] = {0};
	for (int i = 0;String[i] !='\0';i++)
	{
		if(isalpha(String[i]))
		{
			int index = tolower(String[i]) - 'a';
			count[index]++;
		}
	}
	int sum = 0;
	printf("Alphabet Count : ");
	for(int i = 0; i < 26; i++)
	{
		sum += count[i];
	}
	printf("%d\n",sum);
	close(fd);
	return 0;
}
