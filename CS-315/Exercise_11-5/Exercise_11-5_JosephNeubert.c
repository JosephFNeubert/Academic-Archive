#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

struct Activity
{
    int time;
    char activityType[64];
    struct Activity *left;
    struct Activity *right;
    struct Activity *down;
};

void coinFlip()
{
    int count = 0;
    int randomInt;
    srand(time(NULL));
    bool flag = true;
    while (flag)
    {
        randomInt = rand() % 2;
        if (randomInt == 0)
        {
            printf("Heads\n");
            count++;
        }
        else
        {
            printf("Tails\n");
            flag = false;
        }
    }
    printf("Skip List node appears on levels up to: %d\n", count);
}

int main()
{
    coinFlip();
    return 0;
}