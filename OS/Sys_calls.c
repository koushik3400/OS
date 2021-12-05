// System calls (fork, getpid, getppid, exit)

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void main()
{
	int pid=fork();

	if(pid==0)
	{
		printf("Child process\n");
		printf("Pid of child in child= %d\n", getpid());
		printf("pid of parent in child= %d\n",getppid());
		exit(0);
	}
	else
	{
		printf("parent process\n");
		printf("pid of child in parent= %d\n", getpid());
		printf("pid of parent in parent= %d\n", getppid());
		exit(0);
	}
}

// System calls (open, close, read, write)

#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>
#include<fcntl.h>
void main(int argc,char *argv[])
{
	int f1,f2,c;
	char buf[1024];
	f1=open(argv[1],O_RDONLY);
	f2=open(argv[2],O_WRONLY|O_CREAT,S_IRWXU|S_IRGRP| S_IROTH);
	while((c=read(f1,buf,1024))>0)
	write(f2,buf,c);
	printf("Copied\n");
	close(f1);
	close(f2);
}


// System calls (wait & exec)

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
void main()
{
    int option;
    do
    {
        printf("select the option\n");
        printf("0.exit\n");
        printf("1.pwd command \n");
        printf("2.date command \n");
        printf("3.who command \n");
        printf("your choice: ");
        scanf("%d",&option);
switch(option)
{
case 1:
if (fork())
wait(0);
else
execlp("pwd","pwd",(char *)NULL);
break;
case 2:
if (fork())
wait(0);
else
execlp ("date","date",(char *)NULL);
case 3:
if (fork())
wait(0);
else
execlp ("who","who",(char *)NULL);
break;
case 0:
break; 
default:
printf("enter the choice 0->3 only\n");
}
}
while (option != 0);
}

