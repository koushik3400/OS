#include <unistd.h>
#include <string.h>
#include <stdio.h>
int main()
{
    char t[50];
    int pid[50], at[50], bt[50], start[50], finish[50], tat[50], wt[50], i, j, temp, n;
    int tot_wt = 0, tot_tat = 0;
    printf("Enter the no.of processes:");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        printf("Enter the process id,Arrival time and Burst time:");
        scanf("%d%d%d", &pid[i], &at[i], &bt[i]);
    }
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (at[i] < at[j])
            {
                temp = at[i];
                at[i] = at[j];
                at[j] = temp;
                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;
                temp = pid[i];
                pid[i] = pid[j];
                pid[j] = temp;
            }
        }
    }
    for (i = 0; i < n; i++)
    {
        if (i == 0)
        {
            start[i] = at[i];
        }

        else
        {
            start[i] = finish[i - 1];
        }
        wt[i] = start[i] - at[i];
        finish[i] = start[i] + bt[i];
        tat[i] = finish[i] - at[i];
    }
    int n_bt[n], n_pid[n];
    for (i = 0; i < n; i++)
    {
        n_bt[i] = bt[i];
        n_pid[i] = pid[i];
    }
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (pid[i] < pid[j])
            {
                temp = at[i];
                at[i] = at[j];
                at[j] = temp;
                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;
                temp = pid[i];
                pid[i] = pid[j];

                pid[j] = temp;
                temp = wt[i];
                wt[i] = wt[j];
                wt[j] = temp;
                temp = tat[i];
                tat[i] = tat[j];
                tat[j] = temp;
            }
        }
    }
    int gantt[n + 1];
    printf("\n      Process ArrivalTime(ms) BurstTime(ms)   WaitingTime(ms) TurnaroundTime(ms)");
    for (i = 0; i < n; i++)
    {
        printf("\n %d\t\t\t%d\t\t%d\t\t%d\t\t%d", pid[i], at[i], bt[i], wt[i], tat[i]);
        tot_wt += wt[i];
        tot_tat += tat[i];
    }
    gantt[0] = 0;
    for (i = 1; i <= n; i++)
    {
        gantt[i] = gantt[i - 1] + n_bt[i - 1];
    }
    printf("\nAverage Waiting Time (in ms) = %f", (float)tot_wt / n);

    printf("\nAverage Turn Around Time(in ms) = %f", (float)tot_tat / n);
    printf("\n\n GANTT CHART\n\n");
    for (i = 0; i < n; i++)
    {
        printf("| %d ", n_pid[i]);
    }
    printf("|\n");
    for (i = 0; i <= n; i++)
    {
        printf("%d ", gantt[i]);
    }
    printf("\n");
    return 0;
}