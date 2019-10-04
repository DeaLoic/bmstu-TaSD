#ifndef __PHONE_BOOK_H__
#define __PHONE_BOOK_H__

#include <limits.h>
#include <stdio.h>
#include "subscriber.h"

#define MAX_RECORDS (2000)

typedef struct
{
    subscriber_t* subscribers;
    int subscribersCount;

} phoneBook_t;

typedef struct
{
    subscriberKey_t* keys;
    int keysCount;

} phoneBookKeyTable_t;


int dropPhoneBookToFile(phoneBook_t* phoneBook, phoneBookKeyTable_t* keyTable, FILE* dest);
int inputPhoneBookFile(phoneBook_t* phoneBook, FILE* source);

int inputPhoneBookConsole(phoneBook_t* phoneBook);
int setPhoneBookEmpty(phoneBook_t* phoneBook);
int setPhoneBookByKeyTable(phoneBook_t* phoneBook, phoneBookKeyTable_t* keyTable);

int createRandomPhoneBook(phoneBook_t* phoneBook, int recordCnt);

int printPhoneBook(phoneBook_t* phoneBook);
int printPhoneBookByKeyTable(phoneBook_t* phoneBook, phoneBookKeyTable_t* keyTable);

int deletePhoneBook(phoneBook_t* phoneBook);

int addRecord(phoneBook_t* phoneBook, subscriber_t* subscriber);
int deleteRecord(phoneBook_t* phoneBook, int position);

int findFirstByCondition(phoneBook_t* phoneBook, int (*condition)(subscriber_t*, char*), char* str);
int findKeyByCondition(phoneBookKeyTable_t* keyTable, int (condition)(subscriberKey_t*, int), int integer);
int printByCondition(phoneBook_t* phoneBook, int (*condition)(subscriber_t*, char*), char* str);

int createKeyTable(phoneBook_t* phoneBook, phoneBookKeyTable_t* keyTable);
int setKeyTableEmpty(phoneBookKeyTable_t* keyTable);
int printKeyTable(phoneBookKeyTable_t* keyTable);
int addKey(phoneBookKeyTable_t* keyTable, subscriberKey_t* key);
int deleteKey(phoneBookKeyTable_t* keyTable, int position);
int deleteKeyTable(phoneBookKeyTable_t* keyTable);

int sortKeyTableBubble(phoneBookKeyTable_t* keyTable, int (*condition)(const void*, const void*));
int sortPhoneBookBubble(phoneBook_t* phoneBook, int (*condition)(const void* , const void*));
int sortKeyTableQsort(phoneBookKeyTable_t* keyTable, int (*condition)(const void*, const void*));
int sortPhoneBookQsort(phoneBook_t* phoneBook, int (*condition)(const void* , const void*));
int copyKeyTable(phoneBookKeyTable_t* keyTableSource, phoneBookKeyTable_t* keyTableDest);
int copyPhoneBook(phoneBook_t* phoneBookSource, phoneBook_t* phoneBookDest);

#endif