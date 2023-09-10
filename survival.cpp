#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure for a node in the linked list
struct Node {
    int data;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode != NULL) {
        newNode->data = data;
        newNode->next = NULL;
    }
    return newNode;
}

// Function to insert a node into a sorted linked list
void insertSorted(struct Node** head, int data) {
    struct Node* newNode = createNode(data);

    if (*head == NULL || data < (*head)->data) {
        newNode->next = *head;
        *head = newNode;
    } else {
        struct Node* current = *head;
        while (current->next != NULL && current->next->data < data) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

// Function to calculate the median of the linked list
double calculateMedian(struct Node* head) {
    struct Node* slowPtr = head;
    struct Node* fastPtr = head;
    struct Node* prevSlowPtr = NULL;

    while (fastPtr != NULL && fastPtr->next != NULL) {
        fastPtr = fastPtr->next->next;
        prevSlowPtr = slowPtr;
        slowPtr = slowPtr->next;
    }

    if (fastPtr == NULL) {
        // Even number of elements, so the median is the average of two middle elements
        return (double)(prevSlowPtr->data + slowPtr->data) / 2.0;
    } else {
        // Odd number of elements, so the median is the middle element
        return (double)slowPtr->data;
    }
}

int main() {
    struct Node* head = NULL;
    int num;
    char fileName[256]; // Assuming a maximum file name length of 255 characters

    printf("Enter the input file name: ");
    scanf("%s", fileName);

    FILE* inputFile = fopen(fileName, "r"); // Open the input file in read mode

    if (inputFile == NULL) {
        perror("Error opening the input file");
        return 1;
    }

    while (fscanf(inputFile, "%d", &num) != EOF) {
        insertSorted(&head, num);
        double median = calculateMedian(head);
        printf("%d Median: %.1lf\n", num, median);
    }

    fclose(inputFile); // Close the input file

    // Free allocated memory
    while (head != NULL) {
        struct Node* temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
