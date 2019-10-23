#include<iostream>
#include<mpi.h>
#include<bits/stdc++.h>
#include<cstdio>
#include<unistd.h>

using namespace std;

void printTree(int tree[],int start,int end,int my_id)
{
if(start>end)
return;
printTree(tree,2*start+1,end,my_id);
cout<<"id:"<<my_id<<" "<<tree[start];
printTree(tree,2*start+2,end,my_id);
}

void builTree(int start,int end,int tree[],int k,int offset,int n)
{
if(start<=end && k<=n)
{
int mid = (start+end+1)/2;
tree[k] = mid+offset;
builTree(start,mid-1,tree,2*k+1,offset,n);
builTree(mid+1,end,tree,2*k+2,offset,n);
}
}

int main(int argc,char *argv[])
{
int n=10;
int tree[n],slave[n];
int my_id,n_proc,received,send_data_tag,children;
double start,finish;

MPI_Status status;

start = MPI_Wtime();

MPI_Init(&argc,&argv);
MPI_Comm_rank(MPI_COMM_WORLD,&my_id);
MPI_Comm_size(MPI_COMM_WORLD,&n_proc);

children = n_proc;

if(my_id==0)
{
for(int i=0;i<children;i++)
{
int offset = i*n;
builTree(0,n,tree,0,offset,n);
MPI_Send(&n,1,MPI_INT,i,send_data_tag,MPI_COMM_WORLD);
MPI_Send(&tree,n,MPI_INT,i,send_data_tag,MPI_COMM_WORLD);
}
}

MPI_Recv(&received,1,MPI_INT,0,send_data_tag,MPI_COMM_WORLD,&status);
MPI_Recv(&slave,received,MPI_INT,0,send_data_tag,MPI_COMM_WORLD,&status);

printTree(slave,0,n-1,my_id);

finish = MPI_Wtime();
cout<<"time : "<<(finish-start);

MPI_Finalize();

return 0;
}