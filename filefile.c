#include <stdio.h>
#include <stdlib.h>

FILE *fp;

void close_file() {
    if (fp != NULL) {
        fclose(fp);
        printf("File closed.\n");
    }
}

int main() {
    char filename[100];
    char buffer[1000];

    printf("Enter file name: ");
    scanf("%s", filename);

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Failed to open file.\n");
        exit(1);
    }

    while (fgets(buffer, 1000, fp) != NULL) {
        printf("%s", buffer);
    }

    atexit(close_file);
	return 0;
}
