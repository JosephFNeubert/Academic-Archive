#include <stdio.h>

int getIntegerFromUser(char *what)
{
    int userInput = -1;
    if (what == "puppies")
    {
        printf("How many puppies do you want? ");
        scanf("%d", &userInput);
    }
    return userInput;
}

int main()
{
    char *what = "puppies";
    int num = getIntegerFromUser(what);
    printf("%d", num);
    return 0;
}
