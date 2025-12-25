#include <stdio.h>
#include <math.h>
#include <pthread.h>
#include <stdlib.h>

#define NUM_SIMULATIONS 1000000
#define MAX_THREADS 6

double S; //option price
double K; //strike price
double r; //risk free rate
double v; //volatility 
double T; // time until expiry (in years)

typedef struct {

    int simsPerThread; //= NUM_SIMULATIONS / MAX_THREADS;
    double partialSum; 
    unsigned int seed;
}threadStruct;

//argument can also be threadStruct* args, array params decay to pointers in c
    //initializes per thread arguments number of simulations, seed, partial sum and assigns them to args[i]
void createThreads(threadStruct args[]);

//casts arg to threadStruct* in order to access member variables
    //for each simluation uses randomNum() to call callPrice() and calculate partial sum
void* threadWorker(void* arg);

//simple box-muller algo implementation
    //generate random gaussian numbers
    //updates seed state via the pointer
double randomNum(unsigned int *seed);

//calculates price at expiration time and returns max
double callPrice(double S, double K, double r, double v, double T, double z);

