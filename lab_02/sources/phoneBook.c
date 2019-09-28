#include <stdio.h>
#include <stdlib.h>
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
    while (phoneBook->subscribers && !feof(source))
    {
        errorCode = inputSubscriberFile(phoneBook->subscribers + i, source);
        phoneBook->subscribersCount += 1;
        i++;
        if (i == startCount)
        {
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
    if (!errorCode)
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
    int step = 2;
    int startCount = 10;
    phoneBook->subscribersCount = 0;
    phoneBook->subscribers = (subscriber_t*)malloc(sizeof(subscriber_t) * startCount);
    int i = 0;
    subscriber_t* tempBook = NULL;
    while (phoneBook->subscribers && !feof(stdin) && !errorCode)
    {
        errorCode = inputSubscriberConsole(phoneBook->subscribers + i);
        phoneBook->subscribersCount += 1;
        i++;
        if (i == startCount)
        {
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
    if (!errorCode)
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
    printf("| Surname | Name | Phone | Address | Status | Variable Part |\n");
    for (int i = 0; i < phoneBook->subscribersCount; i++)
    {
        printSubscriber(phoneBook->subscribers + i);
    }

    return SUCCES;
}

int printPhoneBookByKeyTable(phoneBook_t* phoneBook, phoneBookKeyTable_t* keyTable)
{
    printf("| Surname | Name | Phone | Address | Status | Variable Part |\n");
    for (int i = 0; i < keyTable->keysCount; i++)
    {
        printSubscriber(phoneBook->subscribers + keyTable->keys[i].position);
    }

    return SUCCES;
}

int addRecord(phoneBook_t* phoneBook, subscriber_t* subscriber)
{
    int errorCode = SUCCES;
    subscriber_t* temp = (subscriber_t*)realloc(phoneBook->subscribers, phoneBook->subscribersCount + 1);
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
    if (position >= 0 && position <= phoneBook->subscribersCount && phoneBook->subscribersCount > 1)
    {
        for (int i = position; i + 1 < phoneBook->subscribersCount; i++)
        {
            swapSubscriber(phoneBook->subscribers + i, phoneBook->subscribers + i + 1);
        }

        subscriber_t* temp = (subscriber_t*)realloc(phoneBook->subscribers, phoneBook->subscribersCount - 1);
        if (temp)
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

int addKey(phoneBookKeyTable_t* keyTable, subscriberKey_t* key)
{
    int errorCode = SUCCES;
    subscriberKey_t* temp = (subscriberKey_t*)realloc(keyTable->keys, keyTable->keysCount + 1);
    if (temp)
    {
        keyTable->keys = temp;
        keyTable->keysCount += 1;
        copyKey(keyTable->keys + keyTable->keysCount - 1, key);
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
    if (position >= 0 && position <= keyTable->keysCount && keyTable->keysCount > 1)
    {
        for (int i = position; i + 1 < keyTable->keysCount; i++)
        {
            swapSubscriberKey(keyTable->keys + i, keyTable->keys + i + 1);
        }

        subscriberKey_t* temp = (subscriberKey_t*)realloc(keyTable->keys, keyTable->keysCount - 1);
        if (temp)
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

int sortKeyTable(phoneBookKeyTable_t* keyTable, int (*condition)(subscriberKey_t*, subscriberKey_t*))
{
    for (int i = 0; i + 1 < keyTable->keysCount; i++)
    {
        for (int j = 0;  j + 1 < keyTable->keysCount - j; j++)
        {
            if (condition(keyTable->keys + j, keyTable->keys + j + 1))
            {
                swapSubscriberKey(keyTable->keys + j, keyTable->keys + j + 1);
            }
        }
    }

    return SUCCES;
}

int sortPhoneBook(phoneBook_t* phoneBook, int (*condition)(subscriber_t* , subscriber_t*))
{
    for (int i = 0; i + 1 < phoneBook->subscribersCount; i++)
    {
        for (int j = 0;  j + 1 < phoneBook->subscribersCount - j; j++)
        {
            if (condition(phoneBook->subscribers + j, phoneBook->subscribers + j + 1))
            {
                swapSubscriber(phoneBook->subscribers + j, phoneBook->subscribers + j + 1);
            }
        }
    }

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