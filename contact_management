#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTACTS 100
#define MAX_NAME 50
#define MAX_PHONE 15

typedef struct {
    char name[MAX_NAME];
    char phone[MAX_PHONE];
    char email[50];
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
    printf("Added successfully!\n");
}

void displayContacts() {
    printf("\n--- All Contacts (%d) ---\n", contactCount);
    for (int i = 0; i < contactCount; i++) {
        printf("%d. Name: %s\n", i+1, contacts[i].name);
        printf("   Phone: %s\n", contacts[i].phone);
        printf("   Email: %s\n", contacts[i].email);
    }
}

void searchContact() {
    char searchName[MAX_NAME];
    printf("Enter name to search: ");
    scanf(" %[^\n]", searchName);
   
    int found = 0;
    for (int i = 0; i < contactCount; i++) {
        if (strstr(contacts[i].name, searchName) != NULL) {
            printf("\nFound Contact:\n");
            printf("Name: %s\n", contacts[i].name);
            printf("Phone: %s\n", contacts[i].phone);
            printf("Email: %s\n", contacts[i].email);
            found = 1;
        }
    }
   
    if (!found) {
        printf("Not found.\n");
    }
}

int main() {
    int choice;
   
    do {
        printf("\n=== CONTACT MANAGEMENT ===\n");
        printf("1. Add Contact\n");
        printf("2. View All Contacts\n");
        printf("3. Search Contact\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
       
        switch (choice) {
            case 1: addContact(); break;
            case 2: displayContacts(); break;
            case 3: searchContact(); break;
            case 4: printf("Goodbye!\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 4);
   
    return 0;
}
