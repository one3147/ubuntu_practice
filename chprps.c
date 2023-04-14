#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    long long int x, y;
    int parent_result, child_result;

    printf(">>");
    scanf("%lld %lld", &x, &y);

    pid_t pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Failed\n");
        exit(1);
    } 
	else if (pid == 0) {
        int i;
        child_result = 0;

        for (i = x; i <= y; i++) {
            child_result += i;
        }

        printf("result: %d\n", child_result);

        exit(0);
    } 
	else {
        int i;
        parent_result = 1;

        for (i = 0; i < y; i++) {
            parent_result *= x;
        }

        wait(NULL);

        printf("Parent process result: %lld\n", parent_result);
        printf("Child process result: %lld\n", child_result);

        printf("Total result: %lld\n", parent_result + child_result);
    }

    return 0;
}

