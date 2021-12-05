// bounded buffer

#include <stdio.h>
#include <time.h>
int max_size = 5;
int in = 0, out = 0, counter = 0;

int buf[10];
int semaphore[3];
/* semaphore[0]-> full semaphore[1]->empty semaphore[2]->binary semaphore*/

int random_number()
{
    return rand();
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

void producer(int p)
{

    wait(&semaphore[1]);
    wait(&semaphore[2]);
    buf[in] = p;
    printf("\nProduced item no.%d", in + 1);
    in = (in + 1) % max_size;
    counter++;
    signal(&semaphore[2]);
    signal(&semaphore[0]);
}

void consumer()
{
    wait(&semaphore[0]);
    wait(&semaphore[2]);
    int q = buf[out];
    printf("\nConsumed item no.%d", q);
    out = (out + 1) % max_size;

    counter--;
    signal(&semaphore[2]);
    signal(&semaphore[1]);
}

int main()
{

    int ch, id;
    semaphore[0] = 0;
    semaphore[1] = max_size;
    semaphore[2] = 1;
    srand(time(0));
    int i = 1;
    while (i <= 10)
    {
        int x = random_number();
        if (x % 2 == 0)
        {

            if (semaphore[0] == max_size)
            {
                printf("\nBuffer is full");
            }
            else
            {
                producer(in + 1);
            }
        }
        else
        {
            if (semaphore[1] == max_size)
            {
                printf("\nBuffer is empty");
            }
            else
            {
                consumer();
            }
        }
        i++;
    }
    return 0;
}
