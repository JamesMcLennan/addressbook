#ifndef ADDRESSBOOK_H
#define ADDRESSBOOK_H

#include "commands.h"

extern int tally;
/* Prototypes */

void studentInformation();

TelephoneBookList * loadFile(char *);
void calculateMoves(int, int);
#endif
