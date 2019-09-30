#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "errorCodes.h"
#include "subscriber.h"
#include "phoneBook.h"

int swapSubscriberKey(subscriberKey_t* first, subscriberKey_t* second);
int swapSubscriber(subscriber_t* first, subscriber_t* second);

int inputPhoneBookFile(phoneBook_t* phoneBook, FILE* source)
{
    int errorCode = SUCCES;
    int step = 2;
    int startCount = 10;
    phoneBook->subscribersCount = 0;
    phoneBook->subscribers = (subscriber_t*)malloc(sizeof(subscriber_t) * startCount);
    int i = 0;
    subscriber_t* tempBook = NULL;
    while (phoneBook->subscribers && !errorCode && !feof(source) && phoneBook->subscribersCount < MAX_RECORDS)
    {
        errorCode = inputSubscriberFile(phoneBook->subscribers + i, source);
        if (!errorCode)
        {
            phoneBook->subscribersCount += 1;
        }

        i++;
        if (i == startCount)
        {
            if (startCount == MAX_RECORDS / 2)
            {
                step = 1;
                startCount = MAX_RECORDS;
            }
            startCount *= step;
            tempBook = (subscriber_t*)realloc(phoneBook->subscribers, sizeof(subscriber_t) * startCount);
            if (tempBook)
            {
                phoneBook->subscribers = tempBook;
            }
            else
            {
                free(phoneBook->subscribers);
                setPhoneBookEmpty(phoneBook);
                errorCode = MEMORY_ERROR;
            }
        }
    }
    if (!errorCode && phoneBook->subscribersCount)
    {
        tempBook = (subscriber_t*)realloc(phoneBook->subscribers, sizeof(subscriber_t) * phoneBook->subscribersCount);
        if (tempBook)
        {
            phoneBook->subscribers = tempBook;
        }
        else
        {
            free(phoneBook->subscribers);
            setPhoneBookEmpty(phoneBook);
            errorCode = MEMORY_ERROR;
        }
    }

    return errorCode;
}

int inputPhoneBookConsole(phoneBook_t* phoneBook)
{
    int errorCode = SUCCES;
    int startCount = 0;
    printf("How many records will be add? (Input 0 for decline, or integer positive < %d)\n", MAX_RECORDS);
    fseek(stdin, 0, SEEK_END);
    if (scanf("%d", &startCount) && startCount >= 0 && startCount <= MAX_RECORDS)
    {
        phoneBook->subscribers = (subscriber_t*)malloc(sizeof(subscriber_t) * startCount);
        phoneBook->subscribersCount = 0;
        
        if (!phoneBook->subscribers)
        {
            free(phoneBook->subscribers);
            setPhoneBookEmpty(phoneBook);
            errorCode = MEMORY_ERROR;
        }
    }
    if (getchar() != '\n')
    {
        errorCode = INPUT_ERROR;
    }

    int i = 0;
    while (phoneBook->subscribers && i < startCount && !errorCode)
    {
        errorCode = inputSubscriberConsole(phoneBook->subscribers + i);
        if (!errorCode)
        {
            phoneBook->subscribersCount += 1;
        }
        i++;
    }
    if (errorCode && (errorCode != MEMORY_ERROR))
    {
        printf("Error in input. ");
        errorCode = SUCCES;
    }

    printf("Correct records: %d\n", phoneBook->subscribersCount);

    return errorCode;
}

int setPhoneBookEmpty(phoneBook_t* phoneBook)
{
    phoneBook->subscribers = NULL;
    phoneBook->subscribersCount = 0;

    return SUCCES;
}

int setPhoneBookByKeyTable(phoneBook_t* phoneBook, phoneBookKeyTable_t* keyTable)
{
    return SUCCES;
}

int printPhoneBook(phoneBook_t* phoneBook)
{
    printf("| Surname |   Name   |   Phone  |  Address | Status | Variable Part |\n");
    for (int i = 0; i < phoneBook->subscribersCount; i++)
    {
        printSubscriber(phoneBook->subscribers + i);
    }

    return SUCCES;
}

