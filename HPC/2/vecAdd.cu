#include <iostream>
usingb namespace std;

__global__ void addi(int *a,int *b,int *c,int n)
{
	int tid = threadIdx.x + blockIdx.x*blockDim.x;

	if(tid<n)
		c[tid] = a[tid] + b[tid];
}

int main()
{
	int *a,*b,*c;
	int n;
	int *d_a,*d_b,*d_c;	

	cin>>n;

	int size = n*sizeof(int);

	a = (int *)malloc(size);
	b = (int *)malloc(size);
	c = (int *)malloc(size);

	for(int i=0;i<n;i++)
	{
		a[i] = i;
		b[i] = i+1;
		c[i] = 0;
	}

	cudaMalloc(&d_a,size);
	cudaMalloc(&d_b,size);
	cudaMalloc(&d_c,size);

	cudaMemcpy(d_a,a,size,cudaMemcpyHostToDevice);
	cudaMemcpy(d_b,b,size,cudaMemcpyHostToDevice);
	cudaMemcpy(d_c,c,size,cudaMemcpyHostToDevice);

	addi<<<2,n/2>>>(d_a,d_b,d_c,n);

	cudaMemcpy(c,d_c,size,cudaMemcpyDeviceToHost);

	for(int i=0;i<n;i++)
	{
		cout<<a[i]<<" + "<<b[i]<<"  = "<<c[i]<<endl; 
	}

	return 0;
}