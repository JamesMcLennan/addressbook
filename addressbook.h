/* Author: James McLennan / s3543182 2016 RMIT*/
#ifndef ADDRESSBOOK_H
#define ADDRESSBOOK_H

#include "commands.h"

#define ARGC1 1
#define ARGC2 2
#define ERRORM printf("> Invalid input\n")
/* Prototypes */

/*Display student information */
void studentInformation();

/*Function will check the next token in the string after load, if it is not NULL, it will pass the string through to command load
 * else it will print an error message (only load was input)*/
TelephoneBookList * loadFile(char *);

/*Function will tokenize the string after Insert has been found*/
void tokenInsert(TelephoneBookList * list, char *);

#endif