int printPhoneBookByKeyTable(phoneBook_t* phoneBook, phoneBookKeyTable_t* keyTable)
{
    printf("| Surname |   Name   |   Phone  |  Address  | Status | Variable Part |\n");
    for (int i = 0; i < keyTable->keysCount; i++)
    {
        printSubscriber(phoneBook->subscribers + keyTable->keys[i].position);
    }

    return SUCCES;
}

int printKeyTable(phoneBookKeyTable_t* keyTable)
{
    int errorCode = SUCCES;
    printf("| Position | Keys |\n");
    for (int i = 0; i < keyTable->keysCount; i++)
    {
        printKey(keyTable->keys + i);
    }

    return errorCode;
}

int addRecord(phoneBook_t* phoneBook, subscriber_t* subscriber)
{
    int errorCode = SUCCES;
    subscriber_t* temp = (subscriber_t*)realloc(phoneBook->subscribers, sizeof(subscriber_t) * (phoneBook->subscribersCount + 1));
    if (temp)
    {
        phoneBook->subscribers = temp;
        phoneBook->subscribersCount += 1;
        copySubscriber(subscriber, phoneBook->subscribers + phoneBook->subscribersCount - 1);
    }
    else
    {
        errorCode = MEMORY_ERROR;
    }
    
    return errorCode;
}

int deleteRecord(phoneBook_t* phoneBook, int position)
{
    int errorCode = SUCCES;
    if (position >= 0 && position <= phoneBook->subscribersCount)
    {
        for (int i = position; i + 1 < phoneBook->subscribersCount; i++)
        {
            swapSubscriber(phoneBook->subscribers + i, phoneBook->subscribers + i + 1);
        }

        subscriber_t* temp = (subscriber_t*)realloc(phoneBook->subscribers, sizeof(subscriber_t) * (phoneBook->subscribersCount - 1));
        if (temp || (phoneBook->subscribersCount - 1) == 0)
        {
            phoneBook->subscribers = temp;
            phoneBook->subscribersCount -= 1;
        }
        else
        {
            errorCode = MEMORY_ERROR;
        }
    }
    else
    {
        errorCode = INCORRECT_INPUT;
    }

    return errorCode;
}

int deletePhoneBook(phoneBook_t* phoneBook)
{
    free(phoneBook->subscribers);
    setPhoneBookEmpty(phoneBook);

    return SUCCES;
}

int createKeyTable(phoneBook_t* phoneBook, phoneBookKeyTable_t* keyTable)
{
    int errorCode = SUCCES;
    keyTable->keys = (subscriberKey_t*)malloc(sizeof(subscriberKey_t) * phoneBook->subscribersCount);
    keyTable->keysCount = phoneBook->subscribersCount;
    if (keyTable->keys)
    {
        for (int i = 0; i < keyTable->keysCount; i++)
        {
            createKey(keyTable->keys + i, phoneBook->subscribers[i].surname, i);
        }
    }
    else
    {
        errorCode = MEMORY_ERROR;
    }

    return errorCode;
}

int setKeyTableEmpty(phoneBookKeyTable_t* keyTable)
{
    keyTable->keys = NULL;
    keyTable->keysCount = 0;
    return SUCCES;
}


int addKey(phoneBookKeyTable_t* keyTable, subscriberKey_t* key)
{
    int errorCode = SUCCES;
    subscriberKey_t* temp = (subscriberKey_t*)realloc(keyTable->keys, sizeof(subscriberKey_t) * (keyTable->keysCount + 1));

    printf("temp: %d, source: %d\n", temp, keyTable->keys);
    if (temp)
    {
        keyTable->keys = temp;
        keyTable->keysCount += 1;
        copyKey(key, keyTable->keys + keyTable->keysCount - 1);
    }
    else
    {
        errorCode = MEMORY_ERROR;
    }
    
    return errorCode;
}

//TODO swap key 
int deleteKey(phoneBookKeyTable_t* keyTable, int position)
{
    int errorCode = SUCCES;
    if (position >= 0 && position <= keyTable->keysCount)
    {
        for (int i = position; i + 1 < keyTable->keysCount; i++)
        {
            swapSubscriberKey(keyTable->keys + i, keyTable->keys + i + 1);
        }

        subscriberKey_t* temp = (subscriberKey_t*)realloc(keyTable->keys, sizeof(subscriberKey_t) * (keyTable->keysCount - 1));
        if (temp || (keyTable->keysCount - 1) == 0)
        {
            keyTable->keys = temp;
            keyTable->keysCount -= 1;
        }
        else
        {
            errorCode = MEMORY_ERROR;
        }
    }
    else
    {
        errorCode = INCORRECT_INPUT;
    }

    return errorCode;
}

