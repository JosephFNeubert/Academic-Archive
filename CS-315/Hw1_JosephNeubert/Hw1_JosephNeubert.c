/****************************************************************************
 * File:      Hw1_JosephNeubert.c
 * Author:    Joseph Neubert
 * Purpose:   TODO
 * Version:   1.0 Sept 17, 2024
 * Resources: ChatGPT gave me a reminder of how to use fscanf for reading from files
 *******************************************************************************/

#include <stdio.h>
#include <string.h>

struct client
{
    char name[100];
    double price;
};

int countSeller = 0;
int countBuyer = 0;
void readClientData(char fileName[100], struct client buyers[], struct client sellers[])
{
    char name[100];
    char type[7];
    double price;
    FILE *file = fopen(fileName, "r");
    while (fscanf(file, "%s %s %lf", name, type, &price) == 3)
    {
        if (strcmp(type, "Seller") == 0)
        {
            strcpy(sellers[countSeller].name, name);
            sellers[countSeller].price = price;
            countSeller++;
        }
        else if (strcmp(type, "Buyer") == 0)
        {
            strcpy(buyers[countBuyer].name, name);
            buyers[countBuyer].price = price;
            countBuyer++;
        }
    }
    fclose(file);
}

int main()
{
    struct client buyers[100];
    struct client sellers[100];
    char fileNames[4][100] = {"file1.txt", "file2.txt", "file3.txt", "file4.txt"};

    for (int i = 0; i < 4; i++)
    {
        readClientData(fileNames[i], buyers, sellers);
    }

    for (int i = 0; i < countBuyer; i++)
    {
        printf("Name: %s, Price: %.2f\n", buyers[i].name, buyers[i].price);
    }
    printf("\n");
    for (int i = 0; i < countSeller; i++)
    {
        printf("Name: %s, Price: %.2f\n", sellers[i].name, sellers[i].price);
    }
    return 0;
}