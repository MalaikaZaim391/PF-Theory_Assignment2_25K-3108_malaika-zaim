#include<stdio.h> 
#define max_books 100
#define max_booktitle 100
//global arrays/variables waghera used everywhere
char ch='y';
int count_books=0;
int isbns[max_books];
char titles[max_books][max_booktitle];
float prices[max_books];
int quantities[max_books];
//all functions below (before main)
void addbook(){
	int isbn, i,j , quantity; float price; char title[max_booktitle];
	if(count_books>=max_books){
		printf("Inventory already full. Cannot add more books\n");
	}
	printf("Enter isbn: ");
	scanf("%d", &isbn);
	for(i=0; i<count_books; i++){
		if(isbns[i]==isbn){
			printf("\nDuplicate ISBN. Book already in inventory\n");
			return;
		}
	}
	getchar();
	printf("Enter book title: ");
	fgets(title, max_booktitle, stdin);
	int k = 0;
	while (title[k] != '\0') {
    	if (title[k] == '\n') {
			title[k] = '\0';
			break; }
		k++; }
// above while loop instead of strcspn: title[strcspn(title, "\n")]='\0';
	printf("Enter price: ");
	scanf(" %f", &price);
	printf("Enter quantity: ");
	scanf(" %d", &quantity);
	isbns[count_books]=isbn;
	for(j=0; title[j]!='\0'; j++){
		titles[count_books][j]=title[j];
	}
	titles[count_books][j]='\0';
	prices[count_books]=price;
	quantities[count_books]=quantity;
	count_books++ ;
	printf("\t\tBook added successfully!\n");
	printf("\t\t\t =======================================\n");
	printf("Do you want to continue? Press Y if yes: ");
	scanf(" %c", &ch);
}
void process_sale(){
	int isbn, copies, i, j, found=0;
	printf("Enter ISBN of book to sell: ");
	scanf(" %d", &isbn);
	for(i=0;i<count_books; i++){
		if(isbns[i]==isbn){
			found=1;
			printf("Book found: %s\n", titles[i]);
			printf("Book quantity in stock: %d\n", quantities[i]);
			printf("Enter copies do you want to sell: ");
			scanf("%d", &copies);
			if(copies<=0){
				printf("Invalid number of copies. \n");
				return;
			}
			if(copies>quantities[i]){
				printf("Not enough stock. Stock currently available: %d\n", quantities[i]);
			} else{
				quantities[i]-=copies;
				printf("Sale processed Successfully. Remaining stock: %d\n", quantities[i]);
			}
			break;
		}
	}
	if(!found){
		printf("No book found with ISBN %d. Try again.\n", isbn);
	}
	printf("\t\t\t =======================================\n");
	printf("Do you want to continue? Press Y if yes: ");
	scanf(" %c", &ch);
}
void generate_stockreport(){
	int i, found=0;
	printf("\n\t\tLow Stock Report (Quantity<5)\n");
	for(i=0;i<count_books;i++){
		if(quantities[i]<5){
			printf("ISBN: %d\t|\tTitle: %s\t|\tQuantity: %d\n", isbns[i], titles[i], quantities[i]);
			found=1;
		}
	}
	if(!found){
		printf("\t\tNo low stock books, all books in good stock.\n");
	}
	printf("\t\t\t =======================================\n");
	printf("Do you want to continue? Press Y if yes: ");
	scanf(" %c", &ch);
}
void displaybooks(){
	int i;
	if(count_books==0){
		printf("No books in inventory.\n");
		return;
	}
	printf("\n\t\tBook Inventory\n");
	for(i=0;i<count_books;i++){
		printf("\t\t%d. ISBN: %d\t|\tTitle: %s\t|\tPrice: %.2f\t|\tQuantity: %d\n\n",
		i+1, isbns[i], titles[i], prices[i], quantities[i]);
	}
	printf("\t\t\t =======================================\n");
	printf("Do you want to continue? Press Y if yes: ");
	scanf(" %c", &ch);
}
void exitsystem(){
	printf("\nExiting the program...\n");
    printf("Thank you for using Liberty Books Inventory System!\n");
    ch='n';
}
//main begins here
int main(){
	int choice;
	do{
		printf("\n\t\t\t ***********Liberty Books Inventory Management System*********** \n");
		printf("\n1. Add new book");
		printf("\n2. Process a Sale");
		printf("\n3. Generate low stock report");
		printf("\n4. Display all books");
		printf("\n5. Exit system");
		printf("\n\t\t\t =======================================\n\t\tEnter your choice (1-5): ");
		scanf(" %d", &choice);
		switch(choice){
			case 1:
				addbook();
				break;
			case 2:
				process_sale();
				break;
			case 3:
				generate_stockreport();
				break;
			case 4:
				displaybooks();
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
