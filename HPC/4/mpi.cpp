#include<bits/c++.h>
#include<iostream>
#include<cstdio>
#include<time.h>
#include<chrono>
#include<mpi.h>
#include <unistd.h>

using namespace std;
using namespace std::chrono;

void bisearch(int *a,int l,int r,int key,int rank)
{
	int m ;
	while(l<=r)
	{
		m = (l+r)/2;
		if(key==a[m])
		{
			cout<<"element is found by the process "<<rank+1<<endl;
			return;
		}
		else if(key<a[m])
			r = m-1;
		else if(key>a[m])
			l = m+1;
	}
	cout<<"not found"<<endl;
}

int main(int argc, char **argv)
{	
	int n=8000;
	int key = 4500;
	int a[n];
	double t[4];

	for(int i=0;i<n;i++)
		a[i] = i+1;

	int rank,size;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,rank);
	MPI_Comm_size(MPI_COMM_WORLD,size);

	size = n/4;

	double start = MPI_Wtime();

	bisearch(a,rank*size,(rank+1)*size-1,key,rank);

	double end = MPI_Wtime();

	cout<<"time for process "<<rank+1<<" is "<<(end-start)*1000<<endl;
	t[rank] = end;

	MPI_Finalize();

	return 0;
}