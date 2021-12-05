#include<stdio.h>
#include<stdlib.h>

int  main()
{
        int n,m,i[3];
        printf("Enter the number of processes: \n");
        scanf("%d",&n);
        printf("Enter the number of resource type: \n");
        scanf("%d",&m);

        printf("Enter the instances of A,B and C respectively");
        scanf("%d",&i[0]);
        scanf("%d",&i[1]);
        scanf("%d",&i[2]);

        int available[3]={3,3,2};

    int max[5][3]={{7,5,3},
                        {3,2,2},
                        {9,0,2},
                        {2,2,2},
                        {4,3,3}};


        int allocation[5][3]={{0,1,0},
                              {2,0,0},
                              {3,0,2},
                              {2,1,1},
                              {0,0,2}};

        int need[n][m];
        printf("the number of instances needed by a process\n");
        for(int i=0;i<n;i++)
        {
                 for(int j=0;j<m;j++)
                          {
                                    need[i][j]=max[i][j]-allocation[i][j];
                                      printf("%d",need[i][j]);
                          }
                 printf("\n");

        }
int x[n], a[n], index = 0;
    for (int k = 0; k < n; k++) {
        x[k] = 0;
    }
int y = 0;
    for (int k = 0; k < 5; k++) {
        for (int i = 0; i < n; i++) {
            if (x[i] == 0) {

                int flag = 0;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > available[j]){
                        flag = 1;
                         break;
                    }
                }

                if (flag == 0) {
                    a[index++] = i;
                    for (y = 0; y < m; y++)
                        available[y] += allocation[i][y];
                    x[i] = 1;
                }
            }
        }
    }

    printf("Following is the SAFE Sequence\n");
    for (int i = 0; i < n - 1; i++)
        printf(" P%d ->", a[i]);
    printf(" P%d", a[n - 1]);

    return (0);


}