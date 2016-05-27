#include "addressbook.h"

int main(int argc, char ** argv)
{
    char usertext[FULLSIZE];
    char *token;
    char *input;
    int shiftPosition;
    TelephoneBookList * list;
    list = NULL;
    /* Show student information */
    studentInformation();
    
    do
    {
        printf("\nEnter your command: ");
        input = fgets(usertext, FULLSIZE, stdin);
        input[strlen(input)-1] = '\0';
        token = strtok(input, DELIMS);

        while(token != NULL)
        {
            if(strcmp(token, COMMAND_QUIT) == 0)
            {
                printf("> Goodbye.\n\n");
            }
            else if(strncmp(token, COMMAND_LOAD, 3) == 0)
            {
                list = loadFile(token);
                if(list == NULL)
                {
                    break;
                }
            }
            else if(strcmp(token, COMMAND_DISPLAY) == 0)
            {
                if(list == NULL)
                {
                    list = createTelephoneBookList();
                    commandDisplay(list);
                    list = NULL;
                }
                else
                {
                    commandDisplay(list);
                }
            }
            else if(strcmp(token, COMMAND_UNLOAD) == 0)
            {
                commandUnload(list);
                list = NULL;
                printf("> The list is unloaded.\n");
                break;
            }
            else if(strcmp(token, COMMAND_FORWARD) == 0)
            {
                token = strtok(NULL, DELIMS);
                if(token != NULL)
                {
                    shiftPosition = strtol(token, &token, 0);
                    commandForward(list, shiftPosition);
                }
                else
                {
                    ERRORM;
                }
            }
            else if(strcmp(token, COMMAND_BACKWARD) == 0)
            {
                token = strtok(NULL, DELIMS);
                if(token != NULL)
                {
                    shiftPosition = strtol(token, &token, 0);
                    commandBackward(list, shiftPosition);
                }
                else
                {
                    ERRORM;
                }
            }
            else if(strcmp(token, COMMAND_INSERT) == 0)
            {
                tokenInsert(list, token);
            }
            else if(strcmp(token, COMMAND_FIND) == 0)
            {
                token = strtok(NULL, DELIMS);
                if(token != NULL)
                {
                    commandFind(list, token);
                }
                else
                {
                    ERRORM;
                }
            }
            else if(strcmp(token, COMMAND_DELETE) == 0)
            {
                if(list != NULL)
                {
                    commandDelete(list);    
                }
                else
                {
                    printf("> Error: Cannot delete node, as the list is empty.\n");
                }
            }
            else if(strcmp(token, COMMAND_REVERSE) == 0)
            {
                if(list != NULL)
                {
                    commandReverse(list);
                }
                else
                {
                    printf("> Error: Caanot reverse an empty list.\n");
                }
            }
            else if(strcmp(token, COMMAND_SAVE) == 0)
            {
                token = strtok(NULL, DELIMS);
                commandSave(list, token);
            }
            /*Input does not match / Buffer overflow*/
            else
            {
                printf("> Input not recognised.\n");
            }
            token = strtok(NULL, DELIMS);
        }
    }while(strcmp(input, COMMAND_QUIT) != 0);
    if(list != NULL)
    {
        commandUnload(list);
    }
    return EXIT_SUCCESS;
}

void studentInformation()
{
    FORMAT;
    printf("Student Name: James McLennan\n");
    printf("Student Number: s3543182\n");
    printf("Advanced Programming Techniques, Assignment Two, Semester 1, 2016\n");
    FORMAT;
}

TelephoneBookList * loadFile(char * token)
{
    TelephoneBookList * list;
    token = strtok(NULL, DELIMS);

    if(token == NULL)
    {
        printf("> Error: Please specify a file\n");
        return NULL;
    }
    else
    {
        printf("> Opening the file %s.\n", token);
        list = commandLoad(token);
        return list;
    }
}

void calculateMoves(int shiftPosition, int listSize)
{
    if(shiftPosition >= EMPTYLIST && shiftPosition <= listSize)
    {
        printf("I am able to move %d nodes\n", shiftPosition);
    }
    else
    {
        printf("> Unable to move %d nodes\n", shiftPosition);
    }
}

void tokenInsert(TelephoneBookList * list, char * token)
{
    char name[MAX];
    char telephone[MAX];
    int id;

        token = strtok(NULL, DELIMS);
        if(token != NULL)
        {
            id = strtol(token, &token, 0);
            token = strtok(NULL, DELIMS);
            if(token != NULL)
            {
                strcpy(name, token);
                token= strtok(NULL, DELIMS);
                if(token != NULL)
                {
                    strcpy(telephone, token);
                    if(list != NULL)
                    {
                        commandInsert(list, id, name, telephone);
                    }
                    else
                    {
                        list = createTelephoneBookList();
                        commandInsert(list, id, name, telephone);
                    }
                }
                else
                    ERRORM;
            }
            else
                ERRORM;
        }
        else
            ERRORM;
}

