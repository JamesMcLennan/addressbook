/* Author: James McLennan / s3543182 2016 RMIT*/
#include "commands.h"

TelephoneBookList * commandLoad(char * fileName)
{
    char text[MAX]; /*Character array used to store the file*/
    char *token; /*Pointer for tokenizer*/
    int number; /*Used to store the ID of the address.*/
    TelephoneBookList * telephonebooklist;
    TelephoneBookNode * node;
    FILE *fp = fopen(fileName, "r"); /*Open the file requested from the user.*/
    
    if(fp == NULL) /*File does not exist */
    {
        printf("> Error: Unable to find the specified file.\n");
        return NULL;
    }

    else
    {
        printf("> Loading the file...\n");
        telephonebooklist = createTelephoneBookList(); /*Create list*/
        
        while(fgets(text, MAX, fp)) /*While there is text to read in the file called from fopen()*/ 
        {
            text[strlen(text) - CLEARONECHAR] = '\0';

            if(strncmp(text, COMMENT, CLEARONECHAR) != 0) /*Ignores lines that being with a # - Comment lines*/
            {
                token = strtok(text, DELIMS);
                while(token != NULL)
                {
                    node = createTelephoneBookNode(); /*Create node*/
                    
                    number = strtol(token, &token, 0); /*First token after load = ID*/
                    node->id = number;
                    token = strtok(NULL, DELIMS);
                    
                    strcpy(node->name, token); /* Second token after load = Name*/
                    token = strtok(NULL, DELIMS);
                    
                    strcpy(node->telephone, token); /* Third token after load = Telephone number*/

                    insert(telephonebooklist, node); /* Insert the node*/
                    token = strtok(NULL, DELIMS);
                }
            }
        }
        
        printf("> %d phone book entries have been loaded from the file.\n", telephonebooklist->size);
        fclose(fp); /* Close the file*/
        printf("> Closing the file.\n");
        return telephonebooklist;
    }
}


void commandUnload(TelephoneBookList * list)
{
   if(list != NULL)
   {
       TelephoneBookNode * node = list->head;
       freeTelephoneBookNode(node);/*Free every node*/
       freeTelephoneBookList(list);/* Free the list*/
   }
}

