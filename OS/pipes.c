#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{
	int fd[2],size=32;
	if(pipe(fd)<0)
	{
		printf("\nPipe creation failed.");
		exit(0);
	}
	printf("\nPipe creation successful. In Parent Process.");
	//close(fd[0]);
	write(fd[1],"Hello from the Parent Process",size);
	close(fd[1]);
	printf("\nString written into pipe.");
	int pid=fork();
	if(pid==0)
	{
		printf("\nIn Child Process.");
		for(int i=0;i<1;i++)
		{	
			char reader[size];
			read(fd[0],reader,size);
			close(fd[0]);
			printf("\n% s",reader);
		}	
		exit(0);
	}
	_exit(0);
	return 0;
}


