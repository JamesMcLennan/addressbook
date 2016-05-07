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

    int i, largeX, nameSpace;
    
    largeX = largestName(list);

    FORMAT;
    printf("%s %3s %s ", SUBBREAK, "Pos", SUBBREAK);
    printf("%3s %s", "Serial", SUBBREAK);
    printf(" %s %2s", "ID", SUBBREAK);
    printf(" %s %*s", "Name", largeX - 3, SUBBREAK);
    printf("%10s %s\n", "Telephone", SUBBREAK);
    FORMAT;
    for(i = 0; i < list->size; i++)
    {
        if(list->size == 0)
        {
            printf("%s %46s", SUBBREAK, SUBBREAK);
        }
        if(i > 0)
        {
            nameSpace = largeX - strlen(node->name) + 1 ;
            printf("%s %5s %d %6s %d %s %s %*s %s %s\n", SUBBREAK, SUBBREAK, i, SUBBREAK, node->id, SUBBREAK, node->name, nameSpace, SUBBREAK, node->telephone, SUBBREAK);
            node = node->nextNode;
        }
    }    
    FORMAT;
    printf("| Total phone book entries: %d %15s\n", list->size, SUBBREAK);
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
    telephonebooknode = createTelephoneBookNode();

    if(id > 0)
    {
        telephonebooknode->id = id;
    }
    if(strlen(name) < NAME_LENGTH)
    {
        strcpy(telephonebooknode->name, name);
    }
    if(strlen(telephone) == TELEPHONE_LENGTH - 1)
    {
        strcpy(telephonebooknode->telephone, telephone);
    }
    
    insert(list, telephonebooknode);
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
