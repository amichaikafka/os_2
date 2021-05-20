#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
// #include <semaphore.h>
#define NUM_T 10
#define NUM_T_L 2
pthread_t tid[NUM_T];
pthread_mutex_t lock;
long sum = 0;
long primeCounter = 0;
int numOfRandomNumbers;
//int arr[];
int *arr;
int random1 = 0;
int index = 0;
int i1 = 0;
int randomPivot;
void *loto(void *arg)
{
    random1 = rand();
    srand(randomPivot);
    for (i1 = 0; i1 < numOfRandomNumbers; i1++)
    {
        random1 = rand();
        if (!(random1!=2&&random1%2==0))
        {
           arr[i1] = random1;
        }
        
        // arr[i1] = random1;
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
        while (index > i1)
        {
            /* code */
        }

        //   printf("hhh%d\n",index);
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
    for (int i = 0; i < NUM_T_L; i++)
    {
        pthread_create(&(tid[0]), NULL, &loto, NULL);
    }
  
    //generate random numbers

    for (int i = NUM_T_L; i < NUM_T; i++)
    {
        // printf("jhg\n");
        e = pthread_create(&(tid[i]), NULL, &sum_count_prime, NULL);
        //check if the number is prime
        if (e != 0)
        {
            printf("erro");
        }
    }
for (int i = 0; i < NUM_T; i++){
     pthread_join(tid[i], NULL);
}
    // pthread_join(tid[0], NULL);
    // pthread_join(tid[1], NULL);
    // pthread_join(tid[2], NULL);
    // pthread_join(tid[3], NULL);
    // pthread_join(tid[4], NULL);
    // pthread_join(tid[5], NULL);
    // pthread_join(tid[6], NULL);
    // pthread_join(tid[7], NULL);
    // pthread_join(tid[8], NULL);
    // pthread_join(tid[9], NULL);
    // pthread_join(tid[2], NULL);
    // pthread_join(tid[3], NULL);
    //keep the out format as this!!
    printf("%ld,%ld\n", sum, primeCounter);
    pthread_mutex_destroy(&lock);
    free(arr);
    exit(0);
}