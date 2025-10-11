/****************************************************************************
 * File:      Hw2_JosephNeubert.c
 * Author:    Joseph Neubert
 * Purpose:   To organize and modify a Minecraft inventory via linked lists
 * Version:   1.0 Sept 30, 2024
 * Resources: ChatGPT assisted in the debugging
 *******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Struct for Minecraft a Minecraft resource
struct Resource
{
    char type[64];
    int quantity;
    struct Resource *next;
};

// Function to traverse and perform additional operations on the linked list
void modifyInventory(struct Resource **head, char newType[64], int newQuantity, char action[15])
{
    struct Resource *temp = *head;
    struct Resource *newResource = (struct Resource *)malloc(sizeof(struct Resource));
    struct Resource *prev = NULL;
    strcpy(newResource->type, newType);
    newResource->quantity = newQuantity;
    newResource->next = NULL;

    // For addition upon "collect"
    if (strcmp(action, "collect") == 0)
    {
        while (temp != NULL && strcmp(newResource->type, temp->type) > 0)
        {
            prev = temp;
            temp = temp->next;
        }
        if (temp != NULL && strcmp(newResource->type, temp->type) == 0)
        {
            temp->quantity += newResource->quantity;
            free(newResource);
        }
        else
        {
            if (prev == NULL)
            {
                newResource->next = *head;
                *head = newResource;
            }
            else
            {
                prev->next = newResource;
                newResource->next = temp;
            }
        }
    }

    // For subtraction upon "use"
    else if (strcmp(action, "use") == 0)
    {
        while (temp != NULL && strcmp(newResource->type, temp->type) != 0)
        {
            prev = temp;
            temp = temp->next;
        }
        if (temp == NULL)
        {
            printf("Resource %s not found.\n", newResource->type);
        }
        else
        {
            int currentQuantity = temp->quantity;
            temp->quantity -= newResource->quantity;
            if (temp->quantity <= 0)
            {
                if (temp->quantity < 0)
                    printf("Request for %d %s is more than available %d.\n", newResource->quantity, newResource->type, currentQuantity);
                if (prev == NULL)
                {
                    *head = temp->next;
                }
                else
                {
                    prev->next = temp->next;
                }
                free(temp);
            }
        }
        free(newResource);
    }
    else
    {
        printf("There has been a major error and the file couldn't be successfully processed.\n");
        free(newResource);
        return;
    }
}

// Function to display the linked list
void displayInventory(struct Resource *head)
{
    struct Resource *temp = head;
    printf("*************Resources*************\n");
    while (temp != NULL)
    {
        printf("%s %d\n", temp->type, temp->quantity);
        temp = temp->next;
    }
}

int main()
{
    struct Resource *inventory = NULL;
    FILE *file;
    char fileName[100];

    char action[15];
    char resourceName[64];
    int resourceQuantity;
    printf("Please type in the exact name of the file to read from (press 'q' to quit): ");
    scanf("%s", fileName);
    while (strcmp(fileName, "q") != 0)
    {
        file = fopen(fileName, "r");
        if (file == NULL)
        {
            printf("Not a valid file name. Please try again.\n");
        }
        else
        {
            while (fscanf(file, "%s %s %d", action, resourceName, &resourceQuantity) == 3)
            {
                modifyInventory(&inventory, resourceName, resourceQuantity, action);
            }
            fclose(file);
            displayInventory(inventory);
        }

        inventory = NULL;
        printf("Please type in the exact name of the file to read from (press 'q' to quit): ");
        scanf("%s", fileName);
    }
    return 0;
}