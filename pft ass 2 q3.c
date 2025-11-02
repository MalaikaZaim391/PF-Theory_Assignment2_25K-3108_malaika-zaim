#include<stdio.h>
#define rows 5
#define cols 5
// below are bit 0 bit 1 and bit 2
#define power (1<<0)
#define overload (1<<1)
#define maintenance (1<<2)
char ch='y';
int grid[rows][cols]={0};
void updatesector(int grid[][cols]){
	int r,c;
	int choice;
	int action;
	printf("Enter row (0 to %d): ", rows-1);
    scanf("%d", &r);
    printf("Enter column (0 to %d): ", cols-1);
    scanf("%d", &c);
    if (r<0 || r>=rows || c<0 || c>=cols) {
        printf("Invalid coordinates! Please try again.\n");
        return;  
    }
    printf("\nSelect which status flag to modify:\n");
    printf("1. Power Status (Bit 0)\n");
    printf("2. Overload Warning (Bit 1)\n");
    printf("3. Maintenance Required (Bit 2)\n");
    printf("Enter your choice (1-3): ");
    scanf("%d", &choice);
    printf("Enter 1 to SET (turn on) or 0 to CLEAR (turn off): ");
    scanf("%d", &action);
    switch(choice){
        case 1: 
            if(action == 1) {
            	grid[r][c] = grid[r][c] | (1 << 0);
			}
            else {
            	grid[r][c] = grid[r][c] & ~(1 << 0);
			}
            break;
        case 2: 
            if(action == 1){
            	grid[r][c] = grid[r][c] | (1 << 1);
			}
            else{
            	grid[r][c] = grid[r][c] & ~(1 << 1);
			}
            break;
        case 3: 
            if(action == 1){
            	grid[r][c] = grid[r][c] | (1 << 2);
			}    
            else{
            	grid[r][c] = grid[r][c] & ~(1 << 2);
			}
            break;
        default:
            printf("Invalid flag selection. Try Again.\n");
            return;
    }
        printf("\nSector (%d,%d) updated successfully! New encoded value: %d\n", r, c, grid[r][c]);
	printf("\t\t\t =======================================\n");
    printf("Do you want to continue? Press Y if yes: ");
    scanf(" %c", &ch);
}
void querysector(int grid[][cols]){
	int r,c;
	printf("Enter row (0 to %d): ", rows-1);
    scanf("%d", &r);
    printf("Enter column (0 to %d): ", cols-1);
    scanf("%d", &c);
    if (r<0 || r>=rows || c<0 || c>=cols) {
        printf("Invalid coordinates! Please try again.\n");
        return;  
    }
    int value=grid[r][c];
    int power_status=value&(1 << 0);       
    int overload_status=value&(1 << 1);    
    int maintenance_status=value&(1 << 2); 
    printf("\nStatus Report for Sector (%d,%d):\n", r, c);
    if (power_status)
        printf("Power: ON\n");
    else
        printf("Power: OFF\n");

    if (overload_status)
        printf("Overload: YES (Warning!)\n");
    else
        printf("Overload: Normal\n");

    if (maintenance_status)
        printf("Maintenance Required: YES\n");
    else
        printf("Maintenance Required: NO\n");

    printf("Encoded Value: %d\n", value);
	printf("\t\t\t =======================================\n");
    printf("Do you want to continue? Press Y if yes: ");
    scanf(" %c", &ch);
}
void rundiagnostics(int grid[][cols]){
	int i, j;
	int overloaded_count = 0;
    int maintenance_count = 0;
    for(i=0; i<rows; i++) {
        for(j=0; j<cols; j++) {
            if (grid[i][j] & overload) {
    			overloaded_count++;
			}
			if (grid[i][j] & maintenance) {
    			maintenance_count++;
			}
    	}
    }
	printf("\nSystem Diagnostic Report:\n");
	printf("Total Overloaded Sectors: %d\n", overloaded_count);
	printf("Total Maintenance Required: %d\n", maintenance_count);
	printf("\t\t\t =======================================\n");
    printf("Do you want to continue? Press Y if yes: ");
    scanf(" %c", &ch);
}
void display(int grid[][cols]){
	int i,j;
	printf("\nCurrent Grid Status (raw integer values):\n");
	for(i=0; i<rows; i++) {
        for (j=0; j<cols; j++) {
            printf("%3d ", grid[i][j]);
        }
        printf("\n");
    }
	printf("\t\t\t =======================================\n");
    printf("Do you want to continue? Press Y if yes: ");
    scanf(" %c", &ch);
}
void exitsystem() {
	printf("\nExiting the program...\n");
    printf("Thank you for using IESCO Grid Monitoring System!\n");
    ch='n';
}
//main starts here
int main(){
	int choice, i;
	do{
		printf("\n\t\t\t ***********IESCO Grid Monitoring System*********** \n");
		printf("\n1. Update Sector Status (set/clear a flag)");
		printf("\n2. Query Sector Status (human-readable)");
		printf("\n3. Run System Diagnostic (count overloaded/maintenance)");
		printf("\n4. Display raw grid (integer values)");
		printf("\n5. Exit");
		printf("\n\t\t\t =======================================\n\t\tEnter your choice (1-5): ");
		scanf(" %d", &choice);
		getchar();
		switch(choice){
			case 1:
				updatesector(grid);
				break;
			case 2:
				querysector(grid);
				break;
			case 3:
				rundiagnostics(grid);
				break;
			case 4:
				display(grid);
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

