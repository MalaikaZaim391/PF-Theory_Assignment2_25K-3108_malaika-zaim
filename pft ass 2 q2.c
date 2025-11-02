#include<stdio.h>
#define max_products 4
#define max_cart 20
#define name_length 50
#define cnic_length 16
char ch='y';
char codes[max_products][4]={"001","002","003","004"};
int stock[max_products]={50, 10, 20, 8};
int price[max_products]={100, 200, 300, 150};
int cart_index[max_cart];
int cart_qty[max_cart];
int cart_count=0;
char customer_name[name_length];
char customer_cnic[cnic_length];
void trim_newline(char *s) {
    int i=0;
    while (s[i]!='\0') {
        if (s[i]=='\n') { s[i] = '\0'; break; }
        i++;
    }
}
void customer_info(){
	printf("Enter customer name: ");
	fgets(customer_name, name_length, stdin);
	trim_newline(customer_name);
	printf("Enter cnic (hyphens included): ");
	fgets(customer_cnic, cnic_length, stdin);
	trim_newline(customer_cnic);
	printf("Customer recorded:\nCustomer Name: %s \nCustomer CNIC: %s \n", customer_name, customer_cnic);	
}
void display_inventory(){
	printf("\nProduct Code\t|\tInventory in Stock\t|\tPrice per Product\n");
	int i;
	for(i=0; i<max_products; i++){
		printf("\t%s\t|\t\t\t%d\t|\t\t%d\n", codes[i], stock[i], price[i]);
	}
}
int search_product(const char *code){
	int i,j;
	for(i=0; i<max_products; i++){
		int k=0, match=1;
		while(code[k]!='\0'||codes[i][k]!='\0'){
			if(code[k]!=codes[i][k]){
				match=0;
				break;
			}
			k++;
		}
		if(match){
			return i;
		}
	}
	return -1;
}
void addtocart(){
	char code[10];
	int quantity;
	printf("Enter product code: ");
	fgets(code, sizeof(code), stdin);
	trim_newline(code);
	int p=search_product(code);
	if(p==-1){
		printf("Product code not found.\n"); 
		return;
	}
	printf("Enter quantity you want to add: ");
	scanf("%d", &quantity);
	getchar();
	if(quantity<=0){
		printf("Invalid. Enter positive quantity.\n");
		return;
	}
	if(quantity>stock[p]){
		printf("Not enough stock. Currently available: %d\n", stock[p]);
		return;
	}
	int i;
	for(i=0; i<cart_count; i++){
		if(cart_index[i]==p){
			cart_qty[i]+= quantity;
			stock[p]-=quantity;
			printf("Added %d more of %s to cart (now %d). \n", quantity, codes[p], cart_qty[i]);
			return;
		}
	}
	if (cart_count<max_cart) {
        cart_index[cart_count]=p;
        cart_qty[cart_count]=quantity;
        cart_count++;
        stock[p]-=quantity;
        printf("Added %d of %s to cart.\n", quantity, codes[p]);
    } else {
        printf("Cart full. Unable to add more items.\n");
    }
    printf("Remaining stock of %s: %d\n", codes[p], stock[p]);
}
double compute_total() {
    double total = 0.0;
    int i;
    for(i=0; i<cart_count; i++) {
        int p=cart_index[i];
        total+=(double)price[p] * cart_qty[i];
    }
    return total;
}
void display_total_bill() {
    if (cart_count==0) { 
	printf("Cart is empty.\n"); 
	return; }
    double total = compute_total();
    printf("Raw total: %.2f\n", total);
    char code[50];
    printf("Do you have a promo code? Enter the code or press enter to skip: ");
    fgets(code, sizeof(code), stdin);
    trim_newline(code);
    double final = total;
    if (code[0] != '\0') {
        char promo[] = "Eid2025";
        int k=0, match=1;
        while (code[k]!='\0' || promo[k]!='\0') {
            if (code[k]!=promo[k]) { 
			match=0; 
			break; }
            k++;
        }
        if(match) {
            final=total*0.75; 
            printf("Promo applied. 25%% discount.\n");
        } else {
            printf("Invalid promo code. No discount applied.\n");
        }
    }
    printf("Final total: %.2f\n", final);
}
void show_invoice() {
    printf("\nINVOICE\nCustomer: %s\nCNIC: %s\n", customer_name[0] ? customer_name : "N/A", customer_cnic[0] ? customer_cnic : "N/A");
    if (cart_count==0) { 
	printf("Cart is empty.\n"); 
	return; }
    printf("\nItem\tQty\tUnitPrice\tLineTotal\n");
    int i;
	for (i=0; i<cart_count; i++) {
        int p = cart_index[i];
        double line = (double)price[p] * cart_qty[i];
        printf("%s\t%d\t%d\t\t%.2f\n", codes[p], cart_qty[i], price[p], line);
    }
    double total = compute_total();
    printf("\nSubtotal: %.2f\n", total);
    char code[50];
    printf("Enter promo code to apply here (or press Enter to skip): ");
    fgets(code, sizeof(code), stdin);
    trim_newline(code);
    double final = total;
    if (code[0]!='\0') {
        char promo[]="Eid2025"; int k=0, match=1;
        while (code[k]!='\0' || promo[k]!='\0') { 
		if (code[k] != promo[k]) { 
		match=0; break; } k++; }
        if (match) final = total * 0.75;
    }
    printf("Total payable: %.2f\n", final);
}
void exitsystem(){
	printf("\nExiting the program...\n");
    printf("Thank you for using Supermarket Inventory Management System!\n");
    ch='n';
}
//main starts here
int main(){
	int choice, i; char message[200];
	do{
		printf("\n\t\t\t ***********Supermarket Inventory Management System*********** \n");
		printf("\n1. Customer Info");
		printf("\n2. Display Inventory");
		printf("\n3. Add items to cart");
		printf("\n4. Total Bill Calculate");
		printf("\n5. Show Invoice");
		printf("\n6. Exit");
		printf("\n\t\t\t =======================================\n\t\tEnter your choice (1-6): ");
		scanf(" %d", &choice);
		getchar();
		switch(choice){
			case 1:
				customer_info(); 
				printf("\t\t\t =======================================\n");
				printf("Do you want to continue? Press Y if yes: ");
				scanf(" %c", &ch);
				break;
			case 2:
				display_inventory();
				printf("\t\t\t =======================================\n");
				printf("Do you want to continue? Press Y if yes: ");
				scanf(" %c", &ch);
				break;
			case 3:
				addtocart();
				printf("\t\t\t =======================================\n");
				printf("Do you want to continue? Press Y if yes: ");
				scanf(" %c", &ch);
				break;
			case 4:
				display_total_bill();
				printf("\t\t\t =======================================\n");
				printf("Do you want to continue? Press Y if yes: ");
				scanf(" %c", &ch);
				break;	
			case 5:
				show_invoice(); 
				printf("\t\t\t =======================================\n");
				printf("Do you want to continue? Press Y if yes: ");
				scanf(" %c", &ch);
				break;
			case 6:
				exitsystem(); 
				break;
			default:
				printf("\t\t\t =======================================\n");
				printf("Do you want to continue? Press Y if yes: ");
				scanf(" %c", &ch);
		}
	}while(ch=='y'|| ch=='Y');
	return 0;
}

