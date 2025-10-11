#include<stdio.h>

int main()
{
    int count = 0;
    int num = 0;

    while (count < 5)
    {
        printf("Enter a number:");
        scanf("%d", &num);
        if (num % 2== 0)
        {
            printf("Even number!\n"); 
        } 
        else 
        {
            printf("Odd number!\n");
        } 
        count++;
    }
    return 0;
}

