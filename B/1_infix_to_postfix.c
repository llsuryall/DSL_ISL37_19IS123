#include<stdio.h>
#include<stdlib.h>
#include<../generic_stack.c>
#include<mem_lib.h>
#include<ctype.h>
#include<stdbool.h>

_Bool isoperator(char som){
	switch(som){
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

unsigned short precedence(char som){
	switch(som){
		case '^':
			return 4;
		case '*':
		case '%':
		case '/':
			return 3;
		case '+':
			return 2;
		case '-':
			return 1;
		default:
			return 0;
	}
}

void main(){
	unsigned n=0;
	printf("Enter approx no. of characters(maximum) in the infix expression-");
	scanf("%u",&n);
	scanf("%*c");
	if(n>(unsigned)0){
		char * infix_expr=malloc(n),* postfix_expr=malloc(2*n);
		Stack * operators = createStack(n,1);
		mal_error(infix_expr,n, );
		printf("Enter the infix expression-\n->");
		fgets(infix_expr,n,stdin);
		unsigned i=0,j=0;
		_Bool som=false;
		while(infix_expr[i]!='\0'){
			if(isalnum(infix_expr[i])){
				postfix_expr[j]=infix_expr[i];
				j++;
				som=true;
			}
			else{
				if(som){
					som=false;
					postfix_expr[j]=' ';
					j++;continue;
				}
				if(infix_expr[i]==')'){
					while(*(char *)getTopPtr(operators)!='('){
						postfix_expr[j]=*(char *)getTopPtr(operators);
						pop(operators);
						j++;
					}
					pop(operators);
				}
				else if(infix_expr[i]=='('){
					push(operators,&infix_expr[i]);
				}
				else if(isoperator(infix_expr[i])){
					while(getTopPtr(operators)!=NULL && precedence(*(char*)getTopPtr(operators))>=precedence(infix_expr[i])){
					//pop if stack operator has equal or greater priority than current
						postfix_expr[j]=*(char *)getTopPtr(operators);
						pop(operators);
						j++;
					}
					push(operators,&infix_expr[i]);
				}
			}
			i++;
			if(i>=n-1){ break;}
		}
		while(getTopPtr(operators)!=NULL){
			postfix_expr[j]=*(char*)getTopPtr(operators);
			j++;
			pop(operators);
		}
		fputs(postfix_expr,stdout);
		printf("\n");
	}
}
