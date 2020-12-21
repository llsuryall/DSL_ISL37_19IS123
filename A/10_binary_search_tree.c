#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct BT_node{
	int data;
	struct BT_node * left;
	struct BT_node * right;
};

typedef struct BT_node BT_node;

BT_node * createNode(int data){
	BT_node * new=malloc(sizeof(BT_node));
	new->data=data;
	new->left=NULL;
	new->right=NULL;
}

BT_node * insert(BT_node * root,int data){
	if(root==NULL){
		return createNode(data);
	}
	else{
		if(data<=root->data){
			if(root->left==NULL){
				root->left=createNode(data);
			}
			else{
				insert(root->left,data);
			}
		}
		else{
			if(root->right==NULL){
				root->right=createNode(data);
			}
			else{
				insert(root->right,data);
			}
		}
		return root;
	}
}

void print_preorder(BT_node * root){
	if(root!=NULL){
		printf("%d ",root->data);
		print_preorder(root->left);
		print_preorder(root->right);
	}
}

void print_inorder(BT_node * root){
	if(root!=NULL){
		print_inorder(root->left);
		printf("%d ",root->data);
		print_inorder(root->right);
	}
}

void print_postorder(BT_node * root){
	if(root!=NULL){
		print_postorder(root->left);
		print_postorder(root->right);
		printf("%d ",root->data);
	}
}

void main(){
	BT_node * root=NULL;
	int inp=0;
	printf("Enter the no.s to insert to binary tree (0 to stop)-\n->");
	scanf("%d",&inp);
	while(inp!=0){
		root=insert(root,inp);
		scanf("%d",&inp);
	}
	printf("Preorder - ");
	print_preorder(root);
	printf("\n");
	printf("Inorder - ");
	print_inorder(root);
	printf("\n");
	printf("Postorder - ");
	print_postorder(root);
	printf("\n");
}
