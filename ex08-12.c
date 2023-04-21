#include <unistd.h>
int main() 
{
	setenv("MYDATA", "5", 0);
	execl("./ex08-13", "ex08-13", (char *) 0);
}
