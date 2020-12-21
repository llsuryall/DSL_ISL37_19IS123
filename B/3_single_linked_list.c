#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct node{
	int data;
	struct node * next;
};

typedef struct node node;

node * createNode(int data,node * next){
	node * new=malloc(sizeof(node));
	new->data=data;
	new->next=next;
	return new;
}

node * insert_front(node * head,int data){
	return createNode(data,head);
}

node * insert_rear(node * head,int data){
	if(head!=NULL){
		node * cur=head;
		while(cur->next!=NULL){
			cur=cur->next;
		}
		cur->next=createNode(data,NULL);
		return head;
	}
	else{
		return createNode(data,NULL);
	}
}

node * insert_after_el(node * head,int el,int data){
	node * cur=head;
	while(cur!=NULL && cur->data!=el){
		cur=cur->next;
	}
	if(cur!=NULL){
		cur->next=createNode(data,cur->next);
	}
	return head;
}

node * insert_before_el(node * head,int el,int data){
	if(head!=NULL){
		if(head->data==el){
			return createNode(data,head);
		}
		node * cur=head;
		while(cur->next!=NULL && cur->next->data!=el){
			cur=cur->next;
		}
		if(cur->next!=NULL){
			cur->next=createNode(data,cur->next);
		}
		return head;
	}
	else{
		return NULL;
	}
}

node * delete_el(node * head,int el){
	if(head!=NULL){
		if(head->data==el){
			node * temp=head->next;
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
	printf("|1-Insert(rear)|\t|2-Delete(front)|\t|3-Insert(front)|\t|4-Delete(rear)|\n|5-Display|\t|6-Insert before element|\t|7-Insert after element|\t|8-Delete element|\t|9-Delete linked list & Exit|\n");
	while(flag){
		printf("->");
		int inp=0,temp=0,el=0;_Bool retCode;
		scanf("%d",&inp);
		switch(inp){
			case 1:
				printf("Enter the value to insert at rear- ");
				scanf("%d",&temp);
				head = insert_rear(head,temp);
				break;
			case 2:
				head = delete_front(head);
				break;
			case 3:
				printf("Enter the value to insert at front- ");
				scanf("%d",&temp);
				head = insert_front(head,temp);
				break;
			case 4:
				head = delete_rear(head);
				break;
			case 5:
				display(head);
				break;
			case 6:
				printf("Insert before which element(value)? ");
				scanf("%d",&el);
				printf("Enter the value to insert before %d - ",el);
				scanf("%d",&temp);
				head=insert_before_el(head,el,temp);
				break;
			case 7:
				printf("Insert after which element(value)? ");
				scanf("%d",&el);
				printf("Enter the value to insert after %d - ",el);
				scanf("%d",&temp);
				head=insert_after_el(head,el,temp);
				break;
			case 8:
				printf("Enter the element to delete-");
				scanf("%d",&el);
				head=delete_el(head,el);
				break;
			case 9:
				head=deleteAll(head);
				flag=false;
				break;
			default:
				printf("Wrong Input! Try again...\n");
		}
		scanf("%*[^\n]");
	}
}
