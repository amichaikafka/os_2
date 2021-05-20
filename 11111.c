#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <semaphore.h>

pthread_t tid[2];
pthread_mutex_t lock;
long sum = 0;
long primeCounter = 0;

int isPrime(int num)
{
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
void sum_count_prime(int num){
	if (isPrime(num))
		{
			//if do, add up it's sum, and increment counter
			pthread_mutex_lock(&lock);
			sum = sum + num;
			primeCounter++;
			pthread_mutex_unlock(&lock);
		}

}

int main(int argc, char *argv[])
{
	if(pthread_mutex_init(&lock,NULL)!=0 ){
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
	int randomPivot = atoi(argv[1]);
	int numOfRandomNumbers = atoi(argv[2]);
	

	//init rundom generator
	int random = rand();
	srand(randomPivot);

	//generate random numbers
	for (int i = 0; i < numOfRandomNumbers; i++)
	{
		random = rand();
		e=pthread_create(&(tid[i]),NULL,&sum_count_prime,NULL);
		//check if the number is prime
		if (e!=0)
		{
			printf("erro");
		}
		
		if (isPrime(random))
		{
			//if do, add up it's sum, and increment counter
			sum = sum + random;
			primeCounter++;
		}
	}
	pthread_join(tid[0],NULL);
	pthread_join(tid[1],NULL);
	//keep the out format as this!!
	printf("%ld,%ld\n", sum, primeCounter);
	pthread_mutex_destroy(&lock);

	exit(0);
}
