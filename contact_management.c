#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTACTS 100
#define MAX_NAME 50
#define MAX_PHONE 15
#define MAX_EMAIL 50

typedef struct {
    char name[MAX_NAME];
    char phone[MAX_PHONE];
    char email[MAX_EMAIL];
} Contact;

Contact contacts[MAX_CONTACTS];
int contactCount = 0;

void addContact() {
    if (contactCount >= MAX_CONTACTS) {
        printf("Contact list full!\n");
        return;
    }
   
    printf("\n--- Add New Contact ---\n");
    printf("Name: ");
    scanf(" %[^\n]", contacts[contactCount].name);
   
    printf("Phone: ");
    scanf("%s", contacts[contactCount].phone);
   
    printf("Email: ");
    scanf("%s", contacts[contactCount].email);
   
    contactCount++;
    printf("Contact added successfully!\n");
}

void displayContacts() {
    if (contactCount == 0) {
        printf("\nNo contacts to display.\n");
        return;
    }
   
    printf("\n--- All Contacts (%d) ---\n", contactCount);
    for (int i = 0; i < contactCount; i++) {
        printf("\n%d. Name: %s\n", i+1, contacts[i].name);
        printf("   Phone: %s\n", contacts[i].phone);
        printf("   Email: %s\n", contacts[i].email);
    }
}

void searchContact() {
    if (contactCount == 0) {
        printf("\nNo contacts to search.\n");
        return;
    }
   
    char searchTerm[MAX_NAME];
    printf("Enter name, phone or email to search: ");
    scanf(" %[^\n]", searchTerm);
   
    int found = 0;
    printf("\n--- Search Results ---\n");
   
    for (int i = 0; i < contactCount; i++) {
        // Search in name, phone, and email
        if (strstr(contacts[i].name, searchTerm) != NULL ||
            strstr(contacts[i].phone, searchTerm) != NULL ||
            strstr(contacts[i].email, searchTerm) != NULL) {
           
            printf("\n%d. Name: %s\n", i+1, contacts[i].name);
            printf("   Phone: %s\n", contacts[i].phone);
            printf("   Email: %s\n", contacts[i].email);
            found = 1;
        }
    }
   
    if (!found) {
        printf("No contacts found matching '%s'.\n", searchTerm);
    }
}

void deleteContact() {
    if (contactCount == 0) {
        printf("\nNo contacts to delete.\n");
        return;
    }
   
    char searchName[MAX_NAME];
    printf("Enter name of contact to delete: ");
    scanf(" %[^\n]", searchName);
   
    int found = -1;
    for (int i = 0; i < contactCount; i++) {
        if (strcmp(contacts[i].name, searchName) == 0) {
            found = i;
            break;
        }
    }
   
    if (found >= 0) {
        // Shift all contacts after the found index
        for (int i = found; i < contactCount - 1; i++) {
            contacts[i] = contacts[i + 1];
        }
        contactCount--;
        printf("Contact deleted successfully.\n");
    } else {
        printf("Contact not found.\n");
    }
}

void saveToFile() {
    FILE *file = fopen("contacts.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }
   
    fprintf(file, "%d\n", contactCount);
    for (int i = 0; i < contactCount; i++) {
        fprintf(file, "%s\n%s\n%s\n",
                contacts[i].name,
                contacts[i].phone,
                contacts[i].email);
    }
   
    fclose(file);
    printf("Contacts saved to 'contacts.txt'.\n");
}

void loadFromFile() {
    FILE *file = fopen("contacts.txt", "r");
    if (file == NULL) {
        printf("No existing contacts file found. Starting fresh.\n");
        return;
    }
   
    fscanf(file, "%d\n", &contactCount);
    for (int i = 0; i < contactCount; i++) {
        fgets(contacts[i].name, MAX_NAME, file);
        contacts[i].name[strcspn(contacts[i].name, "\n")] = 0; // Remove newline
       
        fgets(contacts[i].phone, MAX_PHONE, file);
        contacts[i].phone[strcspn(contacts[i].phone, "\n")] = 0;
       
        fgets(contacts[i].email, MAX_EMAIL, file);
        contacts[i].email[strcspn(contacts[i].email, "\n")] = 0;
    }
   
    fclose(file);
    printf("Loaded %d contacts from file.\n", contactCount);
}

int main() {
    int choice;
   
    // Load existing contacts at startup
    loadFromFile();
   
    do {
        printf("\n=== CONTACT MANAGEMENT SYSTEM ===\n");
        printf("1. Add Contact\n");
        printf("2. View All Contacts\n");
        printf("3. Search Contact\n");
        printf("4. Delete Contact\n");
        printf("5. Save to File\n");
        printf("6. Exit\n");
        printf("Enter choice (1-6): ");
       
        if (scanf("%d", &choice) != 1) {
            // Clear input buffer if invalid input
            while (getchar() != '\n');
            printf("Invalid input! Please enter a number.\n");
            continue;
        }
       
        switch (choice) {
            case 1:
                addContact();
                break;
            case 2:
                displayContacts();
                break;
            case 3:
                searchContact();
                break;
            case 4:
                deleteContact();
                break;
            case 5:
                saveToFile();
                break;
            case 6:
                printf("\nSaving contacts before exit...\n");
                saveToFile();
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice! Please enter 1-6.\n");
        }
    } while (choice != 6);
   
    return 0;
}
