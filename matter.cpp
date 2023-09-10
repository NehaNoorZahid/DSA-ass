#include <stdio.h>
#include <stdlib.h>

// Define a structure for a node in the linked list
struct Node {
    int data;
    struct Node* next;
};

// Function to find the third last element of the linked list
int findThirdLast(struct Node* head) {
    if (head == NULL || head->next == NULL || head->next->next == NULL) {
        return -1; // Less than three elements in the list
    }

    struct Node* current = head;
    struct Node* secondLast = head;
    struct Node* thirdLast = head;

    // Traverse the list
    while (current->next != NULL) {
        current = current->next;
        if (current->next != NULL) {
            thirdLast = secondLast;
            secondLast = current;
        }
    }

    return thirdLast->data;
}

// Function to insert a new element at the end of the linked list
void insertAtEnd(struct Node** head, int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
    } else {
        struct Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

int main() {
    struct Node* head = NULL;
    int data;
    char fileName[100];

    // Prompt the user to enter the input file name
    printf("Enter the input file name: ");
    scanf("%s", fileName);

    // Open the input file for reading
    FILE* inputFile = fopen(fileName, "r");
    if (inputFile == NULL) {
        printf("Error opening input file.\n");
        return 1;
    }

    // Read the elements from the file until the end of the file
    while (fscanf(inputFile, "%d", &data) != EOF) {
        insertAtEnd(&head, data);
    }

    int result = findThirdLast(head);
    if (result != -1) {
        printf("The third last element is: %d\n", result);
    } else {
        printf("-1 \n");
    }

    // Free the allocated memory
    while (head != NULL) {
        struct Node* temp = head;
        head = head->next;
        free(temp);
    }

    // Close the input file
    fclose(inputFile);

    return 0;
}

