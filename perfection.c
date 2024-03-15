#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main() {
    Food menu[100];
    int count = 0;
    loadMenu(menu, &count);
    int option;
    do {
        printf("\n===================================================================");
        printf("\n     WELCOME TO THE NHA LU HANH RESTAURANT MANAGEMENT PROGRAM");
        printf("\n===================================================================");
        printf("\n1. Add food\n");
        printf("\n2. Edit food\n");
        printf("\n3. Search specific food\n");
        printf("\n4. List food\n");
        printf("\n5. Delete specific food\n");
        printf("\n6. Calculate how many foods there are\n");
        printf("\n7. Exit\n");
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






/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    while (fscanf(file, "%[^,],%f", menu[*count].name, &menu[*count].price) != EOF) {
        (*count)++;
    }
    fclose(file);
}

void saveMenu(Food *menu, int count) {
    int i;
    FILE *file = fopen("menu.txt", "a");
    if (file == NULL) {
        printf("Unable to open file.\n");
        return;
    }

    for (i = 0; i < count; i++) {
        fprintf(file, "%s,%.2f\n", menu[i].name, menu[i].price);
    }
    fclose(file);
}

int addFood(Food *menu, int *count) {
  FILE *file = fopen("menu.txt", "a");
  if (file == NULL) {
    printf("Unable to open file.\n");
    return 0; // Indicate failure
  }

  char foodName[50];
  float price;

  printf("Enter food name: ");
  if (fgets(foodName, sizeof(foodName), stdin) == NULL) {
    printf("Error reading food name.\n");
    // Handle error (e.g., clear input buffer)
    return 0;
  }
  foodName[strcspn(foodName, "\n")] = 0;

  // Consume remaining newline character
  scanf("%*[^\n]"); // Discard any remaining characters in the buffer
  getchar();          // Read and discard the newline character

  printf("Enter food price (must be a number): ");
  if (scanf("%f", &price) != 1) { // Check for successful read
    printf("Invalid price. Please enter a number.\n");
    // Clear input buffer (optional)
    do {
      scanf("%*[^\n]"); // Consume remaining input in the buffer
    } while (getchar() != '\n');
    return 0;
  }

  strcpy(menu[*count].name, foodName);
  menu[*count].price = price;

  fprintf(file, "%s %.2f\n", foodName, price);
  fclose(file);
  (*count)++;

  return 1; // Indicate success
}




void editFood(Food *menu, int count) {
    FILE *tempFile = fopen("temp.txt", "w"); // Temporary file
    if (tempFile == NULL) {
        printf("Unable to create temporary file.\n");
        return;
    }

    FILE *file = fopen("menu.txt", "r");
    if (file == NULL) {
        printf("Unable to open file.\n");
        fclose(tempFile);
        return;
    }

    char name[50], searchName[50];
    float price;
    int found = 0;

    printf("Enter food name to edit: ");
    scanf("%s", searchName);

    while (fscanf(file, "%s %f", name, &price) != EOF) {
        if (strcmp(name, searchName) == 0) {
            printf("Enter new food name: ");
            scanf("%s", name); // Using fgets is optional here
            printf("Enter new food price: ");
            scanf("%f", &price);
            found = 1;
        }
        fprintf(tempFile, "%s %.2f\n", name, price);
    }

    fclose(file);
    fclose(tempFile);

    if (!found) {
        printf("Food not found.\n");
        remove("temp.txt"); // Delete temporary file if food not found
        return;
    }

    // Replace original file with temporary file
    remove("menu.txt");
    rename("temp.txt", "menu.txt");
}

void searchFood(Food *menu, int count) {
    FILE *file = fopen("menu.txt", "r");
    if (file == NULL) {
        printf("Unable to open file.\n");
        return;
    }

    char name[50], searchName[50];
    float price, searchPrice; // Declare searchPrice variable
    int option, found = 0;

    printf("Search by:\n1. Food name\n2. Food price\nChoose your option: ");
    scanf("%d", &option);

    switch (option) {
    case 1:
        printf("Enter food name to search: ");
        scanf("%s", searchName);
        while (fscanf(file, "%s %f", name, &price) != EOF) {
            if (strcmp(name, searchName) == 0) {
                printf("Food found:\n%s %.2f\n", name, price);
                found = 1;
                break;
            }
        }
        break;
    case 2:
        printf("Enter food price to search: ");
        scanf("%f", &searchPrice); // Read searchPrice from user
        while (fscanf(file, "%s %f", name, &price) != EOF) {
            if (price == searchPrice) {
                printf("Food found:\n%s %.2f\n", name, price);
                found = 1;
                break;
            }
        }
        break;
    default:
        printf("Invalid option.\n");
    }

    fclose(file);

    if (!found) {
        printf("Food not found.\n");
    }
}

