#include <stdio.h>
#include "errorCodes.h"
#include "subscriber.h"
#include "phoneBook.h"

int inputPhoneBook(phoneBook_t* phoneBook, FILE* source);
int setPhoneBookEmpty(phoneBook_t* phoneBook);
int setPhoneBookByKeyTable(phoneBook_t* phoneBook, phoneBookKeyTable_t* keyTable);
int printPhoneBook(phoneBook_t* phoneBook);
int printPhoneBookByKeyTable(phoneBook_t* phoneBook, phoneBookKeyTable_t* keyTable);
int addRecord(phoneBook_t* phoneBook, subscriber_t* subscriber);
int deleteRecord(phoneBook_t* phoneBook, int position);
int deletePhoneBook(phoneBook_t* phoneBook);

int createKeyTable(phoneBook_t* phoneBook, phoneBookKeyTable_t* keyTable);
int setKeyTableEmpty(phoneBookKeyTable_t* keyTable);
int printKeyTable(phoneBookKeyTable_t* keyTable);
int addKey(phoneBookKeyTable_t* keyTable, subscriberKey_t* key);
int deleteKey(phoneBookKeyTable_t* keyTable, int positionInPhoneBook);
int deleteKeyTable(phoneBookKeyTable_t* keyTable);

int sortKeyTable(phoneBookKeyTable_t* keyTable, int (*condition)(subscriberKey_t*, subscriberKey_t*));
int sortPhoneBook(phoneBook_t* phoneBook, int (*condition)(subscriber_t* , subscriber_t*)));
int copyKeyTable(phoneBookKeyTable_t* keyTableSource, phoneBookKeyTable_t* keyTableDest);
int copyPhoneBook(phoneBook_t* phoneBookSource, phoneBook_t* phoneBookDest);
