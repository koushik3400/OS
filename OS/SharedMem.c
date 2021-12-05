#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int main(){
int r=fork();
if(r!=0){
wait(0);
printf("CLIENT PROCESS:\n");
key_t key=ftok("shmfile",65);
int shmid= shmget(key,1024,0666|IPC_CREAT);
char *str1=(char*) shmat(shmid,(void*)0,0);
printf("data read from memory:%s\n",str1);
shmdt(str1);
}
else{
printf("SERVER PROCESS:\n");
key_t key=ftok("shmfile",65);
int shmid =shmget(key,1024,0666|IPC_CREAT);
char *str= (char*)shmat(shmid,(void*)0,0);
printf("enter data t be written into shared memory:");
scanf("%[^\n]%*c",str);
printf("the string is: %s\n",str);
shmdt(str);
}
}
