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
   if(list != NULL)
   {
       TelephoneBookNode * node = list->head;
       freeTelephoneBookNode(node);
       freeTelephoneBookList(list);
   }
   printf("> The list is unloaded.\n");
}

void commandDisplay(TelephoneBookList * list)
{
    TelephoneBookNode * node = list->head;

    int i;
    int largeName, nameSpace; /* Largest name in the list, space for each name in the list*/
    int largeSerial, serialSpace; /* Largest serial in the list, space for serial in the list*/
    int largeID, idSpace;
    int totalEntries;
    char name[] = "Name";
    char *checkCurrent;

    if(list->size == EMPTYLIST) /* User attempts to display an empty list*/
    {
        largeName = EMPTYLIST;
        largeSerial = EMPTYLIST;
        largeID = EMPTYLIST;
        totalEntries = EMPTYLIST;
    }
    else
    {
        largeSerial = 6; /*Obtain the largest serial in the list*/
        largeName = largestName(list); /*Obtain the largest name in the list*/
        serialSpace = largeSerial; /* Assign the largest serial in the list to the width of the serial*/
        largeID = largestID(node->id);
        totalEntries = finalEntries(list->size);
    }
    FORMAT;
    printf("%s %s %s", SUBBREAK, "Pos", SUBBREAK); /* | Pos |*/
    printf(" %*s %s", largeSerial, "Serial", SUBBREAK); /* Serial(largest serial length) |*/
    printf(" %s %*s", "ID", largeID, SUBBREAK); /* */
    printf(" %s %*s", name, changingNameSize(name, largeName), SUBBREAK);
    printf(" %s  %s\n", "Telephone", SUBBREAK);
    FORMAT;

    if(list->size == EMPTYLIST) /* If empty list - print blank list*/
    {
        printf("%s %44s\n", SUBBREAK, SUBBREAK);       
    }
    else
    {
        for(i = 1; i <= list->size; i++) 
        {
            serialSpace = changingSerialSize(largeSerial, i); /* Modify serialSpace for each list*/
            idSpace = changingIDSize(largeID, node->id);
            nameSpace = changingNameSize(node->name, largeName);
            if(node == list->current)
            {
                checkCurrent = "CUR";
            }
            else
            {
                checkCurrent = "   ";
            }
            if(i <= list->size) /* While 'i' is less than the list size*/
            {
                /*Print each line with a SUBBREAK in between each classification of an address*/
                printf("%s %s %s %d %*s %d %*s %s %*s %s %s\n", SUBBREAK, checkCurrent, SUBBREAK, i, serialSpace, SUBBREAK, node->id, idSpace, SUBBREAK, node->name, nameSpace, SUBBREAK, node->telephone, SUBBREAK);
                node = node->nextNode; /*Change node to the nextNode in the list*/
            }
        }    
    }
    FORMAT;
    printf("| Total phone book entries: %d %*s\n", list->size, totalEntries, SUBBREAK); /*Print the final summary of x itmes in the addressbook. NEED TO ADD SIZE function*/
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

int changingNameSize(char * name, int largeID)
{
    int nameSize = strlen(name);

    while(nameSize <= largeID)
    {
        nameSize++;
    }
    return nameSize - strlen(name);
}
int changingSerialSize(int largeSerial, int i)
{
    int serialSpace; 

    if(i < 10) /*Checks each value - If the value is a single, double or triple digit, minus 0, 1 or 2 respectively from the size*/
    {
        serialSpace = largeSerial;
    }
    else if(i >= 10 && i <= 99)
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
    int threeDigitID = 2;
    int fourDigitID = 3;

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

int changingIDSize(int largeID, int id)
{
    int idSpace;
    
    if(id < 1000)
    {
        idSpace = largeID - 1;
    }
    else if(id  >= 1000)
    {
        idSpace = largeID - 2;
    }
    
    return idSpace;
}

int finalEntries(int listSize)
{
    int totalSpace = 16;

    if(listSize < 10)
    {
        totalSpace = totalSpace - 1;
    }
    else if(listSize >= 10 && listSize < 100)
    {
        totalSpace = totalSpace - 2;
    }
    else if(listSize >= 100 && listSize < 1000)
    {
        totalSpace = totalSpace - 3;
    }
    
    return totalSpace;
}
