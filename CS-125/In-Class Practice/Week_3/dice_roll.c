#include <stdio.h>
#include <stdlib.h>

int main()
{
    int number = 0;
    printf("Number of times to roll: ");
    scanf("%d", &number);

    int i = 0;
    for(i = 0; i < number; i++)
    {
        int roll = rand()%6 + 1;
        printf("You rolled %d", roll);
    }
    return 0;
}

