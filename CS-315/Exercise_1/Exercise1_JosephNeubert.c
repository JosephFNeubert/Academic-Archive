// In-Class Exercise 1 - Joseph Neubert
#include <stdio.h>
#include <string.h>

struct Order
{
    int price;
    int quantity;
    char customerName[100];
};

void readOrder(char *fileName, struct Order *newOrder)
{
    FILE *file = fopen(fileName, "r");
    char buffer[100];

    if (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        sscanf(buffer, "%d", &newOrder->price);
    }
    if (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        sscanf(buffer, "%d", &newOrder->quantity);
    }
    fgets(newOrder->customerName, sizeof(newOrder->customerName), file);
    fclose(file);
}

int main()
{
    struct Order myOrder;
    myOrder.price = 15;
    myOrder.quantity = 1;
    strcpy(myOrder.customerName, "Bob");

    FILE *file = fopen("order.txt", "w");
    fprintf(file, "%d\n", myOrder.price);
    fprintf(file, "%d\n", myOrder.quantity);
    fprintf(file, "%s", myOrder.customerName);
    fclose(file);

    struct Order newOrder;
    readOrder("order.txt", &newOrder);
    printf("%d\n", newOrder.price);
    printf("%d\n", newOrder.quantity);
    printf("%s\n", newOrder.customerName);

    return 0;
}
