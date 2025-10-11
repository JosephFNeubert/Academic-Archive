/* file name: Practice_4-2.c
   Authors: Jesse Lyszczarz and Joseph Neubert
   purpose: learning animal sounds
   sources of help: N/A
*/

#include <stdio.h>

#define MAXLEN 32
#define MAX_ANIMALS 10

typedef struct {
    char name[MAXLEN];
    char sound[MAXLEN];
    char food[MAXLEN];
} Animal;

void getAnimal(Animal* ani) {
    printf("Enter the name of the animal: ");
    scanf("%s", (*ani).name);
    printf("What does a %s eat? ", (*ani).name);
    scanf("%s", (*ani).food);
    printf("Enter the sound made by a %s: ", (*ani).name);
    scanf("%s", (*ani).sound);
    printf("\n");
}

void visitAnimal(Animal* ani) {
    printf("This is a %s. It eats %s and says %s!\n", (*ani).name, (*ani).food, (*ani).sound);
}

int main() {
    int number = 0;
    int i = 0;
    Animal num[MAX_ANIMALS];
    printf("How many kinds of animals in the farm?  ");
    scanf("%d", &number);
    printf("\n");

    for (i = 0; i < number; ++i) {
        getAnimal(&num[i]);
    }
    i = 0;
    printf("\nWelcome to our farm.\n");
    for (i = 0; i < number; ++i) {
        visitAnimal(&num[i]);
    }

    return 0;
}
