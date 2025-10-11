#include <stdio.h>
#include <stdlib.h>


int generateRandomDigit(int smallestInteger, int largestInteger) {
    int rangeOfIntegers = 1 + largestInteger - smallestInteger;
    double normalizedRand = rand() / (RAND_MAX + 1.0);
    return (int) (normalizedRand * rangeOfIntegers) + smallestInteger;
}


void practiceMultiplication(int numbQuestions) {
    int x = 0;
    for (x = 1; x <= numbQuestions; ++x) {
        int num1 = generateRandomDigit(1, 9);
        int num2 = generateRandomDigit(1, 9);
        int product = num1 * num2;
        int userAns = 0;
        printf("Question %d: What is %d times %d? ", x, num1, num2);
        scanf("%d", &userAns);
        while (userAns != product) {
            printf("Not this time. Please try again.");
            scanf("%d", &userAns);
        }
        printf("Very good!\n");
    } 
}


int main() {
    int questions = 0;
    printf("Let's practice multiplication!\n");
    printf("How many questions do you want? ");
    scanf("%d", &questions);
    
    practiceMultiplication(questions);
    printf("Practice session complete. Great job!\n");
    return 0;
}
