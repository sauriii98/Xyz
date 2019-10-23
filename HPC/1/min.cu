#include <iostream>
#include<ctime>
using namespace std;

__global__ void mini(int *a,int *b,int n)
{
	int tid = threadIdx.x;
	int minn = INT_MAX;
	for(int i=0;i<min(tid+256,n);i++)
	{
		if(minn>a[i])
			minn = a[i];
	}
	b[tid] = minn;
}

int main()
{
	int *a,*b,size,n;
	int *d_a,*d_b;

	cin>>n;
	size = n*sizeof(int);

	a = (int*)malloc(size);
	b = (int *)malloc(sizeof(int));

	cudaMalloc(&d_a,size);
	cudaMalloc(&d_b,sizeof(int));

	for(int i=0;i<n;i++)
	{
		a[i] = rand()%100;
	}

	cudaMemcpy(d_a,a,size,cudaMemcpyHostToDevice);

	clock_t start = clock();

	mini<<<1,n>>>(d_a,d_b,n);

	cout<<"time: "<<(float)(clock()-start)/CLOCKS_PER_SEC;

	cudaMemcpy(b,d_b,sizeof(int),cudaMemcpyDeviceToHost);

	cout<<"min is:"<<b[0];

	return 0;
}