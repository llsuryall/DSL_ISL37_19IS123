#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<../mem_lib.h>
#include<stdbool.h>

struct queue{
	unsigned capacity,front,rear,el_size;
	_Bool is_empty;
	void * base;
};

typedef struct queue Queue;

Queue * createQueue(unsigned capacity,unsigned el_size){
	if(capacity>0 && el_size>0){
		Queue * new_queue = malloc(sizeof(Queue));
		mal_error(new_queue,sizeof(Queue),NULL);
		new_queue->capacity = capacity;
		new_queue->el_size = el_size;
		new_queue->front=0;
		new_queue->rear=0;
		new_queue->is_empty=true;
		new_queue->base = malloc(capacity*el_size);
		mal_error(new_queue->base,capacity*el_size,NULL,new_queue);
		return new_queue;
	}
	else{
		return NULL;
	}
}

void * getFrontPtr(Queue * queue){
	if(!queue->is_empty){
		return queue->base + queue->front * queue->el_size;
	}
	return NULL;
}

void * getRearPtr(Queue * queue){
	if(!queue->is_empty){
		return queue->base + queue->rear * queue->el_size;
	}
	return NULL;
}

_Bool insert_front(Queue * queue,void * el){
	if(queue->is_empty){
		queue->front=0,queue->rear=0;
		memcpy(queue->base,el,queue->el_size);
		queue->is_empty=false;
		return false;
	}
	else{
		if( queue->front > 0 ){
			queue->front--;
			memcpy(queue->base+queue->front*queue->el_size,el,queue->el_size);
			return false;
		}
		else{
			return true;
		}
	}
}

_Bool insert_rear(Queue * queue,void * el){
	if(queue->is_empty){
		queue->front=0,queue->rear=0;
		memcpy(queue->base,el,queue->el_size);
		queue->is_empty=false;
		return false;
	}
	else{
		if( queue->rear < queue->capacity-1){
			queue->rear++;
			memcpy(queue->base+queue->rear*queue->el_size,el,queue->el_size);
			return false;
		}
		else{
			return true;
		}
	}
}

_Bool delete_front(Queue * queue){
	if(!queue->is_empty){
		if(queue->rear==queue->front){
			queue->is_empty=true;
		}
		else{
			queue->front++;
		}
		return false;
	}
	else{
		return true;
	}
}


_Bool delete_rear(Queue * queue){
	if(!queue->is_empty){
		if(queue->rear==queue->front){
			queue->is_empty=true;
		}
		else{
			queue->rear--;
		}
		return false;
	}
	else{
		return true;
	}
}

void resetQueue(Queue * queue){
	queue->is_empty=true;
}

void deleteQueue(Queue * queue){
	free(queue->base);
	free(queue);
}


void displayIntQueue(Queue * queue){
	if(!queue->is_empty){
		unsigned cur=queue->front;
		while(cur!=queue->rear){
			printf("%d ",*(int*)(queue->base+cur*4));
			cur++;
		}
		printf("%d\n",*(int*)(queue->base+queue->rear*4));
	}
}

void main(){
	printf("Enter the Queue size-");
	unsigned n=0;
	scanf("%d",&n);
	Queue * myQueue = createQueue(n,4);
	_Bool flag=1;
	printf("|1-Insert(rear)|\t|2-Delete(front)|\t|3-Insert(front)|\t|4-Delete(rear)|\n|5-Display|\t|6-Reset Queue|\t|7-Delete Queue & Exit|\n");
	while(flag){
		printf("->");
		int inp=0,temp=0;_Bool retCode;
		scanf("%d",&inp);
		switch(inp){
			case 1:
				printf("Enter the value to insert at rear- ");
				scanf("%d",&temp);
				retCode = insert_rear(myQueue,&temp);
				if(retCode){
					printf("Unable to insert the element from rear!\n");
				}
				break;
			case 2:
				retCode = delete_front(myQueue);
				if(retCode){
					printf("Unable to delete from front!\n");
				}
				break;
			case 3:
				printf("Enter the value to insert at front- ");
				scanf("%d",&temp);
				retCode = insert_front(myQueue,&temp);
				if(retCode){
					printf("Unable to insert the element from front!\n");
				}
				break;
			case 4:
				retCode = delete_rear(myQueue);
				if(retCode){
					printf("Unable to delete from rear!\n");
				}
				break;
			case 5:
				displayIntQueue(myQueue);
				break;
			case 6:
				resetQueue(myQueue);
				printf("The queue has been reset!\n");
				break;
			case 7:
				deleteQueue(myQueue);
				printf("The queue has been deleted!\nNow exiting...\n");
				flag=0;
				break;
			default:
				printf("Wrong Input! Try again...\n");
		}
		scanf("%*[^\n]");
	}
}
