// In-Class Exercise 6 - Joseph Neubert

#include <stdio.h>

int calculateSeries(int n)
{
    if (n <= 1)
    {
        return 2 * n;
    }
    return calculateSeries(n - 1) + (2 * n);
}

int main()
{
    printf("Enter the number: ");
    int num;
    scanf("%d", &num);
    printf("S(%d) = %d", num, calculateSeries(num));
}