#include<stdio.h>
#include<stdlib.h>

int * q,front=-1,rear=-1,SIZE=0;

void insert(int data){
	if(rear<SIZE-1){
		if(rear==-1){
			front++;rear++;q[0]=data;
		}
		else{
			int i=front;
			for(;i<=rear;i++){
				if(data>q[i]){
					for(int j=rear;j>=i;j--){
						q[j+1]=q[j];
					}
					break;
				}
			}
			q[i]=data;
			rear++;
		}
	}
	else{
		printf("Queue is full!\n");
	}
}

void delete(){
	if(front==-1){
		printf("Queue is empty!\n");
	}
	else if(front==rear){
		front=-1;rear=-1;
	}
	else{
		front++;
	}
}

void display(){
	if(front!=-1){
		for(int i=front;i<=rear;i++){
			printf("%d ",q[i]);
		}
		printf("\n");
	}
	else{
		printf("Queue is empty\n");
	}
}

void main(){
	printf("Enter size of the queue - ");
	scanf("%d",&SIZE);
	if(SIZE>0){
		q=malloc(sizeof(int)*SIZE);
		short inp=4;
		int cur=0;
		printf("1 - Insert, 2 - Delete, 3 - Display , 0 - Exit\n");
		while(inp){
			printf("->");
			scanf("%hd",&inp);
			scanf("%*[^\n]");
			if(inp==1){
					scanf("%d",&cur);
				insert(cur);
			}
			else if(inp==2){
				delete();
			}
			else if(inp==3){
				display();
			}
			else if(inp==0){
				break;
			}
			else{
			}
		}
	}
}
