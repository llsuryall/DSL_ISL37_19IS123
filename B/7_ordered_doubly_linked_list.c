#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct node{
	int data;
	struct node * next;
	struct node * prev;
};

typedef struct node node;

node * createNode(int data,node * prev,node * next){
	node * new=malloc(sizeof(node));
	new->data=data;
	new->next=next;
	new->prev=prev;
	return new;
}

node * insert(node * head,int data){
	if(head!=NULL){
		node * cphead=head;
		while(head->next!=NULL){
			if(head->data>data){
				break;
			}
			head=head->next;
		}
		if(head->data>data){
			if(head->prev!=NULL){
				head->prev=createNode(data,head->prev->prev,head);
				return cphead;
			}
			else{
				head->prev=createNode(data,NULL,head);
				return head->prev;
			}
		}
		else{
			head->next=createNode(data,head,NULL);
			return cphead;
		}
	}
	else{
		return createNode(data,NULL,NULL);
	}
}

node * delete_el(node * head,int el){
	if(head!=NULL){
		if(head->data==el){
			node * temp=head->next;
			temp->prev=NULL;
			free(head);
			return temp;
		}
		node * cur=head;
		while(cur->next!=NULL && cur->next->data!=el){
			cur=cur->next;
		}
		if(cur->next!=NULL){
			node * temp=cur->next->next;
			free(cur->next);
			cur->next=temp;
			if(temp!=NULL)temp->prev=cur;
		}
		return head;
	}
	else{
		printf("The list is empty!\n");
		return NULL;
	}
}

node * delete_front(node * head){
	if(head!=NULL){
		node * temp=head->next;
		free(head);
		if(temp!=NULL)temp->prev=NULL;
		return temp;
	}
	else{
		printf("The list is empty!\n");
		return head;
	}
}

node * delete_rear(node * head){
	if(head!=NULL){
		if(head->next!=NULL){
			node * cur=head;
			while(cur->next->next!=NULL){
				cur=cur->next;
			}
			free(cur->next);
			cur->next=NULL;
			return head;
		}
		else{
			free(head);
			return NULL;
		}
	}
	else{
		printf("The list is empty!\n");
		return head;
	}
}

void display(node * head){
	if(head!=NULL){
		while(head!=NULL){
			printf("%d ",head->data);
			head=head->next;
		}
		printf("\n");
	}
}

node * deleteAll(node * head){
	node * temp=head;
	while(head!=NULL){
		temp=head->next;
		free(head);
		head=temp;
	}
	return NULL;
}

void main(){
	_Bool flag=1;
	node * head=NULL;
	printf("Available operations on singly linked list-\nCurrently the linked list is empty\n");
	printf("|1-Insert|\t|2-Delete(front)|\t|3-Delete(rear)|\t|4-Delete element|\n|5-Display|\t|6-Delete linked list & Exit|\n");
	while(flag){
		printf("->");
		int inp=0,temp=0,el=0;
		scanf("%d",&inp);
		switch(inp){
			case 1:
				printf("Enter the value to insert- ");
				scanf("%d",&temp);
				head = insert(head,temp);
				break;
			case 2:
				head = delete_front(head);
				break;
			case 3:
				head = delete_rear(head);
				break;
			case 4:
				printf("Enter the element to delete-");
				scanf("%d",&el);
				head=delete_el(head,el);
				break;
			case 5:
				display(head);
				break;
			case 6:
				head=deleteAll(head);
				flag=false;
				break;
			default:
				printf("Wrong Input! Try again...\n");
		}
		scanf("%*[^\n]");
	}
}
