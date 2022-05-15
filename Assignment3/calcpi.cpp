// ======================================================================
// You must modify this file and then submit it for grading to D2L.
// ======================================================================
//
// count_pi() calculates the number of pixels that fall into a circle
// using the algorithm explained here:
//
// https://en.wikipedia.org/wiki/Approximations_of_%CF%80
//
// count_pixels() takes 2 paramters:
//  r         =  the radius of the circle
//  n_threads =  the number of threads you should create
//
// Currently the function ignores the n_threads parameter. Your job is to
// parallelize the function so that it uses n_threads threads to do
// the computation.

/*
* Athena McNeil-Roberts
*/

#include "calcpi.h"
#include <pthread.h> 
#include <vector>
#include <cstdio>
#include <iostream>
#include <cmath>

int rad;
int perThread;
struct threadInput{
    int start;
    int finish;
    uint64_t count;
};

void* thread_loop(void* param){
    struct threadInput * myParam = ((struct threadInput *) param);

    double rsq = double(rad) * rad;
    uint64_t count = 0;
    for(double x = myParam->start + 1 ; x <= myParam->finish ; x ++){
        for(double y = 0 ; y <= rad ; y ++){
            if(x <= rad){ // ensure only computing values in range
                if( x*x + y*y <= rsq) count ++;
            }
        }
    }
    myParam->count = count; // store the count for this thread
    pthread_exit(NULL);
    return NULL;
}



uint64_t count_pixels(int r, int n_threads)
{
    rad = r;
    double temp = (double)r / (double)n_threads; 
    perThread = (int)ceil(temp); // number per thread - rounded up
    uint64_t count = 0;

    pthread_t threadPool[n_threads];
    threadInput inputs[n_threads];

    for(int i = 0; i < n_threads; i++){
        inputs[i].start = (i*perThread);
        inputs[i].finish = (i*perThread) + perThread;

        pthread_create(&threadPool[i], NULL, thread_loop, &inputs[i]);
    }

    for (int i = 0; i < n_threads; i++){
        pthread_join(threadPool[i], NULL);
        count = count + inputs[i].count; // add up all threads counts
    }
    return count * 4 + 1;
}

