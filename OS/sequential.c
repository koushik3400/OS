#include<stdio.h>
#include<stdlib.h>
int main()
{
    int start,f[32],n_f,length,flag=-1;
    char filename[30];
    for(int i=0;i<32;i++)
    {
        f[i]=-1;
    }
    printf("Enter the number of files:\n");
    scanf("%d",&n_f);
    for(int i=0;i<n_f;i++)
    {
        printf("\nEnter the starting block,lenght and gilename:");
        scanf("%d %d %s",&start,&length,&filename);
        for(int j=start;j<start+length;j++)
        {
            if(f[j]==-1)
            {
                f[j]=1;
                flag=1;
            }
            else
            {
                printf("file %s can not be allocated..\n",filename);
                flag=-1;
                break;
            }
        }
        if(flag!=-1)
        {
            printf("\n file %s is allocated succcessfully..\n",filename);
            printf("File\t\t start\t\tlength\n");
            printf("%s\t\t%d\t\t%d\t\t",filename,start,length);
        }
        
    }
    return 0;
    
    
}
