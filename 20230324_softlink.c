#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main(int argc, char **argv){
	int a;
	scanf("%d",&a);
	symlink(argv[1],argv[2]);
	if (a == -1)
	{
		system("sudo rm -rf b.txt");
	}

	if(access(argv[2],F_OK)== -1)
	{
		printf("b.txt is not exist.");
		exit(1);
	}
	printf("b.txt is exist.");

}
