#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
void mergesort(int a[], int i, int j);
void merge(int a[], int i1, int j1, int i2, int j2);
void pMergeSort(int a[], int l, int r);

#define SIZE 5

int main(){
	int *a, *b;
	a = (int *)malloc(SIZE*sizeof(int));
	b = (int *)malloc(SIZE*sizeof(int));
	for(int i = 0;i < SIZE;i ++){
		a[i] = rand() % 1516;
		b[i] = a[i];
	}
	
	clock_t timer = clock();
	mergesort(a, 0, SIZE-1);
  // for(int i=0;i<SIZE;i++)
  //   cout<<a[i]<<" ";
  // cout<<endl;
	cout << " Serial sorting time : " << (float)(clock()-timer) / CLOCKS_PER_SEC;
	cout<<endl;
	timer = clock();
	pMergeSort(b, 0, SIZE-1);
  //   for(int i=0;i<SIZE;i++)
  //   cout<<b[i]<<" ";
  // cout<<endl;

	cout << " Parallel sorting time : " << (float)(clock()-timer) / CLOCKS_PER_SEC;

	//Validation
	for(int i = 0;i < SIZE;i ++){
		if(a[i] != b[i]){
			cout << "Error";
			break;
		}
	}
}

void mergesort(int a[], int i, int j){
	
	int mid;
	
	if(i < j)
	{
		mid = (i+j)/2;
		mergesort(a, i, mid);
		mergesort(a, mid+1, j);
		merge(a, i, mid, mid+1, j);
	}
}

void pMergeSort(int a[], int l, int r)
{
    if(l<r)
    {
        int m=(l+r)/2;
        #pragma omp parallel sections num_threads(2)
        {
            #pragma omp section
            {
                pMergeSort(a,l,m);
            }
            #pragma omp section
            {
                pMergeSort(a,m+1,r);
            }
        }
        merge(a,l,m,m+1,r);
    }
}
void merge(int a[], int i1, int j1, int i2, int j2){
	int temp[SIZE];
	int i, j, k;
	i = i1;
	j = i2;
	k = 0;
	
	while(i<=j1 && j<=j2){
		if(a[i]<a[j])
			temp[k++] = a[i++];
		else
			temp[k++] = a[j++];
	}
	
	while(i<=j1)
		temp[k++] = a[i++];
	while(j<=j2)
		temp[k++] = a[j++];
	
	for(i=i1, j=0;i<=j2;i ++, j ++){
		a[i] = temp[j];
	}
}
