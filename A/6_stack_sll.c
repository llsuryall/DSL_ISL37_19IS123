#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<../mem_lib.h>

struct stack{
	void * top;
	unsigned el_size;
};

struct stack_node{
	void * el_addr;
	struct stack_node * next;
};

typedef struct stack_node St_node;
typedef struct stack Stack;

Stack * createStack(unsigned el_size){
	if(el_size>0){
		Stack * new = malloc(sizeof(Stack));
		mal_error(new,sizeof(Stack),NULL);
		new->el_size=el_size;
		new->top=NULL;
		return new;
	}
	else{
		return NULL;
	}
}

_Bool push(Stack * stack,void * el_addr){	
	St_node * new_node=malloc(sizeof(St_node));
	mal_error(new_node,sizeof(St_node),true);
	void * new_addr=malloc(stack->el_size);
	mal_error(new_addr,sizeof(St_node),true,(void*)new_node);
	memcpy(new_addr,el_addr,stack->el_size);
	new_node->el_addr=new_addr;
	new_node->next=stack->top;
	stack->top=new_node;
	return false;
}

_Bool pop(Stack * stack){
	if(stack->top!=NULL){
		St_node * cur=(St_node*)stack->top;
		free(cur->el_addr);
		stack->top=cur->next;
		free(cur);
		return false;
	}
	else{
		return true;
	}
}

void * getTopPtr(Stack * stack){
	if(stack->top!=NULL){
		return ((St_node *)stack->top)->el_addr;
	}
	else{
		return NULL;
	}
}

void deleteStack(Stack * stack){
	St_node * cur=(St_node*)stack->top;
	St_node * last=cur;
	while(cur!=NULL){
		free(cur->el_addr);
		last=cur;
		cur=cur->next;
		free(last);
	}
	free(stack);
}

void main(){
	Stack * myStack = createStack(4);
	_Bool flag=1;
	printf("1-Push\t2-Get\t3-Pop\t4-Delete & Exit\n");
	while(flag){
		printf("->");
		short inp=0;int temp=0;_Bool retCode;
		scanf("%hd",&inp);
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
					retCode = pop(myStack);
					if(retCode){
						printf("Unable to pop!");
					}
					else{
						printf("The value %d has been popped out!",temp);
					}
				}
				else{
					printf("Stack is empty! Cannot pop");
				}
				break;
			case 4:
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
