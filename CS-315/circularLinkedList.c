#include <stdio.h>
#include <stdlib.h>

// Definition of the node structure
struct Node
{
    int data;
    struct Node *next;
};

// Function to create a new node
struct Node *createNode(int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the end of the circular linked list
void insertEnd(struct Node **head, int data)
{
    struct Node *newNode = createNode(data);
    struct Node *temp;
    if (*head == NULL)
    {
        *head = newNode;
        newNode->next = *head;
    }
    else
    {
        temp = *head;
        while (temp->next != *head)
        {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->next = *head;
    }
}

// Function to display the circular linked list
void display(struct Node *head)
{
    struct Node *temp;
    if (head == NULL)
    {
        printf("List is empty.\n");
        return;
    }
    temp = head;
    do
    {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("\n");
}

// Main function to test the circular linked list implementation
int main()
{
    struct Node *head = NULL;

    insertEnd(&head, 10);
    insertEnd(&head, 20);
    insertEnd(&head, 30);
    insertEnd(&head, 40);

    printf("Circular Linked List: \n");
    display(head);

    return 0;
}
