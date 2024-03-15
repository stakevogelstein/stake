#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MENU_COLOR_COUNT 7

typedef struct {
    char name[50];
    float price;
} Food;

void loadMenu(Food *menu, int *count) {
    FILE *file = fopen("menu.txt", "r");
    if (file == NULL) {
        printf("Unable to open file.\n");
        return;
    }
    char line[100];
    while (fgets(line, sizeof(line), file)) {
        char *lastSpace = strrchr(line, ' ');
        if (lastSpace) {
            *lastSpace = '\0'; 
            strcpy(menu[*count].name, line);
            menu[*count].price = atof(lastSpace + 1);
            (*count)++;
        }
    }
    fclose(file);
}


void saveMenu(Food *menu, int count) {
	int i;
    FILE *file = fopen("menu.txt", "w");
    if (file == NULL) {
        printf("Unable to open file.\n");
        return;
    }
    for (i = 0; i < count; i++) {
        fprintf(file, "%s %.2f\n", menu[i].name, menu[i].price);
    }
    fclose(file);
}

void addFood(Food *menu, int *count) {
    FILE *file = fopen("menu.txt", "a");
    if (file == NULL) {
        printf("Unable to open file.\n");
        return;
    }
    printf("Enter food name: ");
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
    fgets(menu[*count].name, sizeof(menu[*count].name), stdin);
    menu[*count].name[strcspn(menu[*count].name, "\n")] = 0;
    printf("Enter food price: ");
    scanf("%f", &menu[*count].price);
    fprintf(file, "%s %.2f\n", menu[*count].name, menu[*count].price);
    fclose(file);
    (*count)++;
    char choice;
    printf("Do you want to return to the main menu? (y/n): ");
    scanf(" %c", &choice);
    if (choice == 'n' || choice == 'N') {
        printf("Exiting...\n");
        exit(0);
    }
}

void editFood(Food *menu, int count) {
	int i;
    char name[50];
    printf("Enter food name to edit: ");
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0; 
    for (i = 0; i < count; i++) {
        if (strcmp(menu[i].name, name) == 0) {
            printf("Enter new food name: ");
            while ((c = getchar()) != '\n' && c != EOF) { }
            fgets(menu[i].name, sizeof(menu[i].name), stdin);
            menu[i].name[strcspn(menu[i].name, "\n")] = 0; 
            printf("Enter new food price: ");
            while ((c = getchar()) != '\n' && c != EOF) { } 
            scanf("%f", &menu[i].price);
            saveMenu(menu, count);
            return;
        }
    }
    printf("Food not found.\n");
     char choice;
    printf("Do you want to return to the main menu? (y/n): ");
    scanf(" %c", &choice);
    if (choice == 'n' || choice == 'N') {
        printf("Exiting...\n");
        exit(0);
    }
}

void searchFood(Food *menu, int count) {
    int option;
    printf("Search by:\n1. Food name\n2. Food price\nChoose your option: ");
    scanf("%d", &option);
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { } 
    switch(option) {
        case 1: {
            char searchName[50];
            printf("Enter food name to search: ");
            fgets(searchName, sizeof(searchName), stdin);
            searchName[strcspn(searchName, "\n")] = 0; 
            printf("\n| %-50s | %-10s |\n", "Food Name", "Food Price");
            printf("|-%-50s-|-%-10s-|\n", "--------------------------------------------------", "----------");
            int i;
            for (i = 0; i < count; i++) {
                if (strcmp(menu[i].name, searchName) == 0) {
                    printf("| %-50s | %-10.2f |\n", menu[i].name, menu[i].price);
                }
            }
            break;
        }
        case 2: {
            float searchPrice;
            printf("Enter food price to search: ");
            scanf("%f", &searchPrice);
            printf("\n| %-50s | %-10s |\n", "Food Name", "Food Price");
            printf("|-%-50s-|-%-10s-|\n", "--------------------------------------------------", "----------");
            int i;
            for (i = 0; i < count; i++) {
                if (menu[i].price == searchPrice) {
                    printf("| %-50s | %-10.2f |\n", menu[i].name, menu[i].price);
                }
            }
            break;
        }
        default:
            printf("Invalid option.\n");
    }
     char choice;
    printf("Do you want to return to the main menu? (y/n): ");
    scanf(" %c", &choice);
    if (choice == 'n' || choice == 'N') {
        printf("Exiting...\n");
        exit(0);
    }
}

void deleteFood(Food *menu, int *count) {
	int i, j;
    char searchName[50];
    printf("Enter food name to delete: ");
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = 0; 
    for (i = 0; i < *count; i++) {
        if (strcmp(menu[i].name, searchName) == 0) {
            char confirm;
            printf("Are you sure you want to delete %s? (y/n): ", menu[i].name);
            scanf(" %c", &confirm);
            if (confirm == 'y' || confirm == 'Y') {
                for (j = i; j < *count - 1; j++) {
                    strcpy(menu[j].name, menu[j + 1].name);
                    menu[j].price = menu[j + 1].price;
                }
                (*count)--;
                saveMenu(menu, *count);
            }
            return;
        }
    }
    printf("Food not found.\n");
     char choice;
    printf("Do you want to return to the main menu? (y/n): ");
    scanf(" %c", &choice);
    if (choice == 'n' || choice == 'N') {
        printf("Exiting...\n");
        exit(0);
    }
}

