#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char data[255];
    struct Node* next;
} Node;

Node* push(Node* head, char* line) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    int i = 0;
    while (line[i] != '\0' && line[i] != '\n' && i < 254) {
        newNode->data[i] = line[i];
        i++;
    }
    newNode->data[i] = '\0';
    newNode->next = head;
    return newNode;
}

Node* pop(Node* head) {
    if (!head) {
        printf("Stack is empty.\n");
        return NULL;
    }
    Node* temp = head;
    head = head->next;
    printf("Popped: %s\n", temp->data);
    free(temp);
    return head;
}

void purge(Node** head) {
    while (*head) {
        Node* temp = *head;
        *head = (*head)->next;
        free(temp);
    }
    printf("Stack has been purged.\n");
}

void renumber(Node* head) {
    int lineNumber = 1;
    while (head) {
        printf("%d: %s\n", lineNumber, head->data);
        head = head->next;
        lineNumber++;
    }
}

void printFileContents(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Can't open the file:(\n");
        return;
    }
    char line[255];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    fclose(file);
}

Node* LoadFileToStack(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Can't open the file\n");
        return NULL;
    }
    Node* stack = NULL;
    char line[255];
    while (fgets(line, sizeof(line), file)) {
        stack = push(stack, line);
    }
    fclose(file);
    printf("File loaded into stack.\n");
    return stack;
}

int main() {
    Node* stack = NULL;
    int choice;

    while (1) {
        printf("\nMenu:\n");
        printf("1: Print file contents\n");
        printf("2: Load file into stack\n");
        printf("3: Print and free stack\n");
        printf("4: Exit\n");
        printf("Enter the number of your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("\nDefault text from the file:\n");
            printFileContents("meow.txt");
            break;
        case 2:
            stack = LoadFileToStack("meow.txt");
            break;
        case 3:
            if (!stack) {
                printf("Stack is empty.\n");
            }
            else {
                printf("\nStack contents:\n");
                renumber(stack);
                purge(&stack);
            }
            break;
        case 4:
            printf("Exiting program.\n");
            purge(&stack);
            return 0;
        default:
            printf("There is no choise with this numb, please try again.\n");
        }
    }
}
