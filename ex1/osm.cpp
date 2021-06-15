#include "osm.h"
#include <iostream>
#include <sys/time.h>

static const int ERR = -1;
static const int DIF_ITERATION_NUM = 1000;
static const int UNROLLING_FACTOR = 10;
static const int CONVERT_CONST_SEC_TO_NSEC = 1000000000;
static const int CONVERT_CONST_MSEC_TO_NSEC = 1000;

/**
 * Resolving some issues regarding to the 'iterations' argument:
 * 1) If iterations has an invalid value - sets it to default value.
 * 2) If iterations is not a multiplication of the unrolling factor - rounds it up so it will be.
 * @param iterations: a non-negative int used in the time measuring process.
 */
void fixIterations(unsigned int& iterations){
    int roundVal = 0;

    // Setting 'iterations' to default if it has an invalid value:
    if(iterations == 0){
        iterations = DIF_ITERATION_NUM;
    }

    // Rounding up 'iterations' to be a multiple of the unrolling factor:
    if(iterations % UNROLLING_FACTOR != 0){
        roundVal = 1;
    }
    iterations = (iterations / UNROLLING_FACTOR) * UNROLLING_FACTOR + (roundVal * UNROLLING_FACTOR);
}


/**
 * Calculates a single operation executing time (in nanoseconds).
 * @param start: start time.
 * @param end: end time.
 * @param iterations: Number of times the executing time was measured.
 * @return: Operation executing time (in nanoseconds)
 */
double calcOpTime(timeval start, timeval end, unsigned int iterations){
    double totalTimeNano = 0;            // The total time of the check (in nanoseconds).

    totalTimeNano = (end.tv_sec - start.tv_sec) * CONVERT_CONST_SEC_TO_NSEC +
                    (end.tv_usec - start.tv_usec) * CONVERT_CONST_MSEC_TO_NSEC;

    return totalTimeNano / iterations;
}

double osm_operation_time(unsigned int iterations){
    int tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7, tmp8, tmp9, tmp10;
    struct timeval start, end;

    fixIterations(iterations);

    // Measuring times:
    if (!gettimeofday(&start, NULL)){
        for(int i = 0; i < static_cast<int>(iterations); i+=UNROLLING_FACTOR){
            tmp1++;
            tmp2++;
            tmp3++;
            tmp4++;
            tmp5++;
            tmp6++;
            tmp7++;
            tmp8++;
            tmp9++;
            tmp10++;
        }
        if (!gettimeofday(&end, NULL))
        {
            return calcOpTime(start, end, iterations);
        }
    }
    return ERR;
}


/**
 * We are going to test the run-time of this function.
 */
void some_func(){}

double osm_function_time(unsigned int iterations){
    struct timeval start, end;

    fixIterations(iterations);

    // Measuring times:
    if (!gettimeofday(&start, NULL))
    {
        for(int i = 0; i < static_cast<int>(iterations); i+=UNROLLING_FACTOR){
            some_func();
            some_func();
            some_func();
            some_func();
            some_func();    // 5'th time
            some_func();
            some_func();
            some_func();
            some_func();
            some_func();    // 10'th time
        }
        if (!gettimeofday(&end, NULL))
        {
            return calcOpTime(start, end, iterations);
        }
    }
    return ERR;
}

double osm_syscall_time(unsigned int iterations){
    struct timeval start, end;

    fixIterations(iterations);

    // Measuring times:
    if (!gettimeofday(&start, NULL))
    {
        for(int i = 0; i < static_cast<int>(iterations); i+=UNROLLING_FACTOR){
            OSM_NULLSYSCALL;
            OSM_NULLSYSCALL;
            OSM_NULLSYSCALL;
            OSM_NULLSYSCALL;
            OSM_NULLSYSCALL;    // 5'th time
            OSM_NULLSYSCALL;
            OSM_NULLSYSCALL;
            OSM_NULLSYSCALL;
            OSM_NULLSYSCALL;
            OSM_NULLSYSCALL;    // 10'th time
        }
        if (!gettimeofday(&end, NULL))
        {
            return calcOpTime(start, end, iterations);
        }
    }
    return ERR;
}
