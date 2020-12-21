#include<stdio.h>

unsigned gcd(unsigned a,unsigned b){
	unsigned rem=a%b;
	if(rem==0){
		return b;
	}
	else{
		return gcd(b,rem);
	}
}

void main(){
	unsigned a=0,b=0;
	printf("Enter 2 +ve nos to calculate gcd -\n->");
	scanf("%u%u",&a,&b);
	printf("GCD of %u and %u is %u\n",a,b,gcd(a,b));
}
