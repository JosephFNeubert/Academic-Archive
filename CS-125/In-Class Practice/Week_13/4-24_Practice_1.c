#include <stdio.h>

typedef struct {
    int year;
    int month;
    int day;
} Date;

typedef struct {
    Date firstDay;
    Date lastDay;
    Date readingDay;
} ExamPeriod;

Date setDate(int year, int month, int day) {
    Date d;
    d.year = year;
    d.month = month;
    d.day = day;
    return d;
}

void printReadingDay(ExamPeriod* epp) {
    printf("%d/%d/%d\n", epp->readingDay.month, epp->readingDay.day, epp->readingDay.year);
}

int main() {
    ExamPeriod spring2024;
    spring2024.firstDay = setDate(2024, 04, 28);
    spring2024.lastDay = setDate(2024, 05, 03);
    spring2024.readingDay = setDate(2024, 04, 26);
    
    printReadingDay(&spring2024);
    return 0;
}
