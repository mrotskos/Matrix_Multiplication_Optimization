#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define MAX_ITER 10
#define sub2int(i, j, n) ((n)*(i) + (j)) // 2D index to 1D index

void matrixMult(float * const C,         // Output matrix
                const float * const A,   // Input matrix A
                const float * const B,   // Input matrix B
                const int n) {           // Matrix size
    
    //const int s = 2048; // Block size    

    //for(int i = 0; i < n * n; i++) C[i] = 0.0; // Initialize C to 0 (important!
    /*
    // Matrix multiplication with blocking
    for(int i_out = 0; i_out < n; i_out += s) {
        for(int k_out = 0; k_out < n; k_out += s) {
            for(int j_out = 0; j_out < n; j_out += s) {
                for(int i_in = 0; i_in < s; i_in++) {
                    for(int k_in = 0; k_in < s; k_in++) {
                        C[sub2int(i_out + i_in, k_out + k_in, n)] = 0;
                        for(int j_in = 0; j_in < s; j_in++) {
                            C[sub2int(i_out + i_in, j_out + j_in, n)] += A[sub2int(i_out + i_in, k_out + k_in, n)] * B[sub2int(k_out + k_in, j_out + j_in, n)];
                        }
                    }
                }
            }
        }
    }
    */

    /*

    // Matrix multiplication with blocking
    for (int i0 = 0; i0 < n; i0 += s) {
        for (int k0 = 0; k0 < n; k0 += s) {
            for (int j0 = 0; j0 < n; j0 += s) {
                for (int i = i0; i < i0 + s; i++) {
                    for (int k = k0; k < k0 + s; k++) {
                        for (int j = j0; j < j0 + s; j++) {
                            C[sub2int(i, j, n)] += A[sub2int(i, k, n)] * B[sub2int(k, j, n)];
                        }
                    }
                }
            }
        }
    }
    */

    

    // Original matrix multiplication
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            C[sub2int(i, j, n)] = 0;
            for(int k = 0; k < n; k++) {
                C[sub2int(i, j, n)] += A[sub2int(i, k, n)] * B[sub2int(k, j, n)];
            }
        }
    }
}


int main() {
    double time = 0.0;
    
    const int n = 2048;
    float *A = (float *)malloc(n * n * sizeof(float));
    float *B = (float *)malloc(n * n * sizeof(float));
    float *C = (float *)malloc(n * n * sizeof(float));

    /* Initialize matrices */
    for (int i = 0; i < n * n; i++) {
        A[i] = i;
        B[i] = i;
    }

    struct timeval start, end;

    /* compute matrix multiplication */
    for (int it = 0; it < MAX_ITER; it++) {
      gettimeofday(&start, NULL);
      matrixMult( C, A, B, n );
      gettimeofday(&end, NULL);

      time = ( (end.tv_sec  - start.tv_sec)  * 1000.0 +  /* sec to ms */
               (end.tv_usec - start.tv_usec) / 1000.0 ); /* us to ms */

      printf("Iter: %d Time: %f\n", it, time);
    }

    // print result
    printf("C[0][4] = %f\n", C[4]);

    free(A);
    free(B);
    free(C);

    return 0;
}