void deleteFood(Food *menu, int *count) {
    int i;
    FILE *file = fopen("menu.txt", "r");
    if (file == NULL) {
        printf("Unable to open file.\n");
        return;
    }
    char name[50], searchName[50];
    float price;
    int found = 0;
    printf("Enter food name to delete: ");
    scanf("%s", searchName);
    while (fscanf(file, "%s %f", name, &price) != EOF) {
        if (strcmp(name, searchName) != 0) {
            strcpy(menu[*count].name, name);
            menu[*count].price = price;
            (*count)++;
        } else {
            found = 1;
        }
    }
    fclose(file);
    if (!found) {
        printf("Food not found.\n");
    } else {
        file = fopen("menu.txt", "w");
        if (file == NULL) {
            printf("Unable to open file.\n");
            return;
        }
        for (i = 0; i < *count; i++) {
            fprintf(file, "%s %.2f\n", menu[i].name, menu[i].price);
        }
        fclose(file);
    }
}

void calculateSummary(Food *menu, int count) {
    FILE *file = fopen("menu.txt", "r");
    if (file == NULL) {
        printf("Unable to open file.\n");
        return;
    }

    int initialCount = count;
    char dummy[50];

    while (fscanf(file, "%s %s", menu[count].name, dummy) != EOF) {
        count++;
    }

    printf("Total number of foods: %d\n", count - initialCount);

    fclose(file);
}

void listFood(Food *menu, int count) {
  int i;
  printf("+---------------------------------------+---------+\n");
  printf("| %-50s | %-10s |\n", "Food Name", "Food Price");
  printf("+---------------------------------------+---------+\n");
  for (i = 0; i < count; i++) {
    if (menu[i].price == 0) {
      printf("| %-50s | %-10s |\n", menu[i].name, "Not Set");
    } else {
      printf("| %-50s | %10.2f |\n", menu[i].name, menu[i].price);
    }
  }
  printf("+---------------------------------------+---------+\n");
}



