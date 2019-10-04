#include "taskLogic.h"
#include "errorCodes.h"
#include "universal.h"
#include "subscriber.h"
#include "phoneBook.h"
#include <time.h>
#include <stdlib.h>

int compareSorting()
{
    phoneBook_t phoneBook, tempPhoneBook;
    setPhoneBookEmpty(&phoneBook);
    setPhoneBookEmpty(&tempPhoneBook);
    
    srand(time(NULL));
    int recordsCnt = 100;
    createRandomPhoneBook(&phoneBook, recordsCnt);
    printf("Create book at %d records\n", recordsCnt);

    phoneBookKeyTable_t keyTable, tempKeyTable;
    setKeyTableEmpty(&keyTable);
    setKeyTableEmpty(&tempKeyTable);
    createKeyTable(&phoneBook, &keyTable);
    copyKeyTable(&keyTable, &tempKeyTable);

    clock_t start, stop;
    int cntSorting = 1000;
    start = clock();
    for (int i = 0; i < cntSorting; i++)
    {
        copyPhoneBook(&phoneBook, &tempPhoneBook);
        sortPhoneBookBubble(&tempPhoneBook, compareSubscribersBySurname);
    }
    stop = clock();
    printf("Main table bubble sort %d time: %15lf\n", cntSorting, (double)(stop - start) / CLK_TCK);

    start = clock();
    for (int i = 0; i < cntSorting; i++)
    {
        copyKeyTable(&keyTable, &tempKeyTable);
        sortKeyTableBubble(&tempKeyTable, compareKeyBySurname);
    }
    stop = clock();
    printf("Keys table bubble sort %d time: %15lf\n", cntSorting, (double)(stop - start) / CLK_TCK);

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

int compareBookAtRecords(int size, int cntSorting)
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
        sortPhoneBookBubble(&tempPhoneBook, compareSubscribersBySurname);
    }
    stop = clock();
    printf("Main table bubble sort %d time: %15lf\n", cntSorting, (double)(stop - start) / CLK_TCK);

    start = clock();
    for (int i = 0; i < cntSorting; i++)
    {
        copyKeyTable(&keyTable, &tempKeyTable);
        sortKeyTableBubble(&tempKeyTable, compareKeyBySurname);
    }
    stop = clock();
    printf("Keys table bubble sort %d time: %15lf\n", cntSorting, (double)(stop - start) / CLK_TCK);

    deletePhoneBook(&phoneBook);
    deletePhoneBook(&tempPhoneBook);

    deleteKeyTable(&keyTable);
    deleteKeyBook(&tempKeyBook);
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