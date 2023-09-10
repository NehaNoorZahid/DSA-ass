#include <stdio.h>
#include <stdlib.h>

// Define a structure for a transaction
struct Transaction {
    int id;
    int amount;
    struct Transaction* next;
};

// Function to create a new transaction
struct Transaction* createTransaction(int id, int amount) {
    struct Transaction* newNode = (struct Transaction*)malloc(sizeof(struct Transaction));
    newNode->id = id;
    newNode->amount = amount;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a transaction at the end of the list
void insertTransaction(struct Transaction** head, int id, int amount) {
    struct Transaction* newNode = createTransaction(id, amount);
    if (*head == NULL) {
        *head = newNode;
    } else {
        struct Transaction* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Function to reverse fraudulent transactions
void reverseFraudulentTransactions(struct Transaction** head, int* fraudulentIds, int numFraudulent) {
    struct Transaction* current = *head;
    struct Transaction* prev = NULL;

    while (current != NULL) {
        int isFraudulent = 0;
        for (int i = 0; i < numFraudulent; i++) {
            if (current->id == fraudulentIds[i]) {
                isFraudulent = 1;
                break;
            }
        }

        if (!isFraudulent) {
            prev = current;
            current = current->next;
        } else {
            struct Transaction* temp = current;
            if (prev != NULL) {
                prev->next = current->next;
            } else {
                *head = current->next;
            }
            current = current->next;
            free(temp);
        }
    }
}

// Function to print the transactions
void printTransactions(struct Transaction* head) {
    struct Transaction* current = head;
    while (current != NULL) {
        printf("%d,%d\n", current->id, current->amount);
        current = current->next;
    }
}

int main() {
    int numTransactions, numFraudulent;
    char fileName[256]; // Assuming a maximum file name length of 255 characters

    printf("Enter the input file name: ");
    scanf("%s", fileName);

    FILE* inputFile = fopen(fileName, "r"); // Open the input file in read mode

    if (inputFile == NULL) {
        perror("Error opening the input file");
        return 1;
    }

    fscanf(inputFile, "%d %d", &numTransactions, &numFraudulent);

    struct Transaction* transactionList = NULL;

    for (int i = 0; i < numTransactions; i++) {
        int id, amount;
        fscanf(inputFile, "%d,%d", &id, &amount);
        insertTransaction(&transactionList, id, amount);
    }

    int fraudulentIds[numFraudulent];
    for (int i = 0; i < numFraudulent; i++) {
        fscanf(inputFile, "%d", &fraudulentIds[i]);
    }

    fclose(inputFile); // Close the input file

    reverseFraudulentTransactions(&transactionList, fraudulentIds, numFraudulent);
    printTransactions(transactionList);

    // Free allocated memory
    while (transactionList != NULL) {
        struct Transaction* temp = transactionList;
        transactionList = transactionList->next;
        free(temp);
    }

    return 0;
}