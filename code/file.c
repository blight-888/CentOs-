#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	int id = fork();

	if(id == -1)
	{
		printf("fork error!\n");
	}
	if(id == 0)
	{
		printf("child pid is: %d parents pid is: %d\n", getpid(), getppid());
		sleep(3);
	}
	else
	{
		printf("father pid is: %d child pid is: %d\n", getppid(), getpid());
		printf("father process is exited!\n");
	}
	return 0;
}
