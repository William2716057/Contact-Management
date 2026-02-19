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
        for (int i = found; i < contactCount - 1; i++) {
            contacts[i] = contacts[i + 1];
        }
        contactCount--;
        printf("Contact deleted successfully.\n");
    } else {
        printf("Contact not found.\n");
    }
}

// ============ JSON FUNCTIONS ============

void saveToJSON() {
    FILE *file = fopen("contacts.json", "w");
    if (file == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }
   
    fprintf(file, "{\n");
    fprintf(file, "  \"contacts\": [\n");
   
    for (int i = 0; i < contactCount; i++) {
        fprintf(file, "    {\n");
        fprintf(file, "      \"name\": \"%s\",\n", contacts[i].name);
        fprintf(file, "      \"phone\": \"%s\",\n", contacts[i].phone);
        fprintf(file, "      \"email\": \"%s\"\n", contacts[i].email);
       
        if (i < contactCount - 1) {
            fprintf(file, "    },\n");
        } else {
            fprintf(file, "    }\n");
        }
    }
   
    fprintf(file, "  ]\n");
    fprintf(file, "}\n");
   
    fclose(file);
    printf("Contacts saved to 'contacts.json' in JSON format.\n");
}

void loadFromJSON() {
    FILE *file = fopen("contacts.json", "r");
    if (file == NULL) {
        printf("No existing contacts file found. Starting fresh.\n");
        return;
    }
   
    char line[256];
    contactCount = 0;
   
    while (fgets(line, sizeof(line), file) && contactCount < MAX_CONTACTS) {
        if (strstr(line, "\"name\"")) {
            char *start = strchr(line, ':') + 1;
            while (*start == ' ' || *start == '\"') start++;
            char *end = strchr(start, '\"');
            if (end) {
                *end = '\0';
                strcpy(contacts[contactCount].name, start);
            }
        }
       
        if (strstr(line, "\"phone\"")) {
            char *start = strchr(line, ':') + 1;
            while (*start == ' ' || *start == '\"') start++;
            char *end = strchr(start, '\"');
            if (end) {
                *end = '\0';
                strcpy(contacts[contactCount].phone, start);
            }
        }
       
        if (strstr(line, "\"email\"")) {
            char *start = strchr(line, ':') + 1;
            while (*start == ' ' || *start == '\"') start++;
            char *end = strchr(start, '\"');
            if (end) {
                *end = '\0';
                strcpy(contacts[contactCount].email, start);
                contactCount++;
            }
        }
    }
   
    fclose(file);
    printf("Loaded %d contacts from JSON file.\n", contactCount);
}

// ============ VIEW RAW JSON ============

void viewJSON() {
    FILE *file = fopen("contacts.json", "r");
    if (file == NULL) {
        printf("No JSON file found.\n");
        return;
    }
   
    printf("\n--- Raw JSON Content ---\n");
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }
   
    fclose(file);
}

int main() {
    int choice;
   
    loadFromJSON();
   
    do {
        printf("\n=== CONTACT MANAGEMENT SYSTEM ===\n");
        printf("1. Add Contact\n");
        printf("2. View All Contacts\n");
        printf("3. Search Contact\n");
        printf("4. Delete Contact\n");
        printf("5. Exit\n");
        printf("Enter choice (1-7): ");
       
        if (scanf("%d", &choice) != 1) {
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
                printf("\nSaving contacts before exit...\n");
                saveToJSON();
                printf("Program ended!\n");
                break;
            default:
                printf("Invalid choice! Please enter 1-5.\n");
        }
    } while (choice != 5);
   
    return 0;
}
