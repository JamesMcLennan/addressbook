#include "commands.h"
#define MAX 1000

TelephoneBookList * commandLoad(char * fileName)
{
    char text[MAX]; /*Character array used to store the file*/
    char *token; /*Pointer for tokenizer*/
    char name[MAX];
    char telephone[MAX];
    int lines = 0;
    int number; /*Used to store the ID of the address.*/
    TelephoneBookList * telephonebooklist;
    FILE *fp = fopen(fileName, "r"); /*Open the file requested from the user.*/
    
    if(fp == NULL)
    {
        printf("> Error: Unable to find the specified file.\n");
        return NULL;
    }

    else
    {
        printf("> Loading the file...\n");
        telephonebooklist = createTelephoneBookList();
        while(fgets(text, MAX, fp)) /*While there is text to read in the file called from fopen()*/ 
        {
            text[strlen(text) - 1] = '\0';

            if(strncmp(text, "#", 1) != 0) /*Ignores lines that being with a # - Comment lines*/
            {
                lines++;
                
                token = strtok(text, ", ");
                while(token != NULL)
                {
                    number = strtol(token, &token, 0);
                    token = strtok(NULL, ", ");
                    
                    strcpy(name, token); 
                    token = strtok(NULL, ", ");
                    
                    strcpy(telephone, token);
                    
                    commandInsert(telephonebooklist, number, name, telephone);
                    token = strtok(NULL, ", ");
                }
            }
        }
        printf("> %d phone book entries have been loaded from the file.\n", telephonebooklist->size);
        fclose(fp);
        printf("> Closing the file.\n");
        return telephonebooklist;
    }
}


void commandUnload(TelephoneBookList * list)
{

}

void commandDisplay(TelephoneBookList * list)
{
    TelephoneBookNode * node = list->head;

    int i;
    int largeName, nameSpace; /* Largest name in the list, space for each name in the list*/
    int largeSerial, serialSpace; /* Largest serial in the list, space for serial in the list*/
    int largeID, idSpace;

    if(list->size == EMPTYLIST) /* User attempts to display an empty list*/
    {
        largeName = EMPTYLIST;
        largeSerial = EMPTYLIST;
        largeID = EMPTYLIST;
    }
    else
    {
        largeSerial = largestSerial(list->size); /*Obtain the largest serial in the list*/
        largeName = largestName(list); /*Obtain the largest name in the list*/
        serialSpace = largeSerial; /* Assign the largest serial in the list to the width of the serial*/
        largeID = largestID(node->id);
    }
    FORMAT;
    printf("%s %s %s", SUBBREAK, "Pos", SUBBREAK); /* | Pos |*/
    printf(" %*s %s", largeSerial, "Serial", SUBBREAK); /* Serial(largest serial length) |*/
    printf(" %s %*s", "ID", largeID, SUBBREAK); /* */
    printf(" %s %s", "Name", SUBBREAK);
    printf(" %s %s\n", "Telephone", SUBBREAK);
    FORMAT;

    if(list->size == EMPTYLIST) /* If empty list - print blank list*/
    {
        printf("%s %44s\n", SUBBREAK, SUBBREAK);       
    }
    else
    {
        for(i = 0; i < list->size; i++) 
        {
            serialSpace = changingSerialSize(largeSerial, i); /* Modify serialSpace for each list*/
            idSpace = changingIDSize(largeID);
            if(i < list->size) /* While 'i' is less than the list size*/
            {
                /*Print each line with a SUBBREAK in between each classification of an address*/
                printf("%s %5s %d %*s %d %*s%s%s%s%s\n", SUBBREAK, SUBBREAK, i, serialSpace, SUBBREAK, node->id, idSpace, SUBBREAK, node->name, SUBBREAK, node->telephone, SUBBREAK);
                node = node->nextNode; /*Change node to the nextNode in the list*/
            }
        }    
    }
    FORMAT;
    printf("| Total phone book entries: %d %16s\n", list->size, SUBBREAK); /*Print the final summary of x itmes in the addressbook. NEED TO ADD SIZE function*/
    FORMAT;
    }

void commandForward(TelephoneBookList * list, int moves)
{

}

void commandBackward(TelephoneBookList * list, int moves)
{

}

void commandInsert(TelephoneBookList * list, int id, char * name, char * telephone)
{
    TelephoneBookNode * telephonebooknode; 
    telephonebooknode = createTelephoneBookNode(); /*Create a node*/

    if(id > 0)
    {
        telephonebooknode->id = id; /*As long as the ID is greater than 0, assign telephonebook node to the id*/
    }
    if(strlen(name) <= NAME_LENGTH) /* If the length of the name passed is less than or equal the max length*/
    {
        strcpy(telephonebooknode->name, name); /* Copy the name passed to the telephonebooknode member name*/
    }
    if(strlen(telephone) == TELEPHONE_LENGTH - 1) /* If the length of the telephone number is equal to the max length -1 for the null character*/
    {
        strcpy(telephonebooknode->telephone, telephone); /* Copy the name passed to the telephonebooknode member telephone*/
    }
    
    insert(list, telephonebooknode); /* Call insert */
}


void commandFind(TelephoneBookList * list, char * name)
{

}

void commandDelete(TelephoneBookList * list)
{

}

void commandReverse(TelephoneBookList * list)
{

}

void commandSave(TelephoneBookList * list, char * fileName)
{

}

void commandSortName(TelephoneBookList * list)
{

}

void commandSortRandom(TelephoneBookList * list)
{

}

int largestName(TelephoneBookList * list)
{
    TelephoneBookNode * node = list->head;

    int x, largeX;

    while(node != NULL)
    {
        x = strlen(node->name);
        if(largeX < x)
        {
            largeX = x;
        }

        node = node->nextNode;
    }
    return largeX;
}

int largestSerial(int x)
{
    int largeSerial;
    int serialLength = 5; /*Minimum serial size*/
    int singleSerial = 1; /*Add a single space for a single digit*/
    int doubleSerial = 2; /*Add two spaces for a double digit*/
    int tripleSerial = 3; /*Add three spaces for a triple digit*/
    
    if(x > 0 && x < 9) /*The below if/else statments seachers for the largest serial (1, 2 or 3 digits)*/
    {
        largeSerial = serialLength + singleSerial;
    }
    else if(x > 9 && x < 99)
    {
        largeSerial = serialLength + doubleSerial;
    }
    else if(x > 99 && x < 999)
    {
        largeSerial = serialLength + tripleSerial;
    }

    return largeSerial; /*Returns the largest serial digit length*/
}

int changingSerialSize(int largeSerial, int i)
{
    int serialSpace; 

    if(i < 10) /*Checks each value - If the value is a single, double or triple digit, minus 0, 1 or 2 respectively from the size*/
    {
        serialSpace = largeSerial;
    }
    else if(i > 9 && i <= 99)
    {
        serialSpace = largeSerial - 1;
    }
    else if(i > 99 && i < 999)
    {
        serialSpace = largeSerial - 2;
    }
    return serialSpace;
}

int largestID(int x)
{
    int largeID;
    int threeDigitID = 3;
    int fourDigitID = 4;

    if(x >= 100 && x < 1000)
    {
        largeID = threeDigitID;
    }
    else if( x >= 1000 && x < 10000)
    {
        largeID = fourDigitID;
    }

    return largeID;
}

int changingIDSize(int largeID)
{
    int idSpace;
    
    if(largeID < 1000)
    {
        idSpace = largeID - 1;
    }
    else if(largeID >= 1000)
    {
        idSpace = largeID - 5;
    }
    
    return idSpace;
}
