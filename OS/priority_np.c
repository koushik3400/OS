#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void res(char name[][20], int arrival_time[], int burst_time[], int priority[], int number, int rr_time);

void sort(char name[][20], int arrival_time[], int burst_time[], int priority[], int atc[], int btc[], int exit_time[], int number);

float avg(int burst_time[], int number);

void cpy(int arrival_time[], int burst_time[], int atc[], int btc[], int number);

int main()
{
    // get the number of processes
    int number;
    printf("enter the number of processes: ");
    scanf("%d", &number);
    if (number == 0)
    {
        printf("no processes given -> program terminated");
        exit(0);
    }
    printf("\n");

    // assign variables to get the inputs from the user
    char name[number][20];
    int arrival_time[number], burst_time[number], priority[number], rr_time = 1;

    // get the inputs from the user
    for (int i = 0; i < number; i++)
    {
        printf("enter the name of process number %d: ", i + 1);
        scanf("%s", name[i]);
    }
    printf("\n");
    for (int i = 0; i < number; i++)
    {
        printf("enter the arrival time of process number %d: ", i + 1);
        scanf("%d", &arrival_time[i]);
    }
    printf("\n");
    for (int i = 0; i < number; i++)
    {
        printf("enter the burst time of process number %d: ", i + 1);
        scanf("%d", &burst_time[i]);
    }
    printf("\n");
    for (int i = 0; i < number; i++)
    {
        printf("enter the priority of process number %d: ", i + 1);
        scanf("%d", &priority[i]);
    }
    printf("\n");

    // printf("enter the quantity of time quantum : ");
    // scanf ("%d", &rr_time);
    // printf("\n\n");

    res(name, arrival_time, burst_time, priority, number, rr_time);
}

// function to sort
void sort(char name[][20], int arrival_time[], int burst_time[], int priority[], int atc[], int btc[], int exit_time[], int number)
{
    char dummy1[20];
    int dummy2, dummy3;
    for (int i = 0; i < number; i++)
    {
        for (int j = i + 1; j < number; j++)
        {
            if (priority[i] > priority[j])
            {
                dummy2 = arrival_time[i];
                arrival_time[i] = arrival_time[j];
                arrival_time[j] = dummy2;

                dummy2 = burst_time[i];
                burst_time[i] = burst_time[j];
                burst_time[j] = dummy2;

                dummy2 = priority[i];
                priority[i] = priority[j];
                priority[j] = dummy2;

                dummy2 = atc[i];
                atc[i] = atc[j];
                atc[j] = dummy2;

                dummy2 = btc[i];
                btc[i] = btc[j];
                btc[j] = dummy2;

                dummy2 = exit_time[i];
                exit_time[i] = exit_time[j];
                exit_time[j] = dummy2;

                strcpy(dummy1, name[i]);
                strcpy(name[i], name[j]);
                strcpy(name[j], dummy1);
            }
        }
    }
}

// function to calculate the avg of burst times
float avg(int burst_time[], int number)
{
    float tot = 0;
    for (int i = 0; i < number; i++)
    {
        tot += burst_time[i];
    }
    float avg = tot / number;
    return (avg);
}

// function to copy arrays
void cpy(int arrival_time[], int burst_time[], int atc[], int btc[], int number)
{
    for (int i = 0; i < number; i++)
    {
        atc[i] = arrival_time[i];
        btc[i] = burst_time[i];
    }
}

// function to calculate the result
void res(char name[][20], int arrival_time[], int burst_time[], int priority[], int number, int rr_time)
{
    // variables to store exit time, counter values and avg value
    int exit_time[number], tat[number], wait_time[number], counter_bef = 0, counter_aft = 0;
    float av_time;
    int buffer;

    // making copy of arrival and burst times
    int atc[number], btc[number];
    cpy(arrival_time, burst_time, atc, btc, number);

    sort(name, arrival_time, burst_time, priority, atc, btc, exit_time, number);

loop:
    av_time = avg(btc, number);

    while (av_time != 0.0)
    {
        for (int i = 0; i < number; i++)
        {
            if ((atc[i] <= counter_bef) && (btc[i] != 0))
            {
                if ((btc[i] - rr_time) > 0)
                {
                    btc[i] -= rr_time;
                    // atc[i] = atc[i] + counter_aft;
                    counter_aft = counter_bef + rr_time;
                    printf("%d..%s..%d || ", counter_bef, name[i], counter_aft);
                    atc[i] = counter_aft;
                    counter_bef = counter_aft;
                    goto loop;
                }
                else if ((btc[i] - rr_time) < 0)
                {
                    buffer = btc[i];
                    btc[i] = 0;
                    counter_aft = counter_bef + buffer;
                    printf("%d..%s..%d || ", counter_bef, name[i], counter_aft);
                    counter_bef = counter_aft;
                    exit_time[i] = counter_aft;
                    goto loop;
                }
                else if ((btc[i] - rr_time) == 0)
                {
                    btc[i] -= rr_time;
                    counter_aft = counter_bef + rr_time;
                    printf("%d..%s..%d || ", counter_bef, name[i], counter_aft);
                    counter_bef = counter_aft;
                    exit_time[i] = counter_aft;
                    goto loop;
                }
            }

            else if ((atc[i] > counter_bef) && (btc[i] != 0))
            {
                buffer = atc[i] - counter_bef;
                counter_aft = counter_bef + buffer;
                printf("%d..no operation..%d || ", counter_bef, counter_aft);
                counter_bef = counter_aft;
                goto loop;
            }
        }
    }

    printf("\n\n");

    for (int i = 0; i < number; i++)
    {
        tat[i] = exit_time[i] - arrival_time[i];
        wait_time[i] = tat[i] - burst_time[i];
    }

    // printing the table
    printf("%10s | %10s | %10s | %10s | %10s | %10s | %10s\n", "name", "arrival", "burst", "priority", "exit", "wait", "turnaround");
    for (int i = 0; i < number; i++)
    {
        printf("%10s | %10d | %10d | %10d | %10d | %10d | %10d\n", name[i], arrival_time[i], burst_time[i], priority[i], exit_time[i], wait_time[i], tat[i]);
    }
    printf("\n\n");

    float av_tat = 0, av_wait = 0;
    for (int i = 0; i < number; i++)
    {
        av_tat += tat[i];
        av_wait += wait_time[i];
    }

    av_tat /= number;
    av_wait /= number;

    printf("average turnaround time = %f\naverage waiting time = %f", av_tat, av_wait);
}
