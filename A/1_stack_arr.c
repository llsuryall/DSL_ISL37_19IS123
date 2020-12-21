#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<../mem_lib.h>
#include<stdbool.h>

struct stack{
	unsigned capacity,top,el_size;
	void * base;
};

typedef struct stack Stack;

Stack * createStack(unsigned capacity,unsigned el_size){
	if(capacity>0 && el_size>0){
		Stack * new_stack = malloc(sizeof(Stack));
		mal_error(new_stack,sizeof(Stack),NULL);
		new_stack->capacity = capacity;
		new_stack->el_size = el_size;
		new_stack->top=0;
		new_stack->base = malloc(capacity*el_size);
		mal_error(new_stack->base,capacity*el_size,NULL,new_stack);
		return new_stack;
	}
	else{
		return NULL;
	}
}

void * getTopPtr(Stack * stack){
	if(stack->top > 0){
		return stack->base + (stack->top-1) * stack->el_size;
	}
	return NULL;
}

_Bool push(Stack * stack,void * el){
	if(stack->top < stack->capacity){
		memcpy(stack->base + stack->top * stack->el_size, el, stack->el_size);
		stack->top++;
		return false;
	}
	else{
		return true;
	}
}

_Bool pop(Stack * stack){
	if(stack->top>0){
		stack->top--;
		return false;
	}
	else{
		return true;
	}
}

void resetStack(Stack * stack){
	stack->top=0;
}

void deleteStack(Stack * stack){
	free(stack->base);
	free(stack);
}

void main(){
	printf("Enter the integer stack size-");
	int n=0;
	scanf("%d",&n);
	Stack * myStack = createStack(n,4);
	_Bool flag=1;
	printf("1-Push\t2-Get\t3-Pop\t4-Reset Stack\t5-Delete Stack & Exit\n");
	while(flag){
		printf("->");
		int inp=0,temp=0;_Bool retCode;
		scanf("%d",&inp);
		switch(inp){
			case 1:
				printf("Enter the value to push-");
				scanf("%d",&temp);
				retCode = push(myStack,&temp);
				if(retCode){
					printf("Unable to push the element!");
				}
				else{
					printf("The number %d has been pushed to the stack!",temp);
				}
				break;
			case 2:
				if(getTopPtr(myStack)!=NULL){
					printf("The value on top is %d",*(int*)getTopPtr(myStack));
				}
				else{
					printf("The stack is empty!");
				}
				break;
			case 3:
				if(getTopPtr(myStack)!=NULL){
					temp = *(int*)getTopPtr(myStack);
				}
				retCode = pop(myStack);
				if(retCode){
					printf("Unable to pop!");
				}
				else{
					printf("The value %d has been popped out!",temp);
				}
				break;
			case 4:
				resetStack(myStack);
				printf("The stack has been reset!");
				break;
			case 5:
				deleteStack(myStack);
				printf("The stack has been deleted!\nNow exiting...");
				flag=0;
				break;
			default:
				printf("Wrong Input! Try again...");
		}
		printf("\n");
	}
}
