#ifndef COMMANDS_H
#define COMMANDS_H

#include "addressbook_list.h"

#define COMMAND_LOAD "load"
#define COMMAND_UNLOAD "unload"
#define COMMAND_DISPLAY "display"
#define COMMAND_FORWARD "forward"
#define COMMAND_BACKWARD "backward"
#define COMMAND_INSERT "insert"
#define COMMAND_FIND "find"
#define COMMAND_DELETE "delete"
#define COMMAND_REVERSE "reverse"
#define COMMAND_SAVE "save"
#define COMMAND_QUIT "quit"
#define COMMAND_SORT "sort"
#define COMMAND_SORT_NAME "name"
#define COMMAND_SORT_RANDOM "random"

#define MAX 1000
#define EMPTYLIST 0
#define SINGLESERIAL 6
#define DOUBLESERIAL 7
#define TRIPLESERIAL 8

#define COMMENT "#"
#define CLEARONECHAR 1
#define CLEARTWOCHAR 2
#define MAXSERIALSIZE 6
#define SMALLSERIALSIZE 10
#define MEDIUMSERIALSIZE 99
#define LARGESERIALSIZE 999

#define LOWESTID 0
#define SINGLEDIGITID 10
#define DOUBLEDIGITID 100
#define TRIPLEDIGITID 1000
#define FOURDIGITID 10000


#define POSHEAD "Pos"
#define SERIALHEAD "Serial"
#define IDHEAD "ID"
#define NAMEHEAD "Name"
#define TELEHEAD "Telephone"
#define CURRENT "CUR"
#define EMPTYPOS "   "
TelephoneBookList * commandLoad(char * fileName);
void commandUnload(TelephoneBookList * list);
void commandDisplay(TelephoneBookList * list);
void commandForward(TelephoneBookList * list, int moves);
void commandBackward(TelephoneBookList * list, int moves);
void commandInsert(TelephoneBookList * list, int id, char * name, char * telephone);
void commandFind(TelephoneBookList * list, char * name);
void commandDelete(TelephoneBookList * list);
void commandReverse(TelephoneBookList * list);
void commandSave(TelephoneBookList * list, char * fileName);
void commandSortName(TelephoneBookList * list);
void commandSortRandom(TelephoneBookList * list);

int largestName(TelephoneBookList * list);
int changingNameSize(char * name, int largestName);
int changingSerialSize(int largeSerial, int i);
int largestID(int x);
int changingIDSize(int largeID, int id);
int finalEntries(int listSize);
char * checkCurrent(TelephoneBookList * list, char current);
#endif
