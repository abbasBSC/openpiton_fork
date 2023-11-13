//**************************************************************************
// Matrix multiplication benchmark
//--------------------------------------------------------------------------
//
// This benchmark execute a multiplication of two matrix and writes the result into another matrix. 
// The input data (and reference data) should be generated using the matmul_gendata.pl perl script and 
// dumped to a file named dataset.h

#include "util.h"
//#include "cache_metrics.h"

//--------------------------------------------------------------------------
// Input/Reference Data

#include "dataset.h"
#define N 1

//--------------------------------------------------------------------------
// matmul function

void matmul(int n, int a[], int b[], int c[])
{
   int i, j, k;
      
   for ( j = 0; j < n; j++ ) {
      for ( k = 0; k < n; k++ )  {
         for ( i = 0; i < n; i++ ) {
            c[i + j*n] += a[j*n + k] * b[k*n + i];
         }
      }
   }

}

//--------------------------------------------------------------------------
// Main

int main( int argc, char* argv[] )
{
  int results_data[ARRAY_SIZE] = {0};

  //reset_L2_metrics(0);
  unsigned long cycle = read_csr(mcycle);
  unsigned long instr = read_csr(minstret); 
  //init_L2_metrics(0);

  for (int i=0;i<N;i++){
    matmul( DIM_SIZE, input1_data, input2_data, results_data );
  }

  //stop_L2_metrics(0);
  cycle = read_csr(mcycle) - cycle;
  instr = read_csr(minstret) - instr;
  
  printf("Cycles: %d \n",cycle);
  printf("Instructions: %d \n",instr);
  //print_L2_metrics(0);

  // Check the results
  int i = verify( ARRAY_SIZE, results_data, verify_data );
  exit(i);	  
	 
}
