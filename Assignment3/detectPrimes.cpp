// =============================================================================
// You must modify this file and then submit it for grading to D2L.
// =============================================================================

/*
* Athena McNeil-Roberts
* 30042085
*/

#include "detectPrimes.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <pthread.h> 
#include <vector>
#include <atomic>

std::vector<int64_t> result;
std::atomic<bool> prime_num;
std::atomic<bool> global_finished;
int64_t num;
pthread_barrier_t barr_id;
int nThreads;
std::vector<int64_t> numbers;
int64_t perThread;

void thread_prime(int64_t tid){
    int64_t start = perThread * tid * 6 + 5;
    int64_t end = start + perThread * 6;
    int64_t max = sqrt(num);
    
    if (num < 2) { prime_num = false; return; }
    if (num <= 3) { return; } // 2 and 3 are primes
    if (num % 2 == 0) { prime_num = false; return; } // handle multiples of 2
    if (num % 3 == 0) { prime_num = false; return; } // handle multiples of 3
    // if((double)((double)sqrt(num) - max) == 0.0) {prime_num = false; return;} // no prime number is a square number

    for(int64_t i = start; i < end; i += 6){
        if(!prime_num){ // cancel thread if discovered not prime
           pthread_cancel(pthread_self());
        }
        if(i <= max){ // ensure only computing values in range
            if (num % i == 0) { prime_num = false; }
            if (num % (i + 2) == 0) { prime_num = false; }
        }else{ // return if past range 
            return;
        }
    }
}

void* thread_function(void* id){

    int64_t tid = (intptr_t) id; 
    while(1){
        if(pthread_barrier_wait(&barr_id) != 0){
        //serial work
            if(numbers.empty()){ // if reached end of numbers
                global_finished = true;
            }else{
                num = numbers.back(); // get next number
                numbers.pop_back(); // removed current num from list
                
                int div = (int)ceil((double)(sqrt(num) + 1.0 ) / 6.0); // total divisors
                perThread = (int64_t)ceil((double)div / (double)nThreads); // number of divisors per thread - rounded up
            }
        }

        pthread_barrier_wait(&barr_id);
        // parallel work

        if(global_finished){ // cancel if end of number has been reached
            pthread_cancel(pthread_self());
            pthread_exit(NULL);
        }else{  
            thread_prime(tid);
        }

        if(pthread_barrier_wait(&barr_id) != 0){
        // serial work
            if(prime_num){
                result.push_back(num); // add to results if num is prime
            }
            prime_num = true; // reset for next num
        }
    }
    pthread_exit(NULL);
}

// This function takes a list of numbers in nums[] and returns only numbers that
// are primes.
//
// The parameter n_threads indicates how many threads should be created to speed
// up the computation.
// -----------------------------------------------------------------------------
// You will most likely need to re-implement this function entirely.
// Note that the current implementation ignores n_threads. Your multithreaded
// implementation must use this parameter.
std::vector<int64_t>
detect_primes(const std::vector<int64_t> &nums, int n_threads)
{
    numbers = nums;
    prime_num = true;
    nThreads = n_threads;
    pthread_t threadPool[n_threads];

    pthread_barrier_init(&barr_id, NULL, n_threads);

    for(int i = 0; i < n_threads; i++){
        pthread_create(&threadPool[i], NULL, thread_function, (void *) (intptr_t) i);
    }

    for (int i = 0; i < n_threads; i++){
        pthread_join(threadPool[i], NULL);
    }

    return result; // return list of primes
}
