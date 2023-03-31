#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

void count_files_and_dirs(char *path, int *file_count, int *dir_count);

int main() {
    char path[100];
    int file_count = 0, dir_count = 0;

    printf("디렉토리 경로를 입력하세요: ");
    scanf("%s", path);

    count_files_and_dirs(path, &file_count, &dir_count);

    printf("파일 개수: %d\n", file_count);
    printf("디렉토리 개수: %d\n", dir_count);

    return 0;
}

void count_files_and_dirs(char *path, int *file_count, int *dir_count) {
    DIR *dir;
    struct dirent *ent;

    dir = opendir(path);

    if (dir == NULL) {
        printf("디렉토리를 열 수 없습니다.\n");
        exit(1);
    }

    while ((ent = readdir(dir)) != NULL) {
        if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0) {
            if (ent->d_type == DT_REG) {
                (*file_count)++;
            } else if (ent->d_type == DT_DIR) {
                (*dir_count)++;
                char sub_path[100];
                sprintf(sub_path, "%s/%s", path, ent->d_name);
                count_files_and_dirs(sub_path, file_count, dir_count);
            }
        }
	}
}
