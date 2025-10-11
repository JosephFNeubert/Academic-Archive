#include <stdio.h>

int main()
{
    int age = -1;
    
    printf("What's your age: ");
    scanf("%d", &age);
    
    if (age >= 0 && age <= 130)
    {
        printf("This age is valid.\n");
    }
    else
    {
        printf("This age is not valid.\n");
    }
    return 0;
}
