#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static int compare(const void *a, const void *b)
{
    int l[2], r[2];
    memcpy(&l, a, sizeof(a));
    memcpy(&r, b, sizeof(b));
    return (l[0] - r[0]);
}
int lower_bound(int x[][2], int n, int val)
{
    int f = 0;
    int l = n;
    int m;
    while (f < l)
    {
        m = (l + f) / 2;
        if (x[m][0] < val)
            f = m + 1;
        else
            l = m;
        if (val == 417)
            printf("%d ", x[m][0]);
    }
    if (f == n)
        return -1;
    return f;
}
void first_fit(int seg[], int n, int pro[], int m)
{
    int i = 0, j = 0, x = -1;
    while (j < m)
    {
        if (i % n == 0 && x == j)
        {
            printf("External Fragmentation!!\n");
            j = m + 1;
            break;
        }
        else if (i % n == 0)
            x = j;
        if (seg[i % n] >= pro[j] && j < m)
        {
            seg[i % n] -= pro[j];
            printf("Process %d allocated to seg %d of size %d. Remaining size: %d\n", j, i % n, seg[i % n] + pro[j], seg[i % n]);
            j++;
        }
        i++;
    }
}
void worst_fit(int mapper[][2], int n, int pro[], int m)
{
    qsort(mapper, n, sizeof *mapper, compare);
    int i = n - 1, j = 0, x = -1;
    while (j < m)
    {
        if (i == n - 1 && x == j)
        {
            printf("External Fragmentation!!\n");
            j = m;
            break;
        }
        else if (i == n - 1)
            x = j;
        if (mapper[i][0] >= pro[j] && j < m)
        {
            mapper[i][0] -= pro[j];
            printf("Process %d allocated to seg %d of size %d. Remaining size: %d\n", j, mapper[i][1], mapper[i][0] + pro[j], mapper[i][0]);
            qsort(mapper, n, sizeof(*mapper), compare);
            j++;
            for (int i = 0; i < n; i++)
                printf("%d ", mapper[i][0]);
            printf("\n");
        }
        i--;
        if (i == -1)
            i = n - 1;
    }
    for (int i = 0; i < n; i++)
        printf("%d ", mapper[i][0]);
    printf("\n");
}
void best_fit(int mapper[][2], int n, int pro[], int m)
{
    for (int i = 0; i < m; i++)
    {
        qsort(mapper, n, sizeof(*mapper), compare);
        for (int i = 0; i < n; i++)
            printf("%d ", mapper[i][0]);
        printf("\n");
        int k = lower_bound(mapper, n, pro[i]);
        if (k == -1)
        {
            printf("External Fragmentation!!\n");
            break;
        }
        mapper[k][0] -= pro[i];
        printf("Process %d allocated to seg %d of size %d. Remaining size: %d\n", i, mapper[k][1], mapper[k][0] + pro[i], mapper[k][0]);
    }
    for (int i = 0; i < n; i++)
        printf("%d ", mapper[i][0]);
    printf("\n");
}
void main()
{
    const int n;
    printf("Give the no. of segments: ");
    scanf("%d", &n);
    int seg[n];
    int mapper[n][2], worst[n][2];
    for (int i = 0; i < n; i++)
    {
        printf("Give the segment size of segment %d: ", i);
        scanf("%d", &seg[i]);
        mapper[i][0] = seg[i];
        mapper[i][1] = i;
        worst[i][0] = seg[i];
        worst[i][1] = i;
    }
    const int m;
    printf("Give the no. of processes: ");
    scanf("%d", &m);
    int pro[m];
    for (int i = 0; i < m; i++)
    {
        printf("Give the segment size of Process %d: ", i);
        scanf("%d", &pro[i]);
    }
    printf("_ _ _ _ _ _ _ _");
    printf("\nFIRST FIT!");
    printf("\n_ _ _ _ _ _ _ _\n");
    first_fit(seg, n, pro, m);
    printf("\n\n_ _ _ _ _ _");
    printf("\nBEST FIT!");
    printf("\n_ _ _ _ _ _\n");
    best_fit(mapper, n, pro, m);
    printf("\n\n_ _ _ _ _ _");
    printf("WORST FIT!\n");
    printf("_ _ _ _ _ _\n");
    worst_fit(worst, n, pro, m);
}