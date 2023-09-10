#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

struct LinkedList {
    struct Node* head;
    struct Node* tail;
    int size;
};

void initializeLinkedList(struct LinkedList* list) {
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

void addToLinkedList(struct LinkedList* list, int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = list->tail;

    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        list->tail->next = newNode;
        list->tail = newNode;
    }

    list->size++;
}

void deleteFromLinkedList(struct LinkedList* list) {
    if (list->size == 0) {
        return;
    } else if (list->size == 1) {
        free(list->head);
        list->head = NULL;
        list->tail = NULL;
    } else {
        struct Node* current = list->tail->prev;
        free(list->tail);
        list->tail = current;
        list->tail->next = NULL;
    }

    list->size--;
}

void GetTrump(struct LinkedList* list) {
    if (list->size == 0) {
        printf("No customers\n");
    } else {
        struct Node* middle1 = list->head;
        struct Node* middle2 = list->head;

        while (middle2->next != NULL && middle2->next->next != NULL) {
            middle1 = middle1->next;
            middle2 = middle2->next->next;
        }

        if (list->size % 2 == 1) {
            printf("%d\n", middle1->data);
        } else {
            printf("%d %d\n", middle1->data, middle1->next->data);
        }
    }
}

int main() {
    struct LinkedList linkedList;
    initializeLinkedList(&linkedList);

    char filename[100];

    printf("Enter the filename: ");
    scanf("%s", filename);

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("File not found.\n");
        return 1;
    }

    char command[10];
    int number;

    while (1) {
        if (fscanf(file, "%s", command) == EOF) {
            break;
        }

        if (strcmp(command, "ADD") == 0) {
            if (fscanf(file, "%d", &number) == EOF) {
                break;
            }
            addToLinkedList(&linkedList, number);
        } else if (strcmp(command, "DELETE") == 0) {
            deleteFromLinkedList(&linkedList);
        } else if (strcmp(command, "END") == 0) {
            break;
        }
    }

    GetTrump(&linkedList);

    while (linkedList.head != NULL) {
        struct Node* temp = linkedList.head;
        linkedList.head = linkedList.head->next;
        free(temp);
    }

    fclose(file);
    return 0;
}
