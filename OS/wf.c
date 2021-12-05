#include <stdio.h>
#include<stdlib.h>
#include<unistd.h>
void bestfit(int n_m,int n_p,int mem[],int pro[])
{
    void sort(int mem[],int n_m)
    {
        int temp;
        for(int i=0;i<n_m-1;i++)
        {
            for(int j=i+1;j<n_m;j++)
            {
                if(mem[i]<mem[j])
                {
                    temp=mem[i];
                    mem[i]=mem[j];
                    mem[j]=temp;
                }
            }
        }
    }
    int dup_mem[50];
    for(int i=0;i<n_m;i++)
    {
        dup_mem[i]=mem[i];
    }
    sort(dup_mem,n_m);
    for(int i=0;i<n_p;i++)
    {
        int flag=0;
        for(int j=0;j<n_m;j++)
        {
            if(dup_mem[j]>=pro[i])
            {
                printf("%dKB process is allocated to %dKB block\n",pro[i],dup_mem[j]);
                dup_mem[j]=dup_mem[j]-pro[i];
                printf("size of hole after allocation %dKB\n",dup_mem[j]);
                flag=1;
                break;
            }
        }
        if(flag==0)
        {
            printf("%d KB process can not be allocated\n",pro[i]);
        }
        
    
    }
    
    
}


int main()
{
    
    int blocks[50],processes[50],n_b,n_p;
    printf("Enter the number of blocks:\n");
    scanf("%d",&n_b);
    for(int i=0;i<n_b;i++)
    {
        printf("Enter the value of block %d in KB:\n",i+1);
        scanf("%d",&blocks[i]);
    }
    printf("Enter the number of processes:\n");
    scanf("%d",&n_p);
    for(int i=0;i<n_p;i++)
    {
        printf("Enter the value of process %d in KB:\n",i+1);
        scanf("%d",&processes[i]);
    }
    worstfit(n_b,n_p,blocks,processes);
    return 0;
    
    
}