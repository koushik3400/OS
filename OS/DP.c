// dining philosopher
#include <stdio.h>
#include <time.h>
int ph[5];
int semaphore[6];
/* 5 forks for 4 philosophers
 */
void state()
{
    int i;
    for (i = 0; i < 4; i++)
    {
        switch (ph[i])
        {
        case 0:
            printf("\nphilosopher%d is thinking", i);
            break;
        case 1:
            printf("\nphilosopher %d is feeling hungry", i);
            break;
        case 2:
            printf("\nphilosopher %d is eating", i);
            break;
        }
    }
}

void wait(int *S)
{
    while ((*S) <= 0)
        ;
    (*S)--;
}
void signal(int *S)
{
    (*S)++;
}
void philosopher(int p)
{
    ph[p] = 1;
    state();
    printf("\n\n");
    wait(&semaphore[p]);
    wait(&semaphore[(p + 1) % 5]);

    ph[p] = 2;
    state();
    printf("\n\n");
    signal(&semaphore[p]);
    signal(&semaphore[(p + 1) % 5]);

    ph[p] = 0;
    state();
    printf("\n\n");
}
int random_number()
{
    return rand();
}

int main()
{
    int i;
    for (i = 0; i < 6; i++)
    {
        semaphore[i] = 1;
    }
    for (i = 0; i < 5; i++)
    {
        ph[i] = 0;
    }
    srand(time(0));
    i = 1;
    state();
    printf("\n\n");
    while (i <= 5)
    {
        int x = random_number();
        int ch = x % 5;
        switch (ch)
        {
        case 0:
            philosopher(0);
            printf("\n\n");
            break;
        case 1:
            philosopher(1);
            printf("\n\n");
            break;
        case 2:
            philosopher(2);
            printf("\n\n");
            break;
        case 3:
            philosopher(3);
            printf("\n\n");
            break;
        case 4:
            philosopher(4);
            printf("\n\n");
            break;
        }
        i++;
    }
    return 0;
}
