#include<stdio.h>
#define max 100
//-1=stack is empty. when incrementing the element will go to index 0 like in array
int top=-1;
int stack[max];
char ch='y';
//all stack functions below
void push(int stack[], int *top, int size){
	if(*top==size-1){
		printf("Stack Overflow. Unable to push more elements.\n");
	}else{
		int num;
		printf("Enter value to push: ");
		scanf("%d", &num);
		(*top)++; 
//		using pointer here means the adress of top moves up, we store value in that adress in the line below
		stack[*top]=num;
		printf("Push successful.  Pushed Element: %d\n", num);
	}
	printf("\t\t\t =======================================\n");
    printf("Do you want to continue? Press Y if yes: ");
    scanf(" %c", &ch);
}
void pop(int stack[], int *top){
	if(*top==-1){
		printf("Stack Underflow. No elements to pop.\n");
	}else{
		printf("Pop Successful. Removed Element: %d\n", stack[*top]);
		(*top)--; 
	}
	printf("\t\t\t =======================================\n");
    printf("Do you want to continue? Press Y if yes: ");
    scanf(" %c", &ch);
}
void peek(int stack[], int top){
	if(top==-1){
		printf("Stack Empty. Nothing to peek.\n");
	}else{
		printf("Peek Successful. Top Element: %d\n", stack[top]);
	}
	printf("\t\t\t =======================================\n");
    printf("Do you want to continue? Press Y if yes: ");
    scanf(" %c", &ch);
}
void display(int stack[], int top){
	int i;
	if(top==-1){
		printf("Stack Empty. Nothing to Display.\n");
	}else{
		printf("\nCurrent Stack - Top to Bottom: \n");
		for(i=top; i>=0; i--){
			printf("%2d. %2d\n", i, stack[i]);
		}
	}
	printf("\t\t\t =======================================\n");
    printf("Do you want to continue? Press Y if yes: ");
    scanf(" %c", &ch);	
}
void exitsystem(){
	printf("\nExiting the program...\n");
    printf("Thank you for using Stack Management System!\n");
    ch='n';
}

//main starts here
int main(){
	int stack[max]={0};
	int choice, i; char message[200];
	do{
		printf("\n\t\t\t ***********Stack Management System*********** \n");
		printf("\n1. Push (insert element)");
		printf("\n2. Pop (remove top element)");
		printf("\n3. Peek (display top element only)");
		printf("\n4. Display (display ALL elements)");
		printf("\n5. Exit");
		printf("\n\t\t\t =======================================\n\t\tEnter your choice (1-5): ");
		scanf(" %d", &choice);
		getchar();
		switch(choice){
			case 1:
				push(stack, &top, max);
				break;
			case 2:
				pop(stack, &top);
				break;
			case 3:
				peek(stack, top);
				break;
			case 4:
				display(stack, top);
				break;	
			case 5:
				exitsystem();
				break;
			default:
				printf("Invalid choice. Please try again\n");
				printf("\t\t\t =======================================\n");
				printf("Do you want to continue? Press Y if yes: ");
				scanf(" %c", &ch);
		}
	}while(ch=='y'|| ch=='Y');
	return 0;
}

