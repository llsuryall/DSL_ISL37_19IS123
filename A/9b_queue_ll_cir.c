#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<../mem_lib.h>

struct queue{
	void *front;
	unsigned el_size;
};

struct queue_node{
	void * el_addr;
	struct queue_node * next;
};

typedef struct queue_node Q_node;
typedef struct queue Queue;

Queue * createQueue(unsigned el_size){
	if(el_size>0){
		Queue * new = malloc(sizeof(Queue));
		mal_error(new,sizeof(Queue),NULL);
		new->el_size=el_size;
		new->front=NULL;
		return new;
	}
	else{
		return NULL;
	}
}

Q_node * createQ_node(Queue * queue,void * el_addr){
	Q_node * new_node=malloc(sizeof(Q_node));
	mal_error(new_node,sizeof(Q_node),NULL);
	void * new_addr=malloc(queue->el_size);
	mal_error(new_addr,sizeof(Q_node),NULL,(void*)new_node);
	memcpy(new_addr,el_addr,queue->el_size);
	new_node->el_addr=new_addr;
	new_node->next=NULL;
	return new_node;
}

_Bool insert_rear(Queue * queue,void * el_addr){
	Q_node * new_node = createQ_node(queue,el_addr);
	if(new_node==NULL){ return true;}
	if(queue->front==NULL){
		queue->front=new_node;
		new_node->next=new_node;
	}
	else{
		Q_node * cur=queue->front;
		while(cur->next!=queue->front){
			cur=cur->next;
		}
		cur->next=new_node;
		new_node->next=queue->front;
	}
	return false;
}

_Bool delete_front(Queue * queue){
	if(queue->front!=NULL){
		Q_node * cur=queue->front,* cp=queue->front;
		while(cur->next!=queue->front){
			cur=cur->next;
		}
		cur->next=cp->next;
		free(cp->el_addr);
		free(cp);
		if(cur==queue->front){
			queue->front=NULL;
		}
		else{
			queue->front=cur->next;
		}
		return false;
	}
	else{
		return true;
	}
}

_Bool insert_front(Queue * queue,void * el_addr){
	Q_node * new_node = createQ_node(queue,el_addr);
	if(new_node==NULL){ return true;}
	if(queue->front==NULL){
		queue->front=new_node;
		new_node->next=new_node;
	}
	else{
		new_node->next=queue->front;
		Q_node * cur=queue->front;
		while(cur->next!=queue->front){
			cur=cur->next;
		}
		cur->next=new_node;
		queue->front=new_node;
	}
	return false;
}

_Bool delete_rear(Queue * queue){
	if(queue->front==NULL){
		return true;
	}
	else{
		if(((Q_node*)queue->front)->next==queue->front){
			free(((Q_node*)queue->front)->el_addr);
			free(queue->front);
			queue->front=NULL;
		}
		else{
			Q_node * cur=queue->front;
			while(cur->next->next!=queue->front){
				cur=cur->next;
			}
			free(cur->next->el_addr);
			free(cur->next);
			cur->next=queue->front;
		}
		return false;
	}
}

void * getFrontPtr(Queue * queue){
	if(queue->front!=NULL){
		return ((Q_node *)queue->front)->el_addr;
	}
	else{
		return NULL;
	}
}

void deleteQueue(Queue * queue){
	if(queue->front!=NULL){
		Q_node * cur=queue->front,* next=NULL;
		while(cur->next!=queue->front){
			free(cur->el_addr);
			next=cur->next;
			free(cur);
			cur=next;
		}
		free(cur->el_addr);
		free(cur);
	}
	free(queue);
}

void displayIntQueue(Queue * queue){
	if(queue->front!=NULL){
		Q_node * cur=queue->front;
		while(cur->next!=queue->front){
			printf("%d ",*(int*)(cur->el_addr));
			cur=cur->next;
		}
		printf("%d\n",*(int*)(cur->el_addr));
	}
}

void main(){
	Queue * myQueue = createQueue(4);
	_Bool flag=1;
	printf("|1-Insert(rear)|\t|2-Delete(front)|\t|3-Insert(front)|\t|4-Delete(rear)|\n|5-Display|\t|6-Delete Queue & Exit|\n");
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
