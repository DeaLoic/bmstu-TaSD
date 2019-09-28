#ifndef __SUBSCRIBER_H__
#define __SUBSCRIBER_H__

#include <stdio.h>

#define MAX_SURNAME_LEN    64
#define MAX_NAME_LEN       64
#define MAX_PHONE_LEN      16
#define MAX_BIRTHDAY_LEN   9
#define MAX_ADDRESS_LEN    256
#define MAX_POSITION_LEN   128
#define MAX_COMPANY_LEN    128


typedef struct
{
    char birthday[MAX_BIRTHDAY_LEN] //format YYYYMMDD

} privateInfo_t;

typedef struct
{
    char position[MAX_POSITION_LEN];
    char company[MAX_COMPANY_LEN];

} workInfo_t;

typedef enum subscriberStatus
{ 
    private,
    work
} subscriberStatus;

typedef union extraInfo
{
    privateInfo_t privateInfo;
    workInfo_t workInfo;
} extraInfo;

typedef struct
{
    char surname[MAX_SURNAME_LEN];
    char name[MAX_NAME_LEN];
    char phone[MAX_PHONE_LEN];      //format D-DDD-DDD-DD-DD
    char address[MAX_ADDRESS_LEN];
    subscriberStatus status;
    extraInfo info;
    
} subscriber_t;

typedef struct
{
    int position;
    char keySurname[MAX_SURNAME_LEN];
} subscriberKey_t;

int inputSubscriberConsole(subscriber_t* subscriber);
int inputSubscriberFile(subscriber_t* subscriber, FILE* source);
int printSubscriber(subscriber_t* subscriber);
int setSubscriberEmpty(subscriber_t* subscriber);

int copySubscriber(subscriber_t* subscriberSource, subscriber_t* subscriberDestination);
int createSubscriber(subscriber_t* subscriberSource, char* surname, char* name, char* phone, char* address,
                     subscriberStatus status, extraInfo info);

int compareSubscribersBySurname(subscriber_t* subscriberFirst, subscriber_t* subscriberSecond);

int createKey(subscriberKey_t* key, subscriber_t* subscriber, int pos);
int setKeyEmpty(subscriberKey_t* key);
int printKey(subscriber_t* subscriber);

int compareKeyBySurname(subscriberKey_t* keyFirst, subscriberKey_t* keySecond);
int compareKeyByPosition(subscriberKey_t* keyFirst, subscriberKey_t* keySecond);
