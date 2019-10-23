#include<stdio.h>
#define SIZE 2

__global__ void MatrixMul(int a[], int b[], int c[], int n) 
{ int row = threadIdx.y + blockIdx.y * blockDim.y;
    int col = threadIdx.x + blockIdx.x * blockDim.x;
    int sum = 0;
    for(int j = 0; j < n; j++) {
        sum += a[row * n + j] * b[j * n + col];
    }
    c[n*row + col] = sum;
}
int main() 
{    
	time_t t;
	srand((unsigned) time(&t));
	
	int *a, *b, *c;
	
	a = (int*)malloc(SIZE * SIZE * sizeof(int));
	b = (int*)malloc(SIZE * SIZE * sizeof(int));
	c = (int*)malloc(SIZE * SIZE * sizeof(int));
	
    	for(int i = 0; i < SIZE ; i++) 
    	{
        	for(int j = 0; j < SIZE ; j++) 
        	{
        		*(a + i*SIZE + j) = i;
        		*(b + i*SIZE + j) = i+1;
        	}
    	}
    
	int *d_a, *d_b, *d_c;

    	cudaMalloc(&d_a, SIZE * SIZE * sizeof(int));
    	cudaMalloc(&d_b, SIZE * SIZE * sizeof(int));
    	cudaMalloc(&d_c, SIZE * SIZE * sizeof(int));
    	
    	cudaMemcpy(d_a, a, SIZE * SIZE * sizeof(int), cudaMemcpyHostToDevice);
    	cudaMemcpy(d_b, b, SIZE * SIZE * sizeof(int), cudaMemcpyHostToDevice);
    
    dim3 grid_dim(SIZE, SIZE, 1);
    MatrixMul<<<grid_dim, 1>>> (d_a, d_b, d_c, SIZE);
    
    	
    	cudaDeviceSynchronize();

    	cudaMemcpy(c, d_c, SIZE * SIZE * sizeof(int), cudaMemcpyDeviceToHost);
    
    	printf("1st matrix: ");
	for (int i = 0; i < SIZE; i++)
	{
		for(int j = 0; j < SIZE; j++)
		{
			printf("%d ", *(a + i*SIZE + j));
		}
		printf("");
	}
	printf("2nd matrix: ");
	for (int i = 0; i < SIZE; i++)
	{
		for(int j = 0; j < SIZE; j++)
		{
			printf("%d ", *(b + i*SIZE + j));
		}
		printf("");
	}
	printf("Product: ");
	for (int i = 0; i < SIZE; i++)
	{
		for(int j = 0; j < SIZE; j++)
		{
			printf("%d ", *(c + i*SIZE + j));
		}
		printf("");
	}

	cudaFree(d_a);
	cudaFree(d_b);
	cudaFree(d_c);
	
	free(a);
	free(b);
	free(c);

   
    	return 0;
}

