#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
// #include <semaphore.h>

pthread_t tid[4];
pthread_mutex_t lock;
long sum = 0;
long primeCounter = 0;
int numOfRandomNumbers;
//int arr[];
int *arr;
int random1 = 0;
int index = 0;

int randomPivot;
void *loto(void *arg)
{
    random1 = rand();
    srand(randomPivot);
    for (int i = 0; i < numOfRandomNumbers; i++)
    {
        random1 = rand();
        arr[i] = random1;
    }
}

int isPrime(int num)
{
    if (num == 0 || num == 1)
    {
        return 0;
    }
    int i;
    for (i = 2; i < sqrt(num); i++)
    {
     
        if (num % i == 0)
        {
            return 0;
        }
       
    }
    return 1;
}
void *sum_count_prime(void *arg)
{
    while (index != numOfRandomNumbers)
    {
        //  printf("hhh%d\n",index);
        /* code */

        pthread_mutex_lock(&lock);
        int num = arr[index];
        index++;
        pthread_mutex_unlock(&lock);

        if (isPrime(num))
        {

            //if do, add up it's sum, and increment counter
            pthread_mutex_lock(&lock);
            sum = sum + num;
            primeCounter++;
            pthread_mutex_unlock(&lock);
        }
    }
}

int main(int argc, char *argv[])
{
    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("erro");
        return 1;
    }

    if (argc != 3)
    {
        printf("Too few arguments ");
        printf("USAGE: ./primeCalc <prime pivot> <num of random numbers>");
        exit(0);
    }
    int e;
    randomPivot = atoi(argv[1]);
    numOfRandomNumbers = atoi(argv[2]);
    // arr[numOfRandomNumbers];
    arr = (int *)malloc(numOfRandomNumbers * sizeof(int));

    //init rundom generator
    //  random = rand();
    // srand(randomPivot);
    pthread_create(&(tid[0]), NULL, &loto, NULL);
    //generate random numbers

    for (int i = 1; i < 4; i++)
    {
        // printf("jhg\n");
        e = pthread_create(&(tid[i]), NULL, &sum_count_prime, NULL);
        //check if the number is prime
        if (e != 0)
        {
            printf("erro");
        }
    }

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    pthread_join(tid[2], NULL);
    pthread_join(tid[3], NULL);
    //keep the out format as this!!
    printf("%ld,%ld\n", sum, primeCounter);
    pthread_mutex_destroy(&lock);
    free(arr);
    exit(0);
}