#include <stdio.h>
#include <stdlib.h>
#include "errorCodes.h"
#include "subscriber.h"
#include "phoneBook.h"
#include "taskLogic.h"
#include "universal.h"

#define RELEASE 1    // For information messages
#define DEBUG 0      // For debug messages

void printMenu();

int main(void)
{
    int errorCode = SUCCES;

    int choose = 1;

    char filename[] = "phoneBook.csv";

    phoneBook_t phoneBook;
    phoneBookKeyTable_t keyTable;
    subscriber_t tempSubscriber;
    subscriberKey_t tempKey;
    setPhoneBookEmpty(&phoneBook);
    setKeyTableEmpty(&keyTable);
    setSubscriberEmpty(&tempSubscriber);
    setKeyEmpty(&tempKey);
    int temp = 0;
    FILE* source = NULL;
    char tempSurname[MAX_SURNAME_LEN];

    while (!errorCode && choose != 0)
    {
        fseek(stdin, 0, SEEK_END);
        printMenu();
        if (!scanf("%d", &choose))
        {
            choose = -1;
        }
        system("cls");
        fseek(stdin, 0, SEEK_END);

        switch (choose)
        {
            case 0:
                break;
            case 1:
                deletePhoneBook(&phoneBook);
                deleteKeyTable(&keyTable);
                setPhoneBookEmpty(&phoneBook);
                setKeyTableEmpty(&keyTable);
                source = fopen(filename, "r");
                if (source)
                {
                    errorCode = inputPhoneBookFile(&phoneBook, source);
                    fclose(source);
                    if (!errorCode)
                    {
                        printf("Done reading file");
                        createKeyTable(&phoneBook, &keyTable);
                    }
                    else
                    {
                        setPhoneBookEmpty(&phoneBook);
                        printf("\nError while reading phone book. Pls, try again\n");
                    }
                }
                else
                {
                    printf("\nError while opening file\n");
                }
                errorCode = SUCCES;
                break;
            
            case 2:
                setPhoneBookEmpty(&phoneBook);
                setKeyTableEmpty(&keyTable);

                errorCode = inputPhoneBookConsole(&phoneBook);

                if (!errorCode)
                {
                    createKeyTable(&phoneBook, &keyTable);
                }
                else
                {
                    setPhoneBookEmpty(&phoneBook);
                    printf("\nError while reading phone book. Pls, try again\n");
                }

                break;

            case 3:
                if (phoneBook.subscribersCount)
                {
                    if (phoneBook.subscribersCount < MAX_RECORDS)
                    {    
                        setSubscriberEmpty(&tempSubscriber);
                        errorCode = inputSubscriberConsole(&tempSubscriber);
                        if (!errorCode)
                        {
                            errorCode = addRecord(&phoneBook, &tempSubscriber);
                            if (!errorCode)
                            {
                                createKey(&tempKey, phoneBook.subscribers[phoneBook.subscribersCount - 1].surname,
                                                    phoneBook.subscribersCount - 1);
                                errorCode = addKey(&keyTable, &tempKey);
                            }
                            if (errorCode)
                            {
                                printf("\nError in memory. Panic exit");
                            }
                        }
                        else
                        {
                            printf("\nIncorrect input. Record doesnt add\n");
                            errorCode = SUCCES;
                        }
                        setKeyEmpty(&tempKey);
                        setSubscriberEmpty(&tempSubscriber);
                    }
                    else
                    {
                        printf("Max records reached. Cant add even more\n");
                    }
                }
                else
                {
                    printf("\nPhone book is empty, pls choose 1 or 2 point to create\n");
                }
                break;

            case 4:
                if (phoneBook.subscribersCount)
                {
                    printPhoneBookByKeyTable(&phoneBook, &keyTable);
                    printf("\nInput surname to delete\n");

                    errorCode = inputString(stdin, tempSurname, MAX_SURNAME_LEN);

                    if (!errorCode)
                    {
                        temp = findFirstByCondition(&phoneBook, &isSurnameMatch, tempSurname);
                        if (temp >= 0)
                        {
                            while (temp >= 0)
                            {
                                errorCode = deleteRecord(&phoneBook, temp);
                                if (!errorCode)
                                {
                                    temp = findKeyByCondition(&keyTable, &isSourcePosition, temp);
                                    errorCode = deleteKey(&keyTable, temp);
                                    if (!errorCode)
                                    {
                                        for (int i = 0; i < keyTable.keysCount; i++)
                                        {
                                            if (keyTable.keys[i].position > temp)
                                            {
                                                keyTable.keys[i].position -= 1;
                                            }
                                        }
                                    }
                                }
                                temp = findFirstByCondition(&phoneBook, &isSurnameMatch, tempSurname);
                            }
                            
                        }
                        else
                        {
                            printf("Records doesnt found\n");
                        }
                        
                        if (errorCode == MEMORY_ERROR)
                        {
                            printf("Memory error, panic exit\n");
                        }
                        else
                        {
                            errorCode = SUCCES;
                        }
                        
                    }
                    else
                    {
                        printf("Incorrect position, try again\n");
                    }
                }
                else
                {
                    printf("\nPhone book is empty, pls choose 1 or 2 point to create\n");
                }
                break;
            
            case 5:
                if (phoneBook.subscribersCount)
                {
                    printPhoneBook(&phoneBook);
                }
                else
                {
                    printf("\nPhone book is empty, pls choose 1 or 2 point to create\n");
                }
                break;
            
            case 6:
                if (keyTable.keysCount)
                {
                    printKeyTable(&keyTable);
                }
                else
                {
                    printf("\nKey table is empty\n");
                }
                break;

            case 7:
                if (phoneBook.subscribersCount)
                {
                    printPhoneBookByKeyTable(&phoneBook, &keyTable);
                }
                else
                {
                    printf("\nPhone book is empty, pls choose 1 or 2 point to create\n");
                }
                break;

            case 8:
                if (phoneBook.subscribersCount)
                {
                    sortKeyTableBubble(&keyTable, &compareKeyBySurname);
                }
                else
                {
                    printf("\nPhone book is empty, pls choose 1 or 2 point to create\n");
                }
                break;

            case 9:
                if (phoneBook.subscribersCount)
                {
                    sortPhoneBookBubble(&phoneBook, &compareSubscribersBySurname);
                }
                else
                {
                    printf("\nPhone book is empty, pls choose 1 or 2 point to create\n");
                }
                break;

            case 10:
                if (phoneBook.subscribersCount)
                {
                    sortKeyTableQsort(&keyTable, &compareKeyBySurname);
                }
                else
                {
                    printf("\nPhone book is empty, pls choose 1 or 2 point to create\n");
                }
                break;

            case 11:
                if (phoneBook.subscribersCount)
                {
                    sortPhoneBookQsort(&phoneBook, &compareSubscribersBySurname);
                }
                else
                {
                    printf("\nPhone book is empty, pls choose 1 or 2 point to create\n");
                }
                break;

            case 12:
                    compareSorting();
                break;
            
            case 13:
                if (phoneBook.subscribersCount)
                {
                    printInWeekBirthday(&phoneBook);
                }
                else
                {
                    printf("\nPhone book is empty, pls choose 1 or 2 point to create\n");
                }
                break;
            
            case 14:
                if (phoneBook.subscribersCount)
                {
                    source = fopen(filename, "w");
                    if (source)
                    {
                        errorCode = dropPhoneBookToFile(&phoneBook, &keyTable, source);
                        fclose(source);

                        printf("Data was writed in file.\n");
                    }
                    else
                    {
                        printf("Error open file.\n");
                    }
                }
                else
                {
                   printf("\nPhone book is empty. You cant write empty table.\n");
                }
                break;

            default:
                printf("\nPls, choose point from menu\n");
                break;
        }
    }
    if (errorCode)
    {
        printf("\nFATAL ERROR");
    }
    else
    {
        printf("\nGoodbay");
    }
    
    getchar();
    return errorCode;
}

void printMenu()
{
    printf("\n------------------MENU------------------\n");
    printf("0.  Exit\n\n");

    printf("1.  Input data from file phoneBook.csv\n");
    printf("2.  Input data from console\n");

    printf("\n3.  Add data from console\n");
    printf("4.  Delete data by surname value\n");

    printf("\n5.  Print phone book\n");
    printf("6.  Print key table\n");
    printf("7.  Print phone book by key table\n");
    
    printf("\n8.  Sort key table bubble\n");
    printf("9.  Sort phone book bubble\n");
    printf("10. Sort key table qsort\n");
    printf("11. Sort phone book qsort\n");

    printf("\n12. Compare sorting\n");
    printf("13. Find friends with birthday in week\n");
    printf("14. Write phone book by key table to phoneBook.csv");
    printf("\nYour choose: ");
}