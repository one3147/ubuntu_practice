#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main() {
   char path[100];
   DIR *dir;

   printf("디렉토리 경로를 입력하세요: ");
   scanf("%s", path);

   dir = opendir(path);

   if (dir) {
      printf("%s는(은) 존재하는 경로입니다.\n", path);
      closedir(dir);
   } else {
      printf("%s는(은) 존재하지 않는 경로입니다.\n", path);
      exit(1);
   }

   return 0;
}

