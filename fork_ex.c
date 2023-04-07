#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int num, sum = 0;
    pid_t pid;

    printf("양의 정수를 입력하세요: ");
    scanf("%d", &num);

    pid = fork();

    if (pid < 0) 
	{
        fprintf(stderr, "fork failed\n");
        return 1;
    }
    else if (pid == 0) 
	{
        int i, prod = 1;
        for (i = 1; i <= num; i++) 
		{
            prod *= i;
        }
        printf("자식 프로세스: 1부터 %d까지의 곱은 %d입니다.\n", num, prod);
    }
    else {
        int i;
        for (i = 1; i <= num; i++) 
		{
            sum += i;
        }
        printf("부모 프로세스: 1부터 %d까지의 합은 %d입니다.\n", num, sum);
    }

    return 0;
}

