/*
* File: hw3_JosephNeubert.c
* Author: Joseph Neubert
* Purpose: To incrementally create a program that determines if a valid input is between 1 and 20
* Date: 2/2/2024
*
* Sources of Help: N/A
*/

#include <stdio.h>

int step1() 
{
    int value = 0;
    printf("Please enter a value between 1 and 20: ");
    scanf("%d", &value);
    printf("You entered a %d\n", value);
    
    return 0;
}


int step2() 
{
    int value = 0;
    printf("Please enter a value between 1 and 20: ");
    scanf("%d", &value);
    
    /*Tests to see if the input is between 1 and 20*/
    if(value <= 20 && value >= 1)
    {
        printf("You entered a %d\n", value);
    }
    else
    {
        printf("The value you entered is not between 1 and 20.\n");
    }
    
    return 0;
}


int step3() 
{
    int value = 0;
    printf("Please enter a value between 1 and 20: ");
    scanf("%d", &value);
    
    /*Tests to see if the input is between 1 and 20*/
    if(value <= 20 && value >= 1)
    {
        /*If the input is within the correct range, test to see if the number starts with a vowel to adjust the article*/
        if(value == 8 || value == 11 || value == 18)
        {
            printf("You entered an %d\n", value);
        }
        else
        {
            printf("You entered a %d\n", value);
        }
    }
    else
    {
        printf("The value you entered is not between 1 and 20.\n");
    }
    
    return 0;
}


int step4() 
{
    int value = 0;
    printf("Please enter a value between 1 and 20: ");
    int valid = scanf("%d", &value);
    
    /*Tests to see if the input is an integer before testing if it is in range*/
    if(valid == 0)
    {
      printf("Your input could not be read as a number!\n");
    }
    else 
    {
        /*Tests to see if the input is between 1 and 20*/
        if(value <= 20 && value >= 1)
        {
            /*If the input is within the correct range, test to see if the number starts with a vowel to adjust the article*/
            if(value == 8 || value == 11 || value == 18)
            {
                printf("You entered an %d\n", value);
            }
            else
            {
                printf("You entered a %d\n", value);
            }
        }
        else
        {
            printf("The value you entered is not between 1 and 20.\n");
        }
    }
    
    return 0;
}


int main()
{
    step1();
    step2();
    step3();
    step4();
    return 0;
}
