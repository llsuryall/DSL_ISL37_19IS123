#include<stdio.h>

void ToH( unsigned n,char from,char to,char spare){
	if(n==1){
		printf("Move disk 1 form %c to %c\n",from,to);
	}
	else{
		ToH(n-1,from,spare,to);
		printf("Move disk %u from %c to %c\n",n,from,to);
		ToH(n-1,spare,to,from);
	}
}

void main(){
	unsigned n=0;
	printf("Enter no. of disks - ");
	scanf("%u",&n);
	if(n>(unsigned)0){
		ToH(n,'a','c','b');
	}
}
