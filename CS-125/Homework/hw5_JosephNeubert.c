/*
* File: hw5_JosephNeubert.c
* Author: Joseph Neubert
* Purpose: Program that outputs data regarding an array of doubles
* Date: 3/1/2024
*
* Sources of Help: N/A
*/

#include <stdio.h>
#include <stdlib.h>

/* use rand() to get a random double in given range */
double getRandomDouble(double lowerBound, double upperBound);

/* assign random doubles to array elements */
int fillArrayWithRandomValues(double* array, int numberToFill, double lowerLimit, double upperLimit);

/* print the array values one above the other */
void listArrayValues(double* array, int arrayLength);

/* return the minimum value found in the array */
double getMinimumArrayValue(double* array, int arrayLength);

/* return the maximum value found in the array */
double getMaximumArrayValue(double* array, int arrayLength);

/* return the sum of the values in the array */
double getSumOfArrayValues(double* array, int arrayLength);

/* return the mean of the array, using sumOfArrayValues() to get the sum */
double getMeanOfArrayValues(double* array, int arrayLength);

#define ARRAY_SIZE 100
#define DATA_LENGTH 75

int main(void) {
    double myArray[ARRAY_SIZE];
    int length = fillArrayWithRandomValues(myArray, DATA_LENGTH, 40.0, 60.0);
    listArrayValues(myArray, length);
    printf("The sum of the %d values was %.3f\n", length,
    getSumOfArrayValues(myArray, length));
    printf("The smallest was %.3f, and the largest was %.3f\n",
    getMinimumArrayValue(myArray, length), getMaximumArrayValue(myArray, length));
    printf("The average of the values was %.3f\n", getMeanOfArrayValues(myArray, length));
    return 0;
}

double getRandomDouble(double lowerBound, double upperBound) {
    double rangeOfReals = upperBound - lowerBound;
    double normalizedRand = rand() / (RAND_MAX + 1.0);
    return normalizedRand * rangeOfReals + lowerBound;
}

int fillArrayWithRandomValues(double* array, int numberToFill, double lowerLimit, double upperLimit) {
    int i = 0;
    for (i = 0; i < numberToFill; i++) {
        array[i] = getRandomDouble(lowerLimit, upperLimit);
    }
    return i;
}

void listArrayValues(double* array, int arrayLength) {
    int i = 0;
    for (i = 0; i < arrayLength; i++) {
        printf("number[%d] is %.3lf\n", i, array[i]);
    }
}

double getMinimumArrayValue(double* array, int arrayLength) {
    double minValue = array[0];
    int i = 0;
    for (i = 1; i < arrayLength; i++) {
        if (array[i] < minValue) {
            minValue = array[i];
        }
    }
    return minValue;
}

double getMaximumArrayValue(double* array, int arrayLength) {
    double maxValue = array[0];
    int i = 0;
    for (i = 1; i < arrayLength; i++) {
        if (array[i] > maxValue) {
            maxValue = array[i];
        }
    }
    return maxValue;
}

double getSumOfArrayValues(double* array, int arrayLength) {
    double sum = 0;
    int i = 0;
    for (i = 0; i < arrayLength; i++) {
        sum += array[i];
    }
    return sum;
}

double getMeanOfArrayValues(double* array, int arrayLength) {
    double sum = getSumOfArrayValues(array, arrayLength);
    return sum / arrayLength;
}