int main() {
    Food menu[100];
    int count = 0;
    loadMenu(menu, &count);
    int option;

    do {
        printf("\n===================================================================");
        printf("\n     WELCOME TO THE NHA LU HANH RESTAURANT MANAGEMENT PROGRAM");
        printf("\n===================================================================");
        printf("\n1. Add food\n");
        printf("\n2. Edit food\n");
        printf("\n3. Search specific food\n");
        printf("\n4. List food\n");
        printf("\n5. Delete specific food\n");
        printf("\n6. Calculate how many foods there are\n");
        printf("\n7. Exit\n");
        printf("\nChoose your option: ");
        scanf("%d", &option);
        switch (option) {
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
    } while (option != 7);
    saveMenu(menu, count);
    return 0;
}

*/



/*

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

  while ((*count) < 100 && fscanf(file, "%49[^,],%f\n", menu[*count].name, &menu[*count].price) == 2) {
    (*count)++;
    // Add null terminator after removing newline (if needed)
    menu[*count - 1].name[strcspn(menu[*count - 1].name, "\n")] = '\0';
  }
  fclose(file);
}

void saveMenu(Food *menu, int count) {
  int i;
  FILE *file = fopen("menu.txt", "w");
  if (file == NULL) {
    printf("Unable to open file for writing.\n");
    return;
  }

  for (i = 0; i < count; i++) {
    fprintf(file, "%s,%.2f\n", menu[i].name, menu[i].price);
  }

  fclose(file);
}

void addFood(Food *menu, int *count) {
  FILE *file = fopen("menu.txt", "a");
  if (file == NULL) {
    printf("Unable to open file for writing.\n");
    return;
  }

  char name[50];
  float price;

  printf("Enter food name: ");
  if (fgets(name, sizeof(name), stdin) == NULL) {
    printf("Error reading food name.\n");
    fclose(file);
    return;
  }
  // Ensure null terminator after removing newline
  name[strcspn(name, "\n")] = '\0';

  // Clear input buffer
  int c;
  while ((c = getchar()) != '\n' && c != EOF);

  printf("Enter food price (must be a number): ");
  if (scanf("%f", &price) != 1) {
    printf("Error reading food price. Please enter a number.\n");
    fclose(file);
    return;
  }

  strcpy(menu[*count].name, name);
  menu[*count].price = price;

  // Write both name and price to the file
  fprintf(file, "%s,%.2f\n", name, price);
  fclose(file);

  (*count)++;

  printf("Food added successfully!\n");
}

/*
void addFood(Food *menu, int *count) {
    FILE *file = fopen("menu.txt", "a");
    if (file == NULL) {
        printf("Unable to open file for writing.\n");
        return;
    }

    char name[50];
    float price;

    printf("Enter food name: ");
    if (fgets(name, sizeof(name), stdin) == NULL) {
        printf("Error reading food name.\n");
        fclose(file);
        return;
    }
    name[strcspn(name, "\n")] = '\0';  

 
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    printf("Enter food price (must be a number): ");
    if (scanf("%f", &price) != 1) {
        printf("Error reading food price. Please enter a number.\n");
        fclose(file);
        return;
    }

    strcpy(menu[*count].name, name);
    menu[*count].price = price;

    fprintf(file, "%s,%.2f\n", name, price);
    fclose(file);

    (*count)++;

    printf("Food added successfully!\n");
}
**/ /*
void editFood(Food *menu, int count) {
    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Unable to create temporary file.\n");
        return;
    }

    FILE *file = fopen("menu.txt", "r");
    if (file == NULL) {
        printf("Unable to open file.\n");
        fclose(tempFile);
        return;
    }

    char name[50], searchName[50];
    float price;
    int found = 0;

    printf("Enter food name to edit: ");
    scanf("%49s", searchName);

    while (fscanf(file, "%49s %f", name, &price) == 2) {
        if (strcmp(name, searchName) == 0) {
            printf("Enter new food name: ");
            scanf("%49s", name);
            printf("Enter new food price: ");
            scanf("%f", &price);
            found = 1;
        }
        fprintf(tempFile, "%s %.2f\n", name, price);
    }

    fclose(file);
    fclose(tempFile);

    if (!found) {
        printf("Food not found.\n");
        remove("temp.txt");
        return;
    }

    remove("menu.txt");
    rename("temp.txt", "menu.txt");
}

void searchFood(Food *menu, int count) {
    FILE *file = fopen("menu.txt", "r");
    if (file == NULL) {
        printf("Unable to open file.\n");
        return;
    }

    char name[50], searchName[50];
    float price, searchPrice;
    int option, found = 0;

    printf("Search by:\n1. Food name\n2. Food price\nChoose your option: ");
    scanf("%d", &option);

    switch (option) {
    case 1:
        printf("Enter food name to search: ");
        scanf("%49s", searchName);
        while (fscanf(file, "%49s %f", name, &price) == 2) {
            if (strcmp(name, searchName) == 0) {
                printf("Food found:\n%s %.2f\n", name, price);
                found = 1;
                break;
            }
        }
        break;
    case 2:
        printf("Enter food price to search: ");
        scanf("%f", &searchPrice);
        while (fscanf(file, "%49s %f", name, &price) == 2) {
            if (price == searchPrice) {
                printf("Food found:\n%s %.2f\n", name, price);
                found = 1;
                break;
            }
        }
        break;
    default:
        printf("Invalid option.\n");
        break;
    }

    fclose(file);

    if (!found) {
        printf("Food not found.\n");
    }
}

void deleteFood(Food *menu, int *count) {
    int i;
    FILE *file = fopen("menu.txt", "r");
    if (file == NULL) {
        printf("Unable to open file.\n");
        return;
    }
    char name[50], searchName[50];
    float price;
    int found = 0;
    printf("Enter food name to delete: ");
    scanf("%49s", searchName);
    while (fscanf(file, "%49s %f", name, &price) == 2) {
        if (strcmp(name, searchName) != 0) {
            strcpy(menu[*count].name, name);
            menu[*count].price = price;
            (*count)++;
        } else {
            found = 1;
        }
    }
    fclose(file);
    if (!found) {
        printf("Food not found.\n");
    } else {
        file = fopen("menu.txt", "w");
        if (file == NULL) {
            printf("Unable to open file.\n");
            return;
        }
        for (i = 0; i < *count; i++) {
            fprintf(file, "%s %.2f\n", menu[i].name, menu[i].price);
        }
        fclose(file);
    }
}

void calculateSummary(Food *menu, int count) {
    FILE *file = fopen("menu.txt", "r");
    if (file == NULL) {
        printf("Unable to open file.\n");
        return;
    }
	
    int initialCount = count;
    char name[50];
    float price;

    while (fscanf(file, "%49s %f", name, &price) == 2) {
        count++;
    }

    printf("Total number of foods: %d\n", count - initialCount);

    fclose(file);
}

void listFood(Food *menu, int count) {
    int i;
    printf("+---------------------------------------+---------+\n");
    printf("| %-50s | %-10s |\n", "Food Name", "Food Price");
    printf("+---------------------------------------+---------+\n");
    for (i = 0; i < count; i++) {
        if (menu[i].price == -1.0) {
            printf("| %-50s | %-10s |\n", menu[i].name, "Not Set");
        } else {
            printf("| %-50s | %10.2f |\n", menu[i].name ? menu[i].name : "", menu[i].price);
        }
    }
    printf("+---------------------------------------+---------+\n");
}

int main() {
	Food menu[100];
    int count = 0;
    int option;
    loadMenu(menu, &count);
    do {
        printf("\n===================================================================");
        printf("\n     WELCOME TO THE NHA LU HANH RESTAURANT MANAGEMENT PROGRAM");
        printf("\n===================================================================");
        printf("\n1. Add food\n");
        printf("\n2. Edit food\n");
        printf("\n3. Search specific food\n");
        printf("\n4. List food\n");
        printf("\n5. Delete specific food\n");
        printf("\n6. Calculate how many foods there are\n");
        printf("\n7. Exit\n");
        printf("\nChoose your option: ");
        scanf("%d", &option);
        switch (option) {
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
    } while (option != 7);
    saveMenu(menu, count);
    return 0;
}

*/
