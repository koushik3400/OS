#include<stdio.h>

#include<limits.h>
int capacity;
int fifo(int pages[],int n)
{
    int page_table[50],p_f,flag=0,i,j;
    for(int i=0;i<capacity;i++)
    {
        page_table[i]=-1;
    }
    printf("\nFIFO");
    for(i=0;i<n;i++)
    {
        flag=1;
        if(i<capacity)
        {
            page_table[i]=pages[i];
            p_f++;
        }
        else
        {
           for(j=0;j<capacity;j++)
           {
               if(page_table[j]==pages[i])
               {
                   flag=0;
                   break;
               }
           }
           if(j==capacity)
           {
               int x=(p_f)%capacity;
               page_table[x]=pages[i];
               p_f++;
           }
        }
        int d;
        if(flag)
        {
            printf("\n");
            for(d=0;d<capacity;d++)
            {
                printf("%d\t",page_table[d]);
            }
            printf("Page fault\n");
        }
        else
        {
            printf("\n");
            for(d=0;d<capacity;d++)
            {
                printf("%d\t",page_table[d]);
            }
        }
    }
    return p_f;
}
int main()
{
    int page_faults;
    int pages[25],n;
    printf("Enter the capacity:\n");
    scanf("%d",&capacity);
    printf("enter the number of pages:\n");
    scanf("%d",&n);
    printf("Enter the sequence:\n");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&pages[i]);
    }
    page_faults=fifo(pages,n);
    printf("\nFIFO:\npage faults:%d\n",page_faults);
    
    return 0;
    
    
    
    
}