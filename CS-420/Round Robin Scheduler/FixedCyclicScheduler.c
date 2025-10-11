/*
 * File: FixedCyclicScheduler.c
 * Author: Joseph Neubert
 * Purpose: Demonstration of a fixed cyclic (round robin) scheduler, time quantum of 4, for threads of user-inputted time lengths
 * Date: 10/6/2025
 */

// Imports
#include <stdio.h>
#include <stdlib.h>
#include "string.h"

// Global thread counter
int threadCounter;

// Create structure for a thread which includes the thread's ID, time to process, current state, and pointer to the next thread
struct Thread
{
    int threadID;
    int timeToProcess;
    int state; // 0 is "waiting" and 1 for "ready"
    struct Thread *next;
};

/* FUNCTION PROTOTYPES */
// Creation function for each thread
struct Thread *createThread(int time);

// Add threads to the end of the linked list
void addThread(struct Thread **head, int time);

// Algorithm for round robin scheduling
void fixedCyclicSchedule(struct Thread *head, int quantum, int threadCount);

/* MAIN */
int main()
{
    int timeQuantum = 4;
    /* TEST CODE - NO LONGER FUNCTIONS
    struct Thread *T1 = (struct Thread *)malloc(sizeof(struct Thread));
    T1->threadName = "T1";
    T1->timeToProcess = 3;
    T1->state = 1;
    T1->next = NULL;
    struct Thread *T2 = (struct Thread *)malloc(sizeof(struct Thread));
    T2->threadName = "T2";
    T2->timeToProcess = 5;
    T2->state = 1;
    T2->next = NULL;
    struct Thread *T3 = (struct Thread *)malloc(sizeof(struct Thread));
    T3->threadName = "T3";
    T3->timeToProcess = 7;
    T3->state = 1;
    T3->next = NULL;
    T1->next = T2;
    T2->next = T3;
    T3->next = T1;

    fixedCyclicSchedule(T1, timeQuantum, 3);
    */

    // Placeholder variables for user input to populate a thread
    int threadLength;
    char buffer[8];
    char input = '\0';

    // Initializes the thread list
    struct Thread *threadList = NULL;

    // Process to take user input and populate the thread list
    printf("Would you like to create a new thread? Type 'y' to confirm. Type any other single character to move to scheduling: ");
    if (!fgets(buffer, sizeof(buffer), stdin))
        return 2;
    buffer[strcspn(buffer, "\n")] = '\0';
    input = buffer[0];
    while (input == 'y' || input == 'Y')
    {
        printf("How many time units will the new thread be: ");
        if (!fgets(buffer, sizeof(buffer), stdin))
            break;
        buffer[strcspn(buffer, "\n")] = '\0';
        threadLength = (int)strtol(buffer, NULL, 10);
        addThread(&threadList, threadLength);
        printf("Would you like to create a new thread? Type 'y' to confirm. Type any other character to move to scheduling: ");
        if (!fgets(buffer, sizeof(buffer), stdin))
            break;
        buffer[strcspn(buffer, "\n")] = '\0';
        input = buffer[0];
    }

    // Run the round robin algorithm on the user-made thread list
    printf("Begin custom thread creation and round robin scheduling!\n");
    fixedCyclicSchedule(threadList, timeQuantum, threadCounter);
    return 0;
}

/* FUNCTION DEFINITIONS*/
struct Thread *createThread(int time)
{
    threadCounter++;
    struct Thread *t = (struct Thread *)malloc(sizeof(struct Thread));
    t->threadID = threadCounter;
    t->timeToProcess = time;
    t->state = 1;
    t->next = NULL;
    return t;
}

void addThread(struct Thread **head, int time)
{
    struct Thread *newThread = createThread(time);
    struct Thread *temp;

    // If linked list is currently empty
    if (*head == NULL)
    {
        *head = newThread;
        newThread->next = *head;
    }
    // Traverse linked list until the last element (circles back to head) to insert to linked list
    else
    {
        temp = *head;
        while (temp->next != *head)
        {
            temp = temp->next;
        }
        temp->next = newThread;
        newThread->next = *head;
    }
}

void fixedCyclicSchedule(struct Thread *head, int quantum, int threadCount)
{
    // Loop terminates once the number of threads completed is equal to total number of threads present
    int terminationCounter = 0;
    while (terminationCounter < threadCount)
    {
        // Checks to ensure thread is "ready" and not "waiting"
        if (head->state == 1)
        {
            // Run thread for time period equal to the time quantum
            head->timeToProcess = head->timeToProcess - quantum;
            if (head->timeToProcess <= 0)
            {
                head->timeToProcess = 0;
                head->state = 0;
                terminationCounter++;
                printf("T%d has been completed.\n", head->threadID);
            }
            else
            {
                printf("T%d remains ready with remaining time of %d.\n", head->threadID, head->timeToProcess);
            }
        }
        // Proceed to next thread
        head = head->next;
    }
    printf("All threads have cycled once successfully!\n");
}
