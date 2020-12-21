#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<mem_lib.h>
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
