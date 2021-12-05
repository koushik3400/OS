#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
pthread_t tid[2];
void *doSomeThing(void *arg)
{
    unsigned long i = 0;
    pthread_t id = pthread_self();
    if (pthread_equal(id, tid[0]))
    {
        printf("\nFirst Thread: Processing.");
    }
    else
    {
        printf("\nSecond Thread: Processing.");
    }
    for (int i = 0; i < (0xFFFFFFFF); i++)
    {
        return NULL;
    }
}
int main(void)
{
    int i = 0, err;
    while (i < 2)
    {
        err = pthread_create(&(tid[i]), NULL, &doSomeThing, NULL);
        if (err != 0)
        {
            printf("\nCannot create Thread: [%s]", strerror(err));
        }
        else
        {
            printf("\nThread Created Successfully !");
        }
        i++;
    }
    sleep(5);
    printf("\n");
    return 0;
}

/// threads 2
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
float balance = 1000;
static float least_amt = 2000;
void *deposit()
{
    float d;
    printf("\nEnter the amt to deposit:");
    scanf("%f", &d);
    balance += d;
    printf("\nDeposit Successfull\n");
}
void *withdraw()
{
    pthread_t tid2;
    printf("\nEnter the amt to withdraw:");
    float wd;
    scanf("%f", &wd);
rep:
    if (balance - wd >= least_amt)
    {
        balance -= wd;
        printf("\nWithdrawal Successfull\n");
    }
    else
    {
        printf("\nBalance Insufficient. Waiting for deposit\n");
        pthread_create(&tid2, NULL, deposit, NULL);
        pthread_join(tid2, NULL);
        goto rep;
    }
}
int main()
{
    pthread_t tid1;
    printf("Started main thread\n");
    pthread_create(&tid1, NULL, withdraw, NULL);
    pthread_join(tid1, NULL);
}
