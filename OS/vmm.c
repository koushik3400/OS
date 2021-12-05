#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int phy_mem[20],phy_start,frame_size,no_of_pages,no_of_frames; int page_table[20];
int random_number(int x)
{
        return (rand()%8);
}

int display(int page_table[8],int phy_mem[8])
{
        int i;
        printf("\nframe_no\tpage_no\tphysical addresses");
        for(i=0;i<no_of_frames;i++)
        {
                if(i!=0)
                {
                        printf("\n%d\t\t%d\t%d",i,phy_mem[i],phy_start+(frame_size*i)-1);
                }

                else
                {
                        printf("\n%d\t\t%d\t%d",i,phy_mem[i],(phy_start));
                }

        }
        return 0;
}

int main()
{
        int page_number,page_offset,i,j,phy_add,frame_no;
        printf("\nenter number of frames:");
        scanf("%d",&no_of_frames);
        printf("\nenter frame size:");

        scanf("%d",&frame_size);
        printf("\nenter number of pages:");
        scanf("%d",&no_of_pages);
        if(no_of_pages>no_of_frames)
        {
                printf("\nnumber of pages should be less than or equal to number of frames");
                printf("\nenter number  of      pages:");
                scanf("%d",&no_of_pages);
        }
        printf("\nenter physical address:");
        scanf("%d",&phy_start);
        for(i=0;i<no_of_frames;i++)
        {
                phy_mem[i]=-1;
        }
        printf("\nbefore allocating:\n");
        display(page_table,phy_mem);
        printf("\nafter allocating:\n");
        srand(time(0));
        for(i=0;i<no_of_pages;i++)
        {
                for(j=0;j<8;j++)
                {
                        int x=random_number(j);
                        if(phy_mem[x] == -1)
                        {
                                phy_mem[x]=i;
                                page_table[i]=x;
                                break;
                        }
                }
        }
        display(page_table,phy_mem);
        printf("\nenter page number(0 to %d) and page offset(0 to %d):",no_of_pages-1,frame_size- 1);
        scanf("%d %d",&page_number,&page_offset);
        if(page_number>= no_of_pages || page_offset>= frame_size)
        {
                printf("\nlogical address is invalid:trap addressing error\n");
        }
        else
        {
                frame_no=page_table[page_number];
                printf("\nframe_no:%d",frame_no);
                if(frame_no !=0)
                {
                        phy_add=phy_start+(frame_no*frame_size -1)+page_offset;
                }
                else
                {
                        phy_add=phy_start+page_offset;
                }
                printf("\nphysical address is:%d\n",phy_add);
        }
        return 0;

}



