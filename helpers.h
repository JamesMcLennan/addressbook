#ifndef HELPERS_H
#define HELPERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <assert.h>

typedef enum boolean
{
    FALSE = 0,
    TRUE
} Boolean;

#define NEW_LINE_SPACE 1
#define NULL_SPACE 1
#define ARRAYSIZE 80

/**
 * This is used to compensate for the extra character spaces taken up by
 * the '\n' and '\0' when input is read through fgets().
 **/
#define EXTRA_SPACES (NEW_LINE_SPACE + NULL_SPACE)
#define FULLSIZE (NEW_LINE_SPACE + NULL_SPACE + ARRAYSIZE)

#define EMPTY_STRING ""

#define DELIMS ", "
#define FORMAT printf("---------------------------------------------\n"); /*46 Characters long*/
#define SUBBREAK "|"
/**
 * Call this function whenever you detect buffer overflow.
 **/
void readRestOfLine();

#endif
