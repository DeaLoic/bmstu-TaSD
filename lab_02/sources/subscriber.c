#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "errorCodes.h"
#include "universal.h"
#include "subscriber.h"
#include "time.h"
#include "stdlib.h"

int dropRecordToFile(subscriber_t* subscriber, FILE* dest)
{
    fprintf(dest, "%s;%s;%s;%s;%d;", subscriber->surname, subscriber->name, subscriber->phone,
                                    subscriber->address, subscriber->status);
    if (subscriber->status == private)
    {
        fprintf(dest, "%s;", subscriber->info.privateInfo.birthday);
    }
    else
    {
        fprintf(dest, "%s;%s;", subscriber->info.workInfo.company, subscriber->info.workInfo.position);
    }

    return SUCCES;
}

int inputSubscriberConsole(subscriber_t* subscriber)
{
    printf("Input surname (max %d symbls): ", MAX_SURNAME_LEN - 1);
    int errorCode = inputString(stdin, subscriber->surname, MAX_SURNAME_LEN);

    if (!errorCode)
    {
        printf("Input name (max %d symbls): ", MAX_NAME_LEN - 1);
        errorCode = inputString(stdin, subscriber->name, MAX_NAME_LEN);
    }
    if (!errorCode)
    {
        printf("Input phone (max %d symbls): ", MAX_PHONE_LEN - 1);
        errorCode = inputString(stdin, subscriber->phone,  MAX_PHONE_LEN);
    }
    if (!errorCode)
    {
        printf("Input address (max %d symbls)", MAX_ADDRESS_LEN - 1);
        errorCode = inputString(stdin, subscriber->address, MAX_ADDRESS_LEN);
    }
    if (!errorCode)
    {
        printf("Input status (0 - personal, 1 - work)");
        int tempStatus;
        if (scanf("%d", &tempStatus) && tempStatus >= 0 && tempStatus <= 1)
        {
            subscriber->status = tempStatus;
            errorCode = SUCCES;
        }
        else
        {
            errorCode = INPUT_ERROR;
        }
        
        if (getchar() != '\n')
        {
            errorCode = INPUT_ERROR;
        }
    }
    if (!errorCode && subscriber->status)
    {
        printf("Input company (max %d symbls): ", MAX_COMPANY_LEN - 1);
        errorCode = inputString(stdin, subscriber->info.workInfo.company, MAX_COMPANY_LEN);
        if (!errorCode)
        {
            printf("Input position in company (max %d symbls): ", MAX_POSITION_LEN - 1);
            errorCode = inputString(stdin, subscriber->info.workInfo.position, MAX_POSITION_LEN);
        }
    }
    if (!errorCode && !subscriber->status)
    {
        printf("Input birthday (format YYYYMMDD): ");
        errorCode = inputString(stdin, subscriber->info.privateInfo.birthday, MAX_BIRTHDAY_LEN);
        if ((errorCode) || !isBirthdayCorrect(subscriber->info.privateInfo.birthday))
        {
            errorCode = INPUT_ERROR;
        }
    }

    return errorCode;
}

int inputSubscriberFile(subscriber_t* subscriber, FILE* source)
{
    int errorCode = SUCCES;
    int cnt = 0;
    int cntSymb = 0;
    char temp;
    while (fscanf(source, "%c", &temp) == 1 && temp != '\n')
    {
        if (temp == ';')
        {
            cntSymb = 0;
            cnt++;
        }
        else
        {
            switch (cnt)
            {
                case 0:
                    subscriber->surname[cntSymb] = temp;
                    subscriber->surname[cntSymb + 1] = '\0';
                    break;
                case 1:
                    subscriber->name[cntSymb] = temp;
                    subscriber->name[cntSymb + 1] = '\0';
                    break;
                case 2:
                    subscriber->phone[cntSymb] = temp;
                    subscriber->phone[cntSymb + 1] = '\0';
                    break;
                case 3:
                    subscriber->address[cntSymb] = temp;
                    subscriber->address[cntSymb + 1] = '\0';
                    break;
                case 4:
                    subscriber->status = (temp - '0');
                    break;
                case 5:
                    if (subscriber->status)
                    {
                        subscriber->info.workInfo.company[cntSymb] = temp;
                        subscriber->info.workInfo.company[cntSymb + 1] = '\0';
                    }
                    else
                    {
                        subscriber->info.privateInfo.birthday[cntSymb] = temp;
                        subscriber->info.privateInfo.birthday[cntSymb + 1] = '\0';
                    }
                    break;
                case 6:
                    if (subscriber->status)
                    {
                        subscriber->info.workInfo.position[cntSymb] = temp;
                        subscriber->info.workInfo.position[cntSymb + 1] = '\0';
                    }
                    break;
                default:
                    break;
            }
            cntSymb++;
        }
    }
    return errorCode;
}

int printSubscriber(subscriber_t* subscriber)
{
    if (subscriber->status == work)
    {
        printf("%10s %10s %10s %10s   work  Company: %10s  Position: %10s\n", subscriber->surname, subscriber->name, subscriber->phone,
                                    subscriber->address, subscriber->info.workInfo.company,
                                    subscriber->info.workInfo.position);
    }
    else
    {
        printf("%10s %10s %10s %10s private Birthday(YYYYMMDD): %10s\n", subscriber->surname, subscriber->name, subscriber->phone,
                                    subscriber->address, subscriber->info.privateInfo.birthday);
    }

    return SUCCES;
}

int printKey(subscriberKey_t* key)
{
    printf("%10d %10s\n", key->position, key->keySurname);
    return SUCCES;
}

