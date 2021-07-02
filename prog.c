#include <stdio.h>      /* input, output    */
#include <omp.h>        /* openMP library   */
#include <time.h>       /* measure time */

#define N 1000000     /* if sourcearray not static, I'll be overflowing the stack.*/
                        /* > ~10^6 elements is a lot for most systems.*/


void forloop(void);


int
main(void)    
{
  double *sourcearray = malloc(N*sizeof(double));
  /* worksharing: for loop */
  forloop();

  return(0);
}

/*=============================================================*/
/*=============================================================*/

void forloop(void){
  /*do a for loop sequentially and in parallel; measure each times */


  printf("=====================\n");
  printf("FOR LOOP\n");
  printf("=====================\n\n");

  long i;    
  clock_t start, end;
  double cpu_time_used;

  static double sourcearray[N];    


  /*============*/
  /*measure time*/
  /*============*/

  start=clock();

  for (i=0; i<N; i++){
    sourcearray[i] = ((double) (i)) * ((double) (i))/2.2034872;
  }

  end = clock();
  cpu_time_usedn = ((double) (end - start)) / CLOCKS_PER_SEC;

  printf("Non-parallel needed %lf s\n", cpu_time_usedn);




  /*===============*/
  /*parallel region*/
  /*===============*/
omp_set_num_threads(12);
#pragma omp parallel 
  /*need to specify num_threads, when OMP_DYNAMIC=true to make sure 12 are used.*/
  {
   

    double starttime_omp, endtime_omp;
    /*time measurement*/
    starttime_omp=omp_get_wtime();

    int procs, maxt, nt, id;

    procs = omp_get_num_procs();        // number of processors in use
    maxt = omp_get_max_threads();       // max available threads
    nt = omp_get_num_threads();
    id = omp_get_thread_num();

    printf("num threads forloop %d from id %d, procs: %d, maxthrds: %d\n", nt, id, procs, maxt);


#pragma omp for  
    for (i=0; i<N; i++){
      sourcearray[i] = ((double) (i)) * ((double) (i))/2.2034872;
    }


    endtime_omp = omp_get_wtime();
    cpu_time_used = ((endtime_omp - starttime_omp)) ;



  } /* end parallel region */
   printf("parallel needed %lf s\n", cpu_time_used);


}