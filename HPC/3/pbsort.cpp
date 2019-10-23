#include <omp.h>
#include<bits/stdc++.h>
#include<iostream>
#include<ctime>

using namespace std;

void bsort(int *a,int n)
{
	for(int i=0;i<n;i++)
	{
		bool f = true;
		for(int j=0;j<n-1;j++)
		{
			if(a[j]>a[j+1])
			{
				swap(a[j],a[j+1]);
				f = false;
			}
		}
		if(f)
			break;
	}
}

void pbsort(int *a,int n)
{
	omp_set_num_threads(2);

	for(int i=0;i<n;i++)
	{
		int first = i%2;
		#pragma omp parallel for default(none), shared(a,first,n)
	
		for(int j=first;j<n-1;j+=2)
		{
			if(a[j]>a[j+1])
			{
				swap(a[j],a[j+1]);
			}
		}
	}
}

int main()
{
	int *a,*b;
	int n;
	cin>>n;

	a = (int *)malloc(n*sizeof(int));
	b = (int *)malloc(n*sizeof(int));

	for(int i=0;i<n;i++)
	{
		a[i] = b[i] = rand()%100;
	}

	clock_t timer = clock();
	bsort(a,n);
	cout<<"serial : "<<(clock()-timer)/CLOCKS_PER_SEC<<endl;

	timer = clock();
	pbsort(b,n);
	cout<<"parallel : "<<(clock()-timer)/CLOCKS_PER_SEC<<endl;

	// for(int i=0;i<n;i++)
	// 	cout<<a[i]<<" ";

	// cout<<endl;

	// for(int i=0;i<n;i++)
	// 	cout<<b[i]<<" ";

	// cout<<endl;

	return 0;
}