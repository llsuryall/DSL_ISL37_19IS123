#include<stdio.h>
#include<stdlib.h>

int binary_search(int * ar, int l, int r, int x) 
{
	if(r>=l){
		int mid=l+(r-l)/2;
		if(ar[mid] == x)
			return mid;
		else if(ar[mid] > x)
			return binary_search(ar, l, mid - 1, x);
		else
			return binary_search(ar, mid + 1, r, x);
	}
	return -1;
}

int cmp_int(const void * a,const void * b){
	return *(int*)a-*(int*)b;
}

void main(){
	int n=0;
	printf("Enter no of elements for new integer array - ");
	scanf("%d",&n);
	int * ar=malloc(n*sizeof(int));
	printf("Enter the elements - \n->");
	for(int i=0;i<n;i++){
		scanf("%d",ar+i);
	}
	printf("The enetered array -\n");
	for(int i=0;i<n;i++){
		printf("%d ",*((int*)ar+i));
	}
	printf("\n");
	qsort(ar,n,sizeof(int),cmp_int);
	printf("The sorted array -\n");
	for(int i=0;i<n;i++){
		printf("%d ",*((int*)ar+i));
	}
	printf("\n");
	int el=0;
	printf("Enter an integer to search - ");
	scanf("%d",&el);
	int pos=binary_search(ar,0,n-1,el);
	if(pos==-1){
		printf("Element not found in the array!\n");
	}
	else{
		printf("Element was found at index(0) - %d\n",pos);
	}
}
