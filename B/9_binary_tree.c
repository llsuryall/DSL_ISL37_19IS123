#include<stdio.h>
#include<stdlib.h>

struct BTree_node{
	int data;
	struct BTree_node * left;
	struct BTree_node * right;
};

typedef struct BTree_node BTree_node;

BTree_node * input_n_create_BTree(){
	int temp;
	scanf("%d",&temp);
	if(temp<=0){
		return NULL;
	}
	BTree_node * new=malloc(sizeof(BTree_node));
	new->data=temp;
	printf("%d L - ",new->data);
	new->left=input_n_create_BTree();
	printf("%d R - ",new->data);
	new->right=input_n_create_BTree();
	return new;
}

void print_preorder(BTree_node * root){
	if(root!=NULL){
		printf("%d ",root->data);
		print_preorder(root->left);
		print_preorder(root->right);
	}
}

void print_inorder(BTree_node * root){
	if(root!=NULL){
		print_inorder(root->left);
		printf("%d ",root->data);
		print_inorder(root->right);
	}
}

void print_postorder(BTree_node * root){
	if(root!=NULL){
		print_postorder(root->left);
		print_postorder(root->right);
		printf("%d ",root->data);
	}
}

void main(){
	printf("Note: Enter natural numbers (0 or -ve for none)\n");
	printf("Root - ");
	BTree_node * root=input_n_create_BTree();
	printf("Preorder -\n");
	print_preorder(root);
	printf("\nInorder -\n");
	print_inorder(root);
	printf("\nPostorder -\n");
	print_postorder(root);
	printf("\n");
}
