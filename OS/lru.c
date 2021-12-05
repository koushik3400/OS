#include<stdio.h>
#include<limits.h>
struct p_t
{
    int x;
    int y;
};
int capacity;
int lru(int pages[],int n)
{
    int p_f,flag=0,i,j;
    struct p_t page_table[10];
    int temp=0;
    for(int i=0;i<capacity;i++)
    {
        page_table[i].x=-1;
    }
    printf("\nLRU");
    for(i=0;i<n;i++)
    {
        flag=1;
        if(i<capacity)
        {
            page_table[i].x=pages[i];
            page_table[i].y=temp++;
            p_f++;
        }
        else
        {
           for(j=0;j<capacity;j++)
           {
               if(page_table[j].x==pages[i])
               {
                   page_table[j].y=temp++;
                   flag=0;
                   break;
               }
           }
           if(j==capacity)
           {
               
               int k,min=INT_MAX,m_i=0;
               for(k=0;k<capacity;k++)
               {
                   if(page_table[k].y<min)
                   {
                       min=page_table[k].y;
                       m_i=k;
                   }
               }
               page_table[m_i].x=pages[i];
               page_table[m_i].y=temp++;
               p_f++;
           }
        }
        int d;
        if(flag)
        {
            printf("\n");
            for(d=0;d<capacity;d++)
            {
                printf("%d\t",page_table[d].x);
            }
            printf("Page fault\n");
        }
        else
        {
            printf("\n");
            for(d=0;d<capacity;d++)
            {
                printf("%d\t",page_table[d].x);
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
    page_faults=lru(pages,n);
    printf("LRU:\npage faults:%d\n",page_faults);
    
    return 0;
    
    
    
    
}