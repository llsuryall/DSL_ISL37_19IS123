#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<ctype.h>
#include<math.h>
#define size 20

double s[size];
int top=-1;

_Bool is_operator(char c){
	switch(c){
		case '+':
		case '-':
		case '*':
		case '/':
		case '^':
			return true;
		default:
			return false;
	}
}

void push(double temp){
	if(top<size-1){
		s[++top]=temp;
	}
}

double pop(){
	if(top>-1){
		return s[top--];
	}
	else{
		return 0;
	}
}

void main(){
	unsigned short approx_size=0;
	printf("Enter the approx size of expression - ");
	scanf("%hu%*c",&approx_size);
	char * str = malloc(approx_size);
	printf("Enter the expression - ");
	fgets(str,approx_size,stdin);
	unsigned i=0;
	double temp=0,op1=0,op2=0;
	if(!isalpha(str[i])){ printf("Invalid postfix expression!\n");return;}
	while(str[i]!=0){
		if(is_operator(str[i])){
			op2=pop();
			op1=pop();
			switch(str[i]){
				case '+':
					op1=op2+op1;break;
				case '-':
					op1=op1-op2;break;
				case '*':
					op1=op1*op2;break;
				case '/':
					op1=op1/op2;break;
				case '^':
					op1=pow(op1,op2);break;
			}
			push(op1);
		}
		else if(isalpha(str[i])){
			printf("Enter the value of %c - ",str[i]);
			scanf("%lf",&temp);
			push(temp);
		}
		i++;
	}
	printf("%lf\n",pop());
	free(str);
}
