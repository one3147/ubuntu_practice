#include<stdio.h>
int main()
{
	FILE *file;
	file = fopen("test.txt","r");
	printf("%c",fgetc(file));
	fclose(file);
	return 0;
}
