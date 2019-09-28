#include <stdio.h>
#include "errorCodes.h"
#include "universal.h"
#include "subscriber.h"

int inputSubscriberConsole(subscriber_t* subscriber)
{
    printf("Input surname (%d symbls): ", MAX_SURNAME_LEN - 1);
    int errorCode = inputString(stdin, subscriber->surname, MAX_SURNAME_LEN - 1);
    if (!errorCode)
    {
        printf("Input name (%d symbls): ", MAX_NAME_LEN - 1);
        errorCode = inputString(stdin, subscriber->name);
    if (!errorCode)
    {
        printf("Input phone (format D-DDD-DDD-DD-DD): ", MAX_PHONE_LEN - 1);
        errorCode = !(scanf("%1[0–9]s", subscriber->phone));

    }
}

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