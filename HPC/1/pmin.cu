#include <iostream>
using namespace std;

__global__ void mini(int *a)
{
	int tid = threadIdx.x;
	int step_size = 1;
	int n_thread = blockDim.x;
	int f,s;

	while(n_thread>0)
	{
		if(tid<n_thread)
		{
			f = tid*step_size*2;
			s = f + step_size;
			if(a[f]>=a[s])
				a[f] = a[s];
		}
		step_size<<=1;
		n_thread>>=1;
	}
}

int main()
{
	int *a,*b,size,n;
	int *d_a;

	cin>>n;

	size = n*sizeof(int);

	a = (int *)malloc(size);
	b = (int *)malloc(sizeof(int));

	cudaMalloc(&d_a,size);

	for(int i=0;i<n;i++)
	{
		a[i] = rand()%100;
	}

	for(int i=0;i<n;i++)
	{
		cout<<a[i]<<" ";
	}

	cudaMemcpy(d_a,a,size,cudaMemcpyHostToDevice);

		clock_t start = clock();


	mini<<<1,n/2>>>(d_a);

	cout<<"time: "<<(float)(clock()-start)/CLOCKS_PER_SEC<<endl;

	cudaMemcpy(b,d_a,size,cudaMemcpyDeviceToHost);

	cout<<"min is :"<<b[0];

	return 0;
}