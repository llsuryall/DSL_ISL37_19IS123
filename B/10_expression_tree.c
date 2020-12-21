#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>
#include<../mem_lib.h>

struct stack{
	void * top;
	unsigned el_size;
};

struct stack_node{
	void * el_addr;
	struct stack_node * next;
};

typedef struct stack_node St_node;
typedef struct stack Stack;

Stack * createStack(unsigned el_size){
	if(el_size>0){
		Stack * new = malloc(sizeof(Stack));
		mal_error(new,sizeof(Stack),NULL);
		new->el_size=el_size;
		new->top=NULL;
		return new;
	}
	else{
		return NULL;
	}
}

_Bool push(Stack * stack,void * el_addr){	
	St_node * new_node=malloc(sizeof(St_node));
	mal_error(new_node,sizeof(St_node),true);
	void * new_addr=malloc(stack->el_size);
	mal_error(new_addr,sizeof(St_node),true,(void*)new_node);
	memcpy(new_addr,el_addr,stack->el_size);
	new_node->el_addr=new_addr;
	new_node->next=stack->top;
	stack->top=new_node;
	return false;
}

_Bool pop(Stack * stack){
	if(stack->top!=NULL){
		St_node * cur=(St_node*)stack->top;
		free(cur->el_addr);
		stack->top=cur->next;
		free(cur);
		return false;
	}
	else{
		return true;
	}
}

void * getTopPtr(Stack * stack){
	if(stack->top!=NULL){
		return ((St_node *)stack->top)->el_addr;
	}
	else{
		return NULL;
	}
}

void deleteStack(Stack * stack){
	St_node * cur=(St_node*)stack->top;
	St_node * last=cur;
	while(cur!=NULL){
		free(cur->el_addr);
		last=cur;
		cur=cur->next;
		free(last);
	}
	free(stack);
}

struct BTree_node{
	char data;
	struct BTree_node * left;
	struct BTree_node * right;
};

typedef struct BTree_node BTree_node;

_Bool is_operator(char ch){
	switch(ch){
		case '+':
		case '-':
		case '/':
		case '*':
		case '^':
		case '%':
			return true;
			break;
		default:
			return false;
	}
}

_Bool is_alpha(char ch){
	return ((ch>='a' && ch<='z') || (ch>='A' && ch<='Z'))?true:false;
}

BTree_node * input_n_create_ExpTree(){
	char temp;
	scanf("%c",&temp);
	scanf("%*[^\n]");
	scanf("%*c");
	if(is_alpha(temp)){
		BTree_node * new=malloc(sizeof(BTree_node));
		new->data=temp;
		new->left=NULL;
		new->right=NULL;
		return new;
	}
	else if(is_operator(temp)){
		BTree_node * new=malloc(sizeof(BTree_node));
		new->data=temp;
		printf("%c L - ",new->data);
		new->left=input_n_create_ExpTree();
		printf("%c R - ",new->data);
		new->right=input_n_create_ExpTree();
		return new;
	}
	else{
		printf("Invalid input! Only operators and alphabets allowed!\nEnter again for the previously asked node- ");
		return input_n_create_ExpTree();
	}
}

_Bool check_strict_BTree(BTree_node * root){
	if(root->left==NULL && root->right==NULL){
		return true;
	}
	else if(root->left!=NULL && root->right!=NULL){
		return check_strict_BTree(root->right) && check_strict_BTree(root->left);
	}
	else{
		return false;
	}
}

void print_preorder(BTree_node * root){
	if(root!=NULL){
		printf("%c ",root->data);
		print_preorder(root->left);
		print_preorder(root->right);
	}
}

void print_inorder(BTree_node * root){
	if(root!=NULL){
		if(root->left!=NULL)printf("(");
		print_inorder(root->left);
		printf("%c",root->data);
		print_inorder(root->right);
		if(root->left!=NULL)printf(")");
	}
}

void print_postorder(BTree_node * root){
	if(root!=NULL){
		print_postorder(root->left);
		print_postorder(root->right);
		printf("%c ",root->data);
	}
}