void commandDisplay(TelephoneBookList * list)
{
    TelephoneBookNode * node = list->head;

    int i;
    int largeName, nameSpace; /* Largest name in the list, space for each name in the list*/
    int largeSerial, serialSpace; /* Largest serial in the list, space for serial in the list*/
    int largeID, idSpace;
    int totalEntries;
    char *checkCurrent;

    if(list->size == EMPTYLIST) /* User attempts to display an empty list*/
    {
        largeName = EMPTYNAMESIZE;
        largeSerial = EMPTYLIST;
        largeID = EMPTYLIST;
        totalEntries = EMPTYTOTALSIZE;
    }
    else
    {
        largeSerial = MAXSERIALSIZE; /*Obtain the largest serial in the list*/
        largeName = largestName(list); /*Obtain the largest name in the list*/
        serialSpace = largeSerial; /* Assign the largest serial in the list to the width of the serial*/
        largeID = largestID(node->id);
        totalEntries = finalEntries(list->size);
    }
    FORMAT;
    printf("%s %s %s", SUBBREAK, POSHEAD, SUBBREAK); /* | Pos |*/
    printf(" %*s %s", largeSerial, SERIALHEAD, SUBBREAK); /* Serial(largest serial length) |*/
    printf(" %s %*s", IDHEAD, largeID, SUBBREAK); /* */
    printf(" %s %*s", NAMEHEAD, changingNameSize(NAMEHEAD, largeName), SUBBREAK);
    printf(" %s  %s\n", TELEHEAD, SUBBREAK);
    FORMAT;

    if(list->size == EMPTYLIST) /* If empty list - print blank list*/
    {
        printf("%s %43s\n", SUBBREAK, SUBBREAK);       
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
                checkCurrent = CURRENT;
            }
            else
            {
                checkCurrent = EMPTYPOS;
            }
            if(i <= list->size) /* While 'i' is less than the list size*/
            {
                /*Print each line with a SUBBREAK in between each classification of an address*/
                printf("%s %s %s %d %*s %d %*s %s %*s %s %s\n", SUBBREAK, checkCurrent, SUBBREAK, i, serialSpace, 
                    SUBBREAK, node->id, idSpace, SUBBREAK, node->name, nameSpace, SUBBREAK, node->telephone, SUBBREAK);
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
    if(forward(list, moves) == FALSE) /*If forward fails*/
    {
        printf("> Unable to move %d nodes forward\n", moves);
    }
}

void commandBackward(TelephoneBookList * list, int moves)
{
    if(backward(list, moves) == FALSE) /*If backward fails*/
    {
        printf("> Unable to move %d nodes backward\n", moves);
    }
}

void commandInsert(TelephoneBookList * list, int id, char * name, char * telephone)
{
    TelephoneBookNode * telephonebooknode; 
    telephonebooknode = createTelephoneBookNode(); /*Create a node*/
    if(id > LOWESTID && id < FOURDIGITID)
    {
        if(findByID(list, id) == NULL)
        {
            if(strlen(name) <= NAME_LENGTH) /* If the length of the name passed is less than or equal the max length*/
            {
                if(strlen(telephone) == TELEPHONE_LENGTH - CLEARONECHAR) /* If the length of the telephone number is equal to the max length -1 for the null character*/
                {
                    telephonebooknode->id = id; /*As long as the ID is greater than 0, assign telephonebook node to the id*/
                    strcpy(telephonebooknode->name, name); /* Copy the name passed to the telephonebooknode member name*/
                    strcpy(telephonebooknode->telephone, telephone); /* Copy the name passed to the telephonebooknode member telephone*/
                    insert(list, telephonebooknode);
                }
                else
                {
                    printf("> Error: Incorrect format\n");
                }
            }
            else
            {
                printf("> Error: Incorrect format\n");
            }
        }
        else
        {
            printf("> Error: Node with ID %d already exists.\n", id);
        }
    }
}


void commandFind(TelephoneBookList * list, char * name)
{
   if(list != NULL)
   {
       if(strlen(name) <= NAME_LENGTH) /* If the name is less the the maximum name length*/
       {
           if(findByName(list, name) == NULL)
           {
               printf("> Error: Unable to find node.\n");
           }
       }
       else
       {
           printf("> Error: Invalid format.\n");
       }
   }
   else
   {
        printf("> Error: Unable to find node.\n");
   }
}

void commandDelete(TelephoneBookList * list)
{
    if(list->size == CLEARONECHAR) /*If the list is equal than 1*/
    {
        commandUnload(list); /* Unload the list*/
    }
    else
    {
        delete(list); /* Else delete */
    }
}

void commandReverse(TelephoneBookList * list)
{
    TelephoneBookNode * nextNode, * currentNode = list->head, * prevNode = NULL;
    
    if(list != NULL)
    {
        while(currentNode != NULL)
        {
            nextNode = currentNode->nextNode; /* Assign an empty node to the currentNode's next position*/
            
            currentNode->nextNode = prevNode; /* currentNode's next position is assigned to the prevNode (In the first instance this is NULL)*/
            currentNode->previousNode = nextNode; /* CurrentNode's previousNode is assigned to the nextNode (changing the direction essentially)*/

            prevNode = currentNode; /*Update prevNode to equal the currentNode (remember prevNode is the currentNode's nextNode)*/
            currentNode = nextNode; /* Update currentNode to equal the nextNode (remember nextNode is the currentNode's next position)*/
        }

        list->head = prevNode;
    }
    else
    {
        printf("> Error: Cannot reverse an empty list\n");
    }
}

void commandSave(TelephoneBookList * list, char * fileName)
{
    TelephoneBookNode * node = list->head;
    FILE *fp = fopen(fileName, "w+"); /*Open the file in a write mode*/
    
    char name[MAX];
    char telephone[MAX];
    while(node != NULL)
    {
        fprintf(fp, "%d, ", node->id); /*Write the id to the file*/
        
        strcpy(name, node->name);
        fprintf(fp, "%s, ", name); /*Write the name to the file*/

        strcpy(telephone, node->telephone);
        fprintf(fp, "%s\n", telephone); /*Write the telephone to the file*/
        
        node = node->nextNode; /*Go to the next node*/
    }
    fclose(fp); /*Close the file*/
}

void commandSortName(TelephoneBookList * list)
{

}

void commandSortRandom(TelephoneBookList * list)
{
    printf("Test\n");
}

int largestName(TelephoneBookList * list) /*Find the largest Node name*/
{
    TelephoneBookNode * node = list->head;

    int x, largeX;
    
    while(node != NULL)
    {
        x = strlen(node->name); /* Assign X to the size of the name*/
        if(largeX < x)
        {
            largeX = x; /*Assign largeX to the largest X*/
        }
        node = node->nextNode; /* Next node*/
     }
    return largeX;
}

int changingNameSize(char * name, int largeID) /*change the name size for each, depending on the largest name*/
{
    int nameSize = strlen(name); 

    while(nameSize <= largeID) /* if the nameSize is <= the largest name size*/
    {
        nameSize++;
    }
    return nameSize - strlen(name); /*Return the size, minus its length*/
}
int changingSerialSize(int largeSerial, int i)
{
    int serialSpace; 

    if(i < SMALLSERIALSIZE) /*Checks each value - If the value is a single, double or triple digit, minus 0, 1 or 2 respectively from the size*/
    {
        serialSpace = largeSerial; /*The size needed is the size of the large serial*/
    }
    else if(i >= SMALLSERIALSIZE && i <= MEDIUMSERIALSIZE) 
    {
        serialSpace = largeSerial - CLEARONECHAR; /*Return the space needed for the serial size, minus a char given it is 2 chars wide */
    }
    else if(i > MEDIUMSERIALSIZE && i < LARGESERIALSIZE)
    {
        serialSpace = largeSerial - CLEARTWOCHAR; /*Return the space needed for the serial size, minus two chars given it is 3 chars wide */
    }
    return serialSpace;
}

int largestID(int x)
{
    int largeID;
    int oneDigitID = 0;
    int twoDigitID = 1;
    int threeDigitID = 2;
    int fourDigitID = 3;
    
    if(x > LOWESTID && x < SINGLEDIGITID) /* If x is passed through, and x is greater than 0 and less than 10 it returns the spaces required to adjust the display*/
    {
        largeID = oneDigitID; /* Spaces required = 0*/
    }
    else if( x >= SINGLEDIGITID && x < DOUBLEDIGITID) /* If x is greater than 10 and less than 100, essentially if it has two digits.*/
    {
        largeID = twoDigitID; /* Spaces required = 1*/
    }
    else if(x >= DOUBLEDIGITID && x < TRIPLEDIGITID) /* If x is greater than 100 and less than 1000, essentially if it has three digits*/
    {
        largeID = threeDigitID; /* Spaces required = 2*/
    }
    else if( x >= TRIPLEDIGITID && x < FOURDIGITID) /* If x is greater than 1000 and less than 10000, essentially if it has four digits*/
    {
        largeID = fourDigitID; /* Spaces required = 3*/
    }

    return largeID; /*The last return will be the largest ID size */
}

int changingIDSize(int largeID, int id)
{
    int idSpace;
    if(id < SINGLEDIGITID) /* Check if the ID is less than 10*/
    {
        idSpace = largeID + CLEARONECHAR; /* The size allocated for this ID is the largest ID size, plus 1 as the single digit is significantly smaller.*/
    }
    else if(id < DOUBLEDIGITID) /* Check if the ID is less than 100*/
    {
        idSpace = largeID; 
    }
    else if(id < TRIPLEDIGITID) /* Check if the ID is less than 1000 (3 digits)*/
    {
        idSpace = largeID - CLEARONECHAR; /* The size allocated for this ID is the largest ID, minus a single char*/
    }
    else if(id  >= TRIPLEDIGITID) /* Check if the ID is less than 10000 (four digits)*/
    {
        idSpace = largeID - CLEARTWOCHAR; /* The size allocated for this ID is the largest ID, minus two char*/
    }
    
    return idSpace; /*Return each individual allocated size. */
}

int finalEntries(int listSize)
{
    int totalSpace = 16;

    if(listSize < SINGLEDIGITID) /* if the list size is less than 10*/
    {
        totalSpace = totalSpace - CLEARONECHAR; /*Total space needed is 15 chars*/
    }
    else if(listSize >= SINGLEDIGITID && listSize < DOUBLEDIGITID)
    {
        totalSpace = totalSpace - CLEARTWOCHAR; /*if the list is between 10 and 100 total space needed is 14 chars*/
    }
    else if(listSize >= DOUBLEDIGITID && listSize < TRIPLEDIGITID)
    {
        totalSpace = totalSpace - CLEARTHREECHAR; /*If the list is between 100 and 1000 total space needed is 13 chars*/
    }
    
    return totalSpace;
}