void calculateSummary(Food *menu, int count) {
    int i;
    float total = 0, min = menu[0].price, max = menu[0].price;
    for (i = 0; i < count; i++) {
        total += menu[i].price;
        if (menu[i].price < min) min = menu[i].price;
        if (menu[i].price > max) max = menu[i].price;
    }
    float average = total / count;
    printf("\n| %-30s | %-10s |\n", "Summary", "Value");
    printf("|-%-30s-|-%-10s-|\n", "------------------------------", "----------");
    printf("| %-30s | %-10d |\n", "Total number of foods", count);
    printf("| %-30s | %-10.2f |\n", "Total price of all foods", total);
    printf("| %-30s | %-10.2f |\n", "Average price of foods", average);
    printf("| %-30s | %-10.2f |\n", "Most expensive food price", max);
    printf("| %-30s | %-10.2f |\n", "Least expensive food price", min);
    char choice;
    printf("\nDo you want to return to the main menu? (y/n): ");
    scanf(" %c", &choice);
    if (choice == 'n' || choice == 'N') {
        printf("Exiting...\n");
        exit(0);
    }
}


void listFood(Food *menu, int count) {
    int i;
    printf("%2s | %-50s| %s\n","Ord", "Food Name", "Food Price");  
    printf("---- --------------------------------------------------- ------------\n");  
    for (i = 0; i < count; i++) {
        printf("%2d  | %-50s| %.2f\n",i+1, menu[i].name, menu[i].price);
    
	}
	 char choice;
    printf("Do you want to return to the main menu? (y/n): ");
    scanf(" %c", &choice);
    if (choice == 'n' || choice == 'N') {
        printf("Exiting...\n");
        exit(0);
    }
}

void printMenuHeader(int colorIndex) {
  const char* colors[] = {"\e[0;93m", "\e[1;91m", "\e[1;93m", "\e[1;92m", "\e[1;96m", "\e[1;95m", "\e[1;94m"}; // Color codes
  printf("%s", colors[colorIndex % MENU_COLOR_COUNT]); // Print color based on index

  printf("\n///////////////////////////////////////////////////////////////////");
  printf("\n  [WELCOME TO THE NHA LU HANH RESTAURANT MANAGEMENT PROGRAM]");
  printf("\n///////////////////////////////////////////////////////////////////\n");

  printf("\033[1;0m"); // Reset color to white
}

int main() {
    Food menu[100];
    int count = 0;
    loadMenu(menu, &count);
    int option;
    do {
    	int j;
        printf("\n================================================================");
        printf("\n     ");
        const char* colors[] = {"\e[1;93m"}; 
        const int num_colors = sizeof(colors) / sizeof(colors[0]);
        const char* welcome_text = "[WELCOME TO NHA LU HANH RESTAURANT MANAGEMENT PROGRAM]";
        const int text_length = strlen(welcome_text);
        for (j = 0; j < text_length; j++) {
            printf("%s%c", colors[j % num_colors], welcome_text[j]);
            fflush(stdout);
            usleep(87000); // Adjust sleep time for speed of transition
        }
        printf("\033[0m"); // Reset color
        printf("\033[1;0m");
        printf("\n================================================================\n");
        printf("\e[1;91m"); //red
        printf("\n1. [ Add food ]");
        printf("\033[1;0m"); //white
        printf("\n------------------------------------------------------");
        printf("\e[1;93m"); //yellow 
        printf("\n2. [ Edit food ]");
        printf("\033[1;0m"); //white
        printf("\n----------------------------------------");
        printf("\e[1;92m"); //green
        printf("\n3. [ Search specific food ]");
        printf("\033[1;0m"); //white
        printf("\n--------------------------");
        printf("\e[1;96m"); //cyan
        printf("\n4. [ List food ]");
        printf("\033[1;0m"); //white
        printf("\n----------------------------------------");
        printf("\e[1;95m"); //magenta
        printf("\n5. [ Delete specific food ]");
        printf("\033[1;0m"); //white
        printf("\n------------------------------------------------------");
        printf("\e[1;94m"); // blue
        printf("\n6. [ Calculate how many foods there are ]");
        printf("\033[1;0m"); //white
        printf("\n===============================================================");
        printf("\e[1;97m"); //white
        printf("\n7. [Exit]\n");
        printf("\nChoose your option: ");
        if (scanf("%d", &option) != 1) {
        	int c;
            printf("Invalid input. Please enter a number.\n");
            while ((c = getchar()) != '\n' && c != EOF) { }
            continue;
        }
        switch(option) {
            case 1:
                addFood(menu, &count);
                break;
            case 2:
                editFood(menu, count);
                break;
            case 3:
                searchFood(menu, count);
                break;
            case 4:
                listFood(menu, count);
                break;
            case 5:
                deleteFood(menu, &count);
                break;
            case 6:
                calculateSummary(menu, count);
                break;
            case 7:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid option.\n");
        }
    } while(option != 7);
    return 0;
}