double calc(char op,double op1,double op2){
	switch(op){
		case '+':
			return op1+op2;
			break;
		case '-':
			return op1-op2;
			break;
		case '*':
			return op1*op2;
			break;
		case '/':
			return op1/op2;
			break;
		case '^':
			return pow(op1,op2);
			break;
		case '%':
			return ((int)op1) % ((int)op2);
			break;
		default:
			return 0;
	}
}

BTree_node * createBTree_node(char data,BTree_node * left, BTree_node * right){
	BTree_node * new=malloc(sizeof(BTree_node));
	new->data=data;
	new->left=left;
	new->right=right;
	return new;
}

double eval(BTree_node * root){
	if(root!=NULL){
		if(is_operator(root->data)){
			double op1=eval(root->left);
			double op2=eval(root->right);
			return calc(root->data,op1,op2);
		}
		else if(is_alpha(root->data)){
			printf("Enter the value for '%c' - ",root->data);
			double som=0;
			scanf("%lf",&som);
			return som;
		}
		else return 0;
	}
	else{
		return 0;
	}
}

void main(){
	short choice=0;
	printf("Choose a way to create expression tree-\n1-Postfix Expression\t2-Recursive tree input\n->");
	scanf("%hd",&choice);
	scanf("%*[^\n]");
	scanf("%*c");
	BTree_node * root=NULL;
	Stack * exp_tree_nodes=createStack(sizeof(BTree_node));
	char * str=NULL;
	printf("Note: Enter different alphabets only for variables\n");
	switch(choice){
		case 1:
			printf("Enter approx size of expression - ");
			unsigned n=0;
			scanf("%u",&n);
			scanf("%*[^\n]");
			scanf("%*c");
			if(n>3){
				str=malloc((n+1)*sizeof(char));
				printf("Enter the expression -\n->");
				scanf("%[^\n]",str);
				unsigned i=0;
				BTree_node * op2,*op1;
				while(str[i]!='\0'){
					if(is_alpha(str[i])){
						push(exp_tree_nodes,createBTree_node(str[i],NULL,NULL));
					}
					else if(is_operator(str[i])){
						if(getTopPtr(exp_tree_nodes)==NULL){
							printf("Invalid Expression 1!\n");
							deleteStack(exp_tree_nodes);
							free(str);
							return;
						}
						op2 = malloc(sizeof(BTree_node));
						memcpy(op2,getTopPtr(exp_tree_nodes),sizeof(BTree_node));
						pop(exp_tree_nodes);
						if(getTopPtr(exp_tree_nodes)==NULL){
							printf("Invalid Expression 2!\n");
							deleteStack(exp_tree_nodes);
							free(str);
							return;
						}
						op1 = malloc(sizeof(BTree_node));
						memcpy(op1,getTopPtr(exp_tree_nodes),sizeof(BTree_node));
						pop(exp_tree_nodes);
						push(exp_tree_nodes,createBTree_node(str[i],op1,op2));
					}
					else if(str[i]==' ');
					else{
						printf("%u - '%c'\n",i,str[i]);
						printf("Invalid Expression 3!\n");
						deleteStack(exp_tree_nodes);
						free(str);
						return;
					}
					i++;
				}
				root=getTopPtr(exp_tree_nodes);
			}
			else{
				printf("Invalid size!\n");
			}
			break;
		case 2:
			printf("Root - ");
			root=input_n_create_ExpTree();
			break;
		default:
			printf("Invalid input!\n");
			return;
	}
	if(check_strict_BTree(root)){
		printf("Prefix Expression -\n");
		print_preorder(root);
		printf("\nInfix Expression-\n");
		print_inorder(root);
		printf("\nPostfix Expression -\n");
		print_postorder(root);
		printf("\n\n");
		printf("Evaluvation - \n");
		double res=eval(root);
		print_inorder(root);
		printf(" = %lf\n",res);
	}
	else{
		printf("Invalid expression tree(Not a strict one)!\n");
		deleteStack(exp_tree_nodes);
		free(str);
	}
	return;
}
