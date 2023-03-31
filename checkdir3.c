#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

void check_symlink(char *path);

int main() {
    char path[100];

    printf("디렉토리 경로를 입력하세요: ");
    scanf("%s", path);

    check_symlink(path);

    return 0;
}

void check_symlink(char *path) {
    struct stat sb;

    if (lstat(path, &sb) == -1) {
        printf("stat 함수를 사용할 수 없습니다.\n");
        exit(1);
    }

    if (S_ISLNK(sb.st_mode)) {
        printf("%s는 소프트링크입니다.\n", path);
    } else if (S_ISDIR(sb.st_mode)) {
        printf("%s는 디렉토리입니다.\n", path);
    } else {
        printf("%s는 파일이거나, 다른 유형의 파일입니다.\n", path);
    }
}

