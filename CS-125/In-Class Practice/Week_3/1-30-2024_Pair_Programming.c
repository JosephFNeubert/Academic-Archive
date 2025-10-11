/*
* File: 1-30-2024_Pair_Programming.c
* Authors: Joseph Neubert and Ryan Trigueiro
* Purpose: Program to find the middle value of a set of 3 integers and use that value to print that number of stars
* Date: 1/30/2024
*
* Sources of Help: N/A
*/

#include <stdio.h>

/* Function to find the middle value */
int middleValue(int value1, int value2, int value3) {
    /* TODO:  the function finds the middle value among three input integers and returns it */
    /*defining largest*/
    if (value3 > value2 && value3 > value1) {
        /*largest = value3*/
        if(value2 > value1) {
            return value2;
        } else {
            return value1;
        }
    } else if (value2 > value3 && value2 > value1) {
        /*largest value2*/
        if(value3 > value1){
            return value3;
        } else {
            return value1;
        }
    } else if(value2 > value3) {
            return value2;
    } else {
            return value3;
    }
}

/* Function to print stars */
void printStars(int numberOfStars) {
    /* TODO: Write a function to print 'stars' numberOfStars times on the same line
     Use either a 'for' or 'while' loop */
    int i = 0;
    for(i = 0; i < numberOfStars; i++) {
        printf("*");
    }
    printf("\n");
}

int main() {
    /* TODO:Declare and initialize your variables here!!! */
    int input_stars = 0;
    int input1 = 0;
    int input2 = 0;
    int input3 = 0;

    /* TODO:Prompt the user to input three integer values */
    printf("Enter 3 integers and press enter after each: ");
    scanf("%d", &input1);
    scanf("%d", &input2);
    scanf("%d", &input3);

    /* TODO:Call middleValue function and store the result in a variable */
    input_stars = middleValue(input1, input2, input3);

    /* TODO:Display the three integer values and the calculated middle value.*/
    /* Example output: */
    /* The middle value of 12, 3 and 8 is 8. */
    printf("The middle value of %d, %d, %d is %d.\n", input1, input2, input3, input_stars);

    /* TODO:Call printStars with the middle value as an argument and display the stars */
    printStars(input_stars);
    printf("\n");
    
    return 0;
}

