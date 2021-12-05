#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h> #include<errno.h>

#define BUFF_SIZE 1024

int main(int argc, char *argv[])
{
        int src_fd,dest_fd,nbread,nbwrite;
        char *buff[BUFF_SIZE],ch[3];

        if(argc !=3) //without options argc is 3
        {
                printf("\nInvalid arguments!!");
                exit(EXIT_FAILURE);
        }

        src_fd = open(argv[1],O_RDWR);//normal copying

        if(src_fd==-1)
        {
                printf("\nError in opening file %s !",argv[1]);
                exit(EXIT_FAILURE);
        }

        dest_fd = open(argv[2],O_RDWR|O_CREAT);
        if(dest_fd==-1)
        {
                printf("\nError in opening file %s !",argv[2]);
                exit(EXIT_FAILURE);
        }


        while((nbread=read(src_fd,buff,BUFF_SIZE))>0) //to check if not empty
        {
                nbwrite=write(dest_fd,buff,nbread);
                if(nbwrite!=nbread) //corruption in data
                {
                        printf("\nError in writing data to %s !",argv[2]);
                }
        }

        if(nbread==-1)
                printf("\nError in reading data from %s",argv[1]);

        if(close(src_fd)==-1)
                printf("\nError in closing file %s !",argv[1]);

        if(close(dest_fd)==-1)
                printf("\nError in closing file %s !",argv[2]);
        printf("\nFILE COPIED!");
        exit(EXIT_SUCCESS);
}