#include <stdio.h>


double getGallonsFromUser()
{
    double gallons = 0;
    printf("Enter number of gallons: ");
    scanf("%lf", &gallons);
    return gallons;
}


double convertGallonsToLiters(double gallons)
{
    return gallons * 3.8;
}


int main()
{
    printf("%.2lf\n", convertGallonsToLiters(getGallonsFromUser()));
    printf("%X\n", 0xC3 | 0xA6);
    printf("%x\n", 0x3A);
    return 0;
}
