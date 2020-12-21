#include<stdio.h>
#include<stdlib.h>

struct node{
	int data;
	struct node * next;
};

typedef struct node node;

node * reverse_sll(node * head){
	if(head!=NULL){
		node * prev=NULL,* cur=head,* next=head->next;
		while(next!=NULL){
			next=cur->next;
			cur->next=prev;
			prev=cur;
			cur=next;
		}
		if(prev!=NULL){
			return prev;
		}
		else{
			return head;
		}
	}
	else{
		return NULL;
	}
}

node * createNode(unsigned data){
	node * new=malloc(sizeof(node));
	new->data=data;
	new->next=NULL;
	return new;
}

node * insert(node * head,unsigned data){
	if(head!=NULL){
		node * cur=head;
		while(cur->next!=NULL){
			cur=cur->next;
		}
		cur->next=createNode(data);
		return head;
	}
	else{
		return createNode(data);
	}
}

void main(){
	node * head=NULL;
	printf("Enter natural no.s for the linked list (Enter 0 to stop) -\n");
	unsigned inp=0;
	printf("->");
	scanf("%u",&inp);
	while(inp!=0){
		head=insert(head,inp);
		scanf("%u",&inp);
	}
	printf("The elements in the list are -\n");
	node * cur=head;
	while(cur!=NULL){
		printf("%u ",cur->data);
		cur=cur->next;
	}
	printf("\nAfter reversing the list-\n");
	head=reverse_sll(head);
	cur=head;
	while(cur!=NULL){
		printf("%u ",cur->data);
		cur=cur->next;
	}
	printf("\n");
}
