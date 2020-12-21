#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<../mem_lib.h>
#include<stdbool.h>

struct cirqueue{
	unsigned capacity,front,rear,el_size;
	_Bool is_empty;
	void * base;
};

typedef struct cirqueue CirQueue;

CirQueue * createCirQueue(unsigned capacity,unsigned el_size){
	if(capacity>0 && el_size>0){
		CirQueue * new_cirqueue = malloc(sizeof(CirQueue));
		mal_error(new_cirqueue,sizeof(CirQueue),NULL);
		new_cirqueue->capacity = capacity;
		new_cirqueue->el_size = el_size;
		new_cirqueue->front=0;
		new_cirqueue->rear=0;
		new_cirqueue->is_empty=true;
		new_cirqueue->base = malloc(capacity*el_size);
		mal_error(new_cirqueue->base,capacity*el_size,NULL,new_cirqueue);
		return new_cirqueue;
	}
	else{
		return NULL;
	}
}

void * getFrontPtr(CirQueue * cirqueue){
	if(!cirqueue->is_empty){
		return cirqueue->base + cirqueue->front * cirqueue->el_size;
	}
	return NULL;
}

void * getRearPtr(CirQueue * cirqueue){
	if(!cirqueue->is_empty){
		return cirqueue->base + cirqueue->rear * cirqueue->el_size;
	}
	return NULL;
}

_Bool insert_front(CirQueue * cirqueue,void * el){
	if(cirqueue->is_empty){
		cirqueue->front=0,cirqueue->rear=0;
		memcpy(cirqueue->base,el,cirqueue->el_size);
		cirqueue->is_empty=false;
		return false;
	}
	else{
		unsigned pos=(cirqueue->capacity+cirqueue->front-1)%cirqueue->capacity;
		if( pos != cirqueue->rear){
			cirqueue->front=pos;
			memcpy(cirqueue->base+cirqueue->front*cirqueue->el_size,el,cirqueue->el_size);
			return false;
		}
		else{
			return true;
		}
	}
}

_Bool insert_rear(CirQueue * cirqueue,void * el){
	if(cirqueue->is_empty){
		cirqueue->front=0,cirqueue->rear=0;
		memcpy(cirqueue->base,el,cirqueue->el_size);
		cirqueue->is_empty=false;
		return false;
	}
	else{
		unsigned pos=(cirqueue->rear+1)%cirqueue->capacity;
		if( pos != cirqueue->front){
			cirqueue->rear=pos;
			memcpy(cirqueue->base+cirqueue->rear*cirqueue->el_size,el,cirqueue->el_size);
			return false;
		}
		else{
			return true;
		}
	}
}

_Bool delete_front(CirQueue * cirqueue){
	if(!cirqueue->is_empty){
		if(cirqueue->rear==cirqueue->front){
			cirqueue->is_empty=true;
		}
		else{
			cirqueue->front=(cirqueue->front+1)%cirqueue->capacity;
		}
		return false;
	}
	else{
		return true;
	}
}


_Bool delete_rear(CirQueue * cirqueue){
	if(!cirqueue->is_empty){
		if(cirqueue->rear==cirqueue->front){
			cirqueue->is_empty=true;
		}
		else{
			cirqueue->rear=(cirqueue->capacity+cirqueue->rear-1)%cirqueue->capacity;
		}
		return false;
	}
	else{
		return true;
	}
}

void resetCirQueue(CirQueue * cirqueue){
	cirqueue->is_empty=true;
}

void deleteCirQueue(CirQueue * cirqueue){
	free(cirqueue->base);
	free(cirqueue);
}

void displayIntCirQueue(CirQueue * cirqueue){
	if(!cirqueue->is_empty){
		unsigned cur=cirqueue->front;
		while(cur!=cirqueue->rear){
			printf("%d ",*(int*)(cirqueue->base+cur*4));
			cur=(cur+1)%cirqueue->capacity;
		}
		printf("%d\n",*(int*)(cirqueue->base+cirqueue->rear*4));
	}
}

void main(){
	printf("Enter the CirQueue size-");
	unsigned n=0;
	scanf("%d",&n);
	CirQueue * myCirQueue = createCirQueue(n,4);
	_Bool flag=1;
	printf("|1-Insert(rear)|\t|2-Delete(front)|\t|3-Insert(front)|\t|4-Delete(rear)|\n|5-Display|\t|6-Reset CirQueue|\t|7-Delete CirQueue & Exit|\n");
	while(flag){
		printf("->");
		int inp=0,temp=0;_Bool retCode;
		scanf("%d",&inp);
		switch(inp){
			case 1:
				printf("Enter the value to insert at rear- ");
				scanf("%d",&temp);
				retCode = insert_rear(myCirQueue,&temp);
				if(retCode){
					printf("Unable to insert the element from rear!\n");
				}
				break;
			case 2:
				retCode = delete_front(myCirQueue);
				if(retCode){
					printf("Unable to delete from front!\n");
				}
				break;
			case 3:
				printf("Enter the value to insert at front- ");
				scanf("%d",&temp);
				retCode = insert_front(myCirQueue,&temp);
				if(retCode){
					printf("Unable to insert the element from front!\n");
				}
				break;
			case 4:
				retCode = delete_rear(myCirQueue);
				if(retCode){
					printf("Unable to delete from rear!\n");
				}
				break;
			case 5:
				displayIntCirQueue(myCirQueue);
				break;
			case 6:
				resetCirQueue(myCirQueue);
				printf("The cirqueue has been reset!\n");
				break;
			case 7:
				deleteCirQueue(myCirQueue);
				printf("The cirqueue has been deleted!\nNow exiting...\n");
				flag=0;
				break;
			default:
				printf("Wrong Input! Try again...\n");
		}
		scanf("%*[^\n]");
	}
}
