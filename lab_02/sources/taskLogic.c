#include "taskLogic.h"
#include "errorCodes.h"
#include "universal.h"
#include "subscriber.h"
#include "phoneBook.h"
#include <time.h>
#include <stdlib.h>

int compareBookAtRecords(int size, int cntSorting, int (*sortBook)(phoneBook_t*, int (*)(const void* , const void*)),
                         int (*sortKeys)(phoneBookKeyTable_t*, int (*)(const void*, const void*)),
                         int (*secondSortBook)(phoneBook_t*, int (*)(const void* , const void*)),
                         int (*secondSortKeys)(phoneBookKeyTable_t*, int (*)(const void*, const void*)));

int compareSorting()
{
    printf("First sort - bubble\nSecond sort - qsort\n\n");
    compareBookAtRecords(100, 100, sortPhoneBookBubble, sortKeyTableBubble, sortPhoneBookQsort, sortKeyTableQsort);
    printf("\n");
    compareBookAtRecords(500, 100, sortPhoneBookBubble, sortKeyTableBubble, sortPhoneBookQsort, sortKeyTableQsort);
    printf("\n");
    compareBookAtRecords(1000, 100, sortPhoneBookBubble, sortKeyTableBubble, sortPhoneBookQsort, sortKeyTableQsort);


    /*
    start = clock();
    sortPhoneBookQsort(&tempPhoneBook, compareSubscribersBySurname);
    stop = clock();
    printf("Main table qsort:       %15ld\n", (stop - start) / CLK_TCK);

    start = clock();
    sortKeyTableBubble(&tempKeyTable, compareKeyBySurname);
    stop = clock();

    printf("Key table bubble sort: %15ld\n", (stop - start) / CLK_TCK);

    copyKeyTable(keyTable, &tempKeyTable);
    start = clock();
    sortKeyTableBubble(&tempKeyTable, compareKeyBySurname);
    stop = clock();
    printf("Key table bubble sort: %15ld\n", (stop - start) / CLK_TCK);
    */

    return SUCCES;
}

int compareBookAtRecords(int size, int cntSorting, int (*firstSortBook)(phoneBook_t*, int (*)(const void* , const void*)),
                         int (*firstSortKeys)(phoneBookKeyTable_t*, int (*)(const void*, const void*)),
                         int (*secondSortBook)(phoneBook_t*, int (*)(const void* , const void*)),
                         int (*secondSortKeys)(phoneBookKeyTable_t*, int (*)(const void*, const void*)))
{
    phoneBook_t phoneBook, tempPhoneBook;
    setPhoneBookEmpty(&phoneBook);
    setPhoneBookEmpty(&tempPhoneBook);
    
    srand(time(NULL));
    createRandomPhoneBook(&phoneBook, size);
    printf("Create book at %d records\n", size);

    phoneBookKeyTable_t keyTable, tempKeyTable;
    setKeyTableEmpty(&keyTable);
    setKeyTableEmpty(&tempKeyTable);
    createKeyTable(&phoneBook, &keyTable);
    copyKeyTable(&keyTable, &tempKeyTable);

    clock_t start, stop;
    start = clock();
    for (int i = 0; i < cntSorting; i++)
    {
        copyPhoneBook(&phoneBook, &tempPhoneBook);
        firstSortBook(&tempPhoneBook, compareSubscribersBySurname);
    }
    stop = clock();
    printf("Main table first sort %d time: %15lf\n", cntSorting, (double)(stop - start) / CLK_TCK);

    start = clock();
    for (int i = 0; i < cntSorting; i++)
    {
        copyKeyTable(&keyTable, &tempKeyTable);
        firstSortKeys(&tempKeyTable, compareKeyBySurname);
    }
    stop = clock();
    printf("Keys table first sort %d time: %15lf\n", cntSorting, (double)(stop - start) / CLK_TCK);

    start = clock();
    for (int i = 0; i < cntSorting; i++)
    {
        copyPhoneBook(&phoneBook, &tempPhoneBook);
        secondSortBook(&tempPhoneBook, compareSubscribersBySurname);
    }
    stop = clock();
    printf("Main table second sort %d time: %15lf\n", cntSorting, (double)(stop - start) / CLK_TCK);

    start = clock();
    for (int i = 0; i < cntSorting; i++)
    {
        copyKeyTable(&keyTable, &tempKeyTable);
        secondSortKeys(&tempKeyTable, compareKeyBySurname);
    }
    stop = clock();
    printf("Keys table second sort %d time: %15lf\n", cntSorting, (double)(stop - start) / CLK_TCK);

    deletePhoneBook(&phoneBook);
    deletePhoneBook(&tempPhoneBook);

    deleteKeyTable(&keyTable);
    deleteKeyTable(&tempKeyTable);

    return SUCCES;
}

int printInWeekBirthday(phoneBook_t* phoneBook)
{
    fseek(stdin, 0, SEEK_END);

    int errorCode = SUCCES;
    char tempBirthday[MAX_BIRTHDAY_LEN];

    errorCode = inputString(stdin, tempBirthday, MAX_BIRTHDAY_LEN);

    if ((errorCode) || !isBirthdayCorrect(tempBirthday))
    {
        printf("Incorrect input.\n");
        errorCode = SUCCES;
    }
    else
    {
        printByCondition(phoneBook, &isBirthdayNextWeek, tempBirthday + 4);
    }
    return SUCCES;
}