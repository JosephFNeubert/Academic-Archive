/*
* File: hw4_JosephNeubert.c
* Author: Joseph Neubert
* Purpose: Program to simulate a slot machine
* Date: 2/15/2024
*
* Sources of Help: N/A
*/


#include <stdio.h>
#include <stdlib.h>


int getRandomInteger(int minimum_value, int maximum_value)
{
    int random_range = maximum_value - minimum_value + 1;
    double  normalized_random = rand() / (RAND_MAX + 1.0);
    return (int) (normalized_random * random_range) + minimum_value;
}


void printWheelImage(int value)
{
    switch(value)
    {
        case 1:
            printf("  Cherry  ");
            break;
        
        case 2:
            printf("  Peach  ");
            break;
        
        case 3:
            printf("    7    ");
            break;
            
        case 4:
            printf("    $    ");
            break;

        default:
            printf("ERROR"); 
    }
}


void printLosingGame(int value1, int value2, int value3)
{
    printWheelImage(value1);
    printWheelImage(value2);
    printWheelImage(value3);
    printf("\n");
}


void printWinningGame(value)
{
    int i = 0;
    for (i = 0; i < 3; i++) 
    {
        printWheelImage(value);
    }
    printf("          YOU WIN!\n");
}


void playGame()
{
    int value1 = getRandomInteger(1, 4);
    int value2 = getRandomInteger(1, 4);
    int value3 = getRandomInteger(1, 4);
    
    if(value1 == value2 && value2 == value3)
    {
        printWinningGame(value1);
    }
    else
    {
        printLosingGame(value1, value2, value3);
    }
}


int main() 
{
    char valid = '\n';
    printf("Hit enter for each play, or 'q' to quit: ");
    scanf("%c", &valid);
    while(valid == '\n')
    {
        playGame();
        scanf("%c", &valid);
    }
    return 0;
}
