#include<stdio.h>
#include<stdlib.h>
#include<math.h>

//struct for each term
struct term{
	double coeff;//coefficient of x
	double exp;//exponent of x
	struct term * next;
};

typedef struct term term;

//create polynomial given 1st term
term * createPol(term * first){
	if(first!=NULL){
		first->next=NULL;
		return first;
	}
	else{
		return NULL;
	}
}

//add terms to existing polynomial linked list and return the end
term * addTerm(term * end,term * new){
	if(end!=NULL){
		end->next=new;
		new->next=NULL;
	}
	else{
		return NULL;
	}
}

//for taking input for single term and returnint it's base pointer
term * takeTermInp(){
	term * temp = malloc(sizeof(term));
	scanf("%lf %lf",&temp->coeff,&temp->exp);//see operator precedence of '->' and '&', no brackets required
	return temp;
}

//for taking a polynomial input and returning pointer to the head
term * takePolInp(){
	unsigned count=0;//unsigned stores only +ve values,so double the int storage
	printf("Enter the no. of terms in the polynomial(min 1)- ");
	term * head=NULL,*end=NULL;
	scanf("%u",&count);
	if(count==0){
		printf("Invalid Input!\n");
		return NULL;
	}
	unsigned n=count;
	printf("(Enter the terms in the form - <coefficient> <exponent>)\n");
	printf("Enter term 1- ");
	head = createPol(takeTermInp());//takes first node as parameter
	count--;
	end = head;//head and end will be same in beginning
	//using 2 pointers instead of traversing to the end each time
	while(count>0){
		printf("Enter term %u- ",n-count+1);
		end = addTerm(end,takeTermInp());
		count--;
	}
	return head;
}

//display the polynomial
void displayPol(term * head){
	printf("P(x) = ");
	if(head!=NULL){
		while(head->next!=NULL){
			printf("%.2lfx^(%.2lf) + ",head->coeff,head->exp);
			head=head->next;
		}
		printf("%.2lfx^(%.2lf)\n",head->coeff,head->exp);
	}
	else{
		printf(" 0 \n");
	}
}

//evaluvate the lnked list with given x
long double evalPol(term * head, double x){
	long double res=0;
	while(head!=NULL){
		res += (head->coeff) * pow(x,head->exp);
		head = head->next;
	}
	return res;
}

void main(){
	term * poly = takePolInp();
	double x=0;
	displayPol(poly);
	printf("Enter the value to of x to evaluvate- ");
	scanf("%lf",&x);
	printf("The value of P(%.2lf) = %.4Lf\n",x,evalPol(poly,x));//%Lf(not 'lf') is format specifier for Long Double
}