int setSubscriberEmpty(subscriber_t* subscriber)
{
    subscriber->surname[0] = '\0';
    subscriber->name[0] = '\0';
    subscriber->phone[0] = '\0';
    subscriber->address[0] = '\0';
    subscriber->status = 0;
    subscriber->info.workInfo.company[0] = '\0';
    subscriber->info.workInfo.position[0] = '\0';

    return SUCCES;
}

int copySubscriber(subscriber_t* subscriberSource, subscriber_t* subscriberDestination)
{
    createSubscriber(subscriberDestination, subscriberSource->surname, subscriberSource->name, subscriberSource->phone,
                     subscriberSource->address, subscriberSource->status, subscriberSource->info);
    return SUCCES;
}

int createRandomSubscriber(subscriber_t* subscriber)
{
    createRandomString(subscriber->surname, rand() % (MAX_SURNAME_LEN - 2) + 1);
    createRandomString(subscriber->name, rand() % (MAX_NAME_LEN - 2) + 1);
    createRandomString(subscriber->phone, rand() % (MAX_PHONE_LEN - 2) + 1);
    createRandomString(subscriber->address, rand() % (MAX_ADDRESS_LEN - 2) + 1);
    if (rand() % 2)
    {
        subscriber->status = 0;
        char numbs[] = "0123456789";
        for (int i = 0; i < MAX_BIRTHDAY_LEN; i++)
        {
            subscriber->info.privateInfo.birthday[i] = numbs[rand() % 10];
        }
    }
    else
    {
        subscriber->status = 1;
        createRandomString(subscriber->info.workInfo.position, rand() % (MAX_POSITION_LEN - 2) + 1);
        createRandomString(subscriber->info.workInfo.company, rand() % (MAX_COMPANY_LEN - 2) + 1);
    }

    return SUCCES;
}

int createSubscriber(subscriber_t* subscriberDestination, char* surname, char* name, char* phone, char* address,
                     subscriberStatus status, extraInfo info)
{
    strcpy(subscriberDestination->surname, surname);
    strcpy(subscriberDestination->name, name);
    strcpy(subscriberDestination->phone, phone);
    strcpy(subscriberDestination->address, address);
    subscriberDestination->status = status;
    if (status)
    {
        strcpy(subscriberDestination->info.workInfo.company, info.workInfo.company);
        strcpy(subscriberDestination->info.workInfo.position, info.workInfo.position);
    }
    else
    {
        strcpy(subscriberDestination->info.privateInfo.birthday, info.privateInfo.birthday);
    }

    return SUCCES;
}

int compareSubscribersBySurname(const void* subscriberFirst, const void* subscriberSecond)
{
    subscriber_t* subA = (subscriber_t*)subscriberFirst;
    subscriber_t* subB = (subscriber_t*)subscriberSecond;

    return (strcmp(subA->surname, subB->surname));  // First > second
}

int createKey(subscriberKey_t* key, char* surname, int pos)
{
    key->position = pos;
    strcpy(key->keySurname, surname);
    return SUCCES;
}

int copyKey(subscriberKey_t* keySource, subscriberKey_t* keyDestination)
{
    (keyDestination->position) = keySource->position;
    createKey(keyDestination, keySource->keySurname, keySource->position);
    return SUCCES;
}

int setKeyEmpty(subscriberKey_t* key)
{
    key->position = 0;
    key->keySurname[0] = '\0';

    return SUCCES;
}

int compareKeyBySurname(const void* keyFirst, const void* keySecond)
{
    subscriberKey_t* keyA = (subscriberKey_t *)keyFirst;
    subscriberKey_t* keyB = (subscriberKey_t *)keySecond;

    return (strcmp(keyA->keySurname, keyB->keySurname));  // First > second => return > 0
}

int compareKeyByPosition(const void* keyFirst, const void* keySecond)
{
    subscriberKey_t* keyA = (subscriberKey_t *)keyFirst;
    subscriberKey_t* keyB = (subscriberKey_t *)keySecond;
    return (keyA->position - keyB->position);
}

int isBirthdayCorrect(char* str)
{
    int exitCode = 1;
    if (strlen(str) == MAX_BIRTHDAY_LEN - 1)
    {
        int i = 0;
        while (i < MAX_BIRTHDAY_LEN - 1 && exitCode)
        {
            exitCode = isdigit(str[i]);
            i++;
        }
    }
    else
    {
        exitCode = 0;
    }

    return exitCode;
}

int isSurnameMatch(subscriber_t* subscriber, char* surname)
{
    return !strcmp(subscriber->surname, surname);
}

int isSourcePosition(subscriberKey_t* key, int pos)
{
    return (key->position == pos);
}


int strToInt(char* str)
{
    int len = strlen(str);
    int res = 0;
    for (int i = len - 1, pow = 1; i >= 0; i -= 1, pow*=10)
    {
        res += (str[i] - '0') * pow;
    }

    return res;
}

int dateToDay(int date)
{
    return (date % 100 + date / 100 * 31) % (31 * 12);
}
int isBirthdayNextWeek(subscriber_t* subscriber, char* birthday)
{
    int exitCode = 0;
    int curDays = dateToDay(strToInt(birthday));
    int nextWeek = (curDays + 7) % (31 * 12);
    if (nextWeek == 0)
    {
        nextWeek++;
    }
    int tempDate = 0;
    if (subscriber->status == private)
    {
        tempDate = dateToDay(strToInt(subscriber->info.privateInfo.birthday + 4));
        if (nextWeek > curDays)
        {
            exitCode = (nextWeek >= tempDate && tempDate >= curDays);
        }
        else if (tempDate <= nextWeek || tempDate >= curDays)
        {
            exitCode = 1;
        }
        
    }
    return (exitCode);
}