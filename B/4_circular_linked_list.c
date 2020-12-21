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

node * insert(node * head,int data){
	if(head!=NULL){
		node * cur=head;
		while(cur->next!=head){
			cur=cur->next;
		}
		cur->next=createNode(data,head);
		return cur->next;
	}
	else{
		node * new=createNode(data,NULL);
		new->next=new;
		return new;
	}
}

node * insert_after_el(node * head,int el,int data){
	if(head!=NULL){
		node * cur=head->next;
		while(cur!=head && cur->data!=el){
			cur=cur->next;
		}
		if(cur->data==el){
			cur->next=createNode(data,cur->next);
		}
		return head;
	}
	else{
		return head;
	}
}

node * insert_before_el(node * head,int el,int data){
	if(head!=NULL){
		node * cur=head;
		while(cur->next!=head && cur->next->data!=el){
			cur=cur->next;
		}
		if(cur->next->data==el){
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
		if(head==head->next && head->data==el){
			free(head);
			return NULL;
		}
		node * cur=head;
		while(cur->next!=head && cur->next->data!=el){
			cur=cur->next;
		}
		if(cur->next->data==el){
			node * temp=cur->next;
			cur->next=cur->next->next;
			free(temp);
			if(temp!=head){
				return head;
			}
			else{
				return cur->next;
			}
		}
		else{
			return head;
		}
	}
	else{
		printf("The list is empty!\n");
		return NULL;
	}
}

node * delete(node * head){
	if(head!=NULL){
		if(head==head->next){
			free(head);
			return NULL;
		}
		node * cur=head;
		while(cur->next!=head){
			cur=cur->next;
		}
		cur->next=cur->next->next;
		free(head);
		return cur->next;
	}
	else{
		printf("The list is empty!\n");
		return head;
	}
}

void display(node * head){
	if(head!=NULL){
		node * cur=head;
		do{
			printf("%d ",cur->data);
			cur=cur->next;
		}while(cur!=head);
		printf("\n");
	}
}

node * deleteAll(node * head){
	if(head!=NULL){
		node * temp=head;
		node * cur=head;
		do{
			temp=cur->next;
			free(cur);
			cur=temp;
		}while(cur!=head);
		return NULL;
	}
}

void main(){
	_Bool flag=1;
	node * head=NULL;
	printf("Available operations on singly linked list-\nCurrently the linked list is empty\n");
	printf("|1-Insert|\t|2-Delete|\t|3-Insert before element|\t|4-Insert after element|\n|5-Display|\t|6-Delete element|\t|7-Delete linked list & Exit|\n");
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
				head = delete(head);
				break;
			case 3:
				printf("Insert before which element(value)? ");
				scanf("%d",&el);
				printf("Enter the value to insert before %d - ",el);
				scanf("%d",&temp);
				head=insert_before_el(head,el,temp);
				break;
			case 4:
				printf("Insert after which element(value)? ");
				scanf("%d",&el);
				printf("Enter the value to insert after %d - ",el);
				scanf("%d",&temp);
				head=insert_after_el(head,el,temp);
				break;
			case 5:
				display(head);
				break;
			case 6:
				printf("Enter the element to delete-");
				scanf("%d",&el);
				head=delete_el(head,el);
				break;
			case 7:
				head=deleteAll(head);
				flag=false;
				break;
			default:
				printf("Wrong Input! Try again...\n");
		}
		scanf("%*[^\n]");
	}
}
