#include <stdio.h>
#include <stdlib.h>

static int s = 1, full = 0, empty = 10, buffer[10] = {
                                            -1,
                                            -1,
                                            -1,
                                            -1,
                                            -1,
                                            -1,
                                            -1,
                                            -1,
                                            -1,
                                            -1,
};
static int common_res[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
static int count_prod = 0, count_cons = 0;

int wait(int *count)
{
    if (*count <= 0)
    {
        printf("process stalled");
        printf("\n\n");
        return (0);
    }
    else
    {
        *count = *count - 1;
        return (1);
    }
};

void signal(int *count)
{
    *count = *count + 1;
};

void producer()
{
    wait(&empty);
    wait(&s);
    buffer[count_prod % 10] = common_res[count_prod % 10];
    printf("%d : written into buffer from the common resource", buffer[count_prod % 10]);
    printf("\n\n");
    count_cons = count_prod % 10;
    count_prod += 1;
    signal(&s);
    signal(&full);
};

void consumer()
{
    int chk_full = wait(&full);
    if (chk_full == 0)
    {
        ;
    }
    else
    {
        wait(&s);
        printf("%d : read from buffer by consumer", buffer[count_cons]);
        printf("\n\n");
        buffer[count_cons] = -1;
        count_prod = (count_prod - 1) % 10;
        count_cons = (count_cons - 1) % 10;
        signal(&s);
        signal(&empty);
    }
};

int main()
{
    for (int i = 0; i < 10; i++)
    {
        int random = rand() % 100 + 1;
        if (random % 2 == 0)
        {
            printf("producer process: ");
            producer();
        }
        else
        {
            printf("consumer process: ");
            consumer();
        }
    }
}
