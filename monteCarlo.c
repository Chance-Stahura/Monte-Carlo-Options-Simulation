/*An option is a financial contract that gives you the right, but not an 
obligation to buy a stock at a fixed price on a fixed future date

    S = price of the stock today
    K = price you are able to buy the stock for later
    r = interest rate used to discount future money today
    v = how much the stock price tends to fluctuate
    T = how long the option lasts (in years)

    no mutex needed as these variables are read only, they are initialized
    once and never modified afterwards

    each thread writes its own partial sum and seed
*/

#include "monteCarlo.h"

double randomNum(unsigned int *seed) {
    
    double x = 0.0;
    double y = 0.0;
    double euclidianSquare = 0.0;

    do {
        x = 2.0 * rand_r(seed) / (double)RAND_MAX - 1;
        y = 2.0 * rand_r(seed) / (double)RAND_MAX - 1;
        euclidianSquare = x * x + y * y;
    } while(euclidianSquare >= 1.0 || euclidianSquare == 0.0);

    return x * sqrt(-2 * log(euclidianSquare) / euclidianSquare);
}

void* threadWorker(void* arg) {

    threadStruct* ptr = (threadStruct*)arg;
    ptr->partialSum = 0.0;
    for(int i = 0; i < ptr->simsPerThread; i++) {
        double z = randomNum(&ptr->seed);
        double payoff = callPrice(S, K, r, v, T, z);
        ptr->partialSum += payoff;
    }
    return NULL;
}

double callPrice(double S, double K, double r, double v, double T, double z) {

    double priceAtExpiration = S * exp((r - 0.5 * v * v) * T + v * sqrt(T) * z);
    return fmax(priceAtExpiration - K, 0);
}

void createThreads(threadStruct args[]) { 

    pthread_t threads[MAX_THREADS];
    int rem = NUM_SIMULATIONS % MAX_THREADS; //remainder simulations
    int baseSimulations = NUM_SIMULATIONS / MAX_THREADS; //gives base number of simulations per thread
    for(int i = 0; i < MAX_THREADS; i++) {
        unsigned int baseSeed = (unsigned int)time(NULL) ^ (i * 0x9e3779b9);
        args[i].simsPerThread = baseSimulations + (i < rem ? 1: 0); //adds reamaining simulations to the first 'rem' threads
        args[i].seed = baseSeed + i;
        args[i].partialSum = 0.0;
        //(name, attribute, function, argument);
        pthread_create(&threads[i], NULL, threadWorker, &args[i]);
    }
     for(int i = 0; i < MAX_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
}

int main () {

    threadStruct args[MAX_THREADS];
    double finalPrice = 0.0, totalPayoff = 0.0, avgPayoff = 0.0;
    printf("Welcome to the Monte Carlo Options Simulation\n");
    printf("Initial option price: ");  scanf("%lf", &S);
    printf("Strike price: ");  scanf("%lf", &K);
    printf("Risk free rate: "); scanf("%lf", &r);
    printf("Volatility: "); scanf("%lf", &v);
    printf("Time (in years) until expiration: "); scanf("%lf", &T);

    createThreads(args);
    for(int i = 0; i < MAX_THREADS; i++) {
        totalPayoff += args[i].partialSum;
    }
    avgPayoff = totalPayoff / NUM_SIMULATIONS;
    finalPrice = exp(-r * T) * avgPayoff;
    printf("Final Price: %lf\n", finalPrice);

    return 0;
}