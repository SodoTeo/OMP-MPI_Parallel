//compute the sum of two arrays in parallel 
#include <stdio.h>      /* input, output    */
#include <omp.h>        /* openMP library   */
#include <time.h>       /* measure time */
#define N 1000000 /* if arrays not static, I'll be overflowing the stack.*/
int main(void) {
    double cpu_time_used;
    double* firstsourcearray = malloc(N * sizeof(double));
    double* secondsourcearray = malloc(N * sizeof(double));
    double* thirdarray = malloc(N * sizeof(double));
    int i;

    /* Initialize arrays firstsourcearray and secondsourcearray */
    for (i = 0; i < N; i++) {
        firstsourcearray[i] = ((double)(i)) * 2.0;
        secondsourcearray[i] = ((double)(i)) * 3.0;
    }

    /* Compute values of array thirdarray = firstsourcearray+secondsourcearray in parallel. */
    omp_set_num_threads(12); /*set to 12 cores*/
    #pragma omp parallel shared(firstsourcearray, secondsourcearray, thirdarray) private(i)
       {
        double starttime_omp, endtime_omp;
        /*time measurement*/
        starttime_omp = omp_get_wtime();

        #pragma omp for             
                for (i = 0; i < N; i++) {
                    thirdarray[i] = firstsourcearray[i] + secondsourcearray[i];
                    /*printf("%f\n", thirdarray[i]); --> if you want to print the result of addition (time consuming for printiing)*/
                }
                endtime_omp = omp_get_wtime();
                cpu_time_used = ((endtime_omp - starttime_omp));
        } /* end parallel region */
       printf("parallel computation needed %lf s\n", cpu_time_used);
}
