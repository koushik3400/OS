#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
struct p_t
{
        int x; int y;
};
int capacity;
int optimal(int pages[],int n)
{
         int i,j,p_f=0,flag=0;
        int size=0;
        struct p_t table[50],page_table[capacity];
        for(i=0;i<capacity;i++)
        {
                page_table[i].x=-1;
        }
        printf("\nOPTIMAL:");
        for(i=0;i<n;i++)
        {
                if(i<capacity)
                {
                        table[size].x=pages[i];
                        table[size].y=1;
                        size++;
                }
                else
                {
                        for(j=0;j<size;j++)
                        {
                                if(table[j].x == pages[i])
                                {
                                        (table[j].y)++;
                                        break;

                                }
                        }
                        if(j==size)
                        {
                                table[size].x=pages[i];

                                table[size].y=1;
                                size++;
                        }
                }
        }
        for(i=0;i<n;i++)
        {
                flag=1;
                if(i<capacity)
                {
                        page_table[i].x=table[i].x;
                        page_table[i].y=table[i].y-1;
                        table[i].y=table[i].y-1;

                        p_f++;
                }
                else
                {
                        for(j=0;j<capacity;j++)
                        {
                                if(page_table[j].x==pages[i])
                                {

                                        page_table[j].y=page_table[j].y-1;
                                        flag=0;
                                        break;
                                }
                        }
                        if(j==capacity)
                        {
                                int k,min=INT_MAX,m_i=0;
                                for(k=0;k<capacity;k++)
                                {
                                        if(page_table[k].y< min)
                                        {
                                                min=page_table[k].y;

                                        }
                                }
                                for(k=0;k<size;k++)
                                {
                                        if(pages[i]==table[k].x)
                                        {
                                                page_table[m_i].x=pages[i];
                                                page_table[m_i].y=table[k].y-1;
                                                break;
                                        }
                                }
                                p_f++;

                        }

                }
                int d;
                if(flag)
                {
                        printf("\n");
                        for(d=0;d<capacity;d++)
                        {
                                printf("%d ",page_table[d].x);
                        }
                        printf(" page fault\n");
                }

                else
                {
                        printf("\n");
                        for(d=0;d<capacity;d++)
                        {


                                printf("%d ",page_table[d].x);
                        }
                }

        }
        return p_f;
}
int main()
{
        int page_faults[3]={0,0,0};
        int pages[25],n;
        printf("\nenter capacity:");
        scanf("%d",&capacity);
        printf("\nenter number of pages:");
        scanf("%d",&n);
        int i;
        printf("\nenter the sequence:");
        for(i=0;i<n;i++)
        {
                scanf("%d",&pages[i]);
        }
        page_faults[0]=optimal(pages,n);
        printf("\noptimal:\npage    faults:%d",page_faults[0]);
        return 0;
}