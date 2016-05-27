#ifndef ADDRESSBOOK_H
#define ADDRESSBOOK_H

#include "commands.h"

#define ERRORM printf("> Invalid input\n")
extern int tally;
/* Prototypes */

void studentInformation();

TelephoneBookList * loadFile(char *);
void calculateMoves(int, int);
void tokenInsert(TelephoneBookList * list, char *);
char checkToken(char *);
#endif