int deleteKeyTable(phoneBookKeyTable_t* keyTable)
{
    free(keyTable->keys);
    setKeyTableEmpty(keyTable);

    return SUCCES;
}

int sortKeyTableBubble(phoneBookKeyTable_t* keyTable, int (*condition)(const void*, const void*))
{
    for (int i = 0; i + 1 < keyTable->keysCount; i++)
    {
        for (int j = 0;  j + 1 < keyTable->keysCount - j; j++)
        {
            if (condition(keyTable->keys + j, keyTable->keys + j + 1) > 0)
            {
                swapSubscriberKey(keyTable->keys + j, keyTable->keys + j + 1);
            }
        }
    }

    return SUCCES;
}

int sortPhoneBookBubble(phoneBook_t* phoneBook, int (*condition)(const void* , const void*))
{
    for (int i = 0; i + 1 < phoneBook->subscribersCount; i++)
    {
        for (int j = 0;  j + 1 < phoneBook->subscribersCount - j; j++)
        {
            if (condition(phoneBook->subscribers + j, phoneBook->subscribers + j + 1) > 0)
            {
                swapSubscriber(phoneBook->subscribers + j, phoneBook->subscribers + j + 1);
            }
        }
    }

    return SUCCES;
}

int sortKeyTableQsort(phoneBookKeyTable_t* keyTable, int (*condition)(const void*, const void*))
{
    qsort(keyTable->keys, keyTable->keysCount, sizeof(subscriberKey_t), condition);

    return SUCCES;
}

int sortPhoneBookQsort(phoneBook_t* phoneBook, int (*condition)(const void* , const void*))
{
    qsort(phoneBook->subscribers, phoneBook->subscribersCount, sizeof(subscriber_t), condition);

    return SUCCES;
}

int copyKeyTable(phoneBookKeyTable_t* keyTableSource, phoneBookKeyTable_t* keyTableDest)
{
    keyTableDest->keysCount = keyTableSource->keysCount;

    for (int i = 0; i < keyTableDest->keysCount; i++)
    {
        copyKey(keyTableSource->keys + i, keyTableDest->keys + i);
    }

    return SUCCES;
}

int copyPhoneBook(phoneBook_t* phoneBookSource, phoneBook_t* phoneBookDest)
{
    phoneBookDest->subscribersCount = phoneBookSource->subscribersCount;

    for (int i = 0; i < phoneBookDest->subscribersCount; i++)
    {
        copySubscriber(phoneBookSource->subscribers + i, phoneBookDest->subscribers + i);
    }

    return SUCCES;
}

int swapSubscriberKey(subscriberKey_t* first, subscriberKey_t* second)
{
    subscriberKey_t temp;
    setKeyEmpty(&temp);
    copyKey(first, &temp);
    copyKey(second, first);
    copyKey(&temp, second);
    
    return SUCCES;
}

int swapSubscriber(subscriber_t* first, subscriber_t* second)
{
    subscriber_t temp;
    setSubscriberEmpty(&temp);
    copySubscriber(first, &temp);
    copySubscriber(second, first);
    copySubscriber(&temp, second);

    return SUCCES;
}

int findFirstByCondition(phoneBook_t* phoneBook, int (*condition)(subscriber_t*, char*), char* str)
{
    int i = 0;
    while (i < phoneBook->subscribersCount && !condition(phoneBook->subscribers + i, str))
    {
        i++;
    }
    if (i == phoneBook->subscribersCount)
    {
        i = -1;
    }

    return i;
}

int findKeyByCondition(phoneBookKeyTable_t* keyTable, int (condition)(subscriberKey_t*, int), int integer)
{
    int i = 0;
    while (i < keyTable->keysCount && !condition(keyTable->keys + i, integer))
    {
        i++;
    }
    if (i == keyTable->keysCount)
    {
        i = -1;
    }

    return i;
}