/* Author: James McLennan / s3543182 2016 RMIT*/
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

    if(argc > ARGC1) /*If the argument count (argc) is greater than 1 (the './addressbook' is position 0 */
    {
        if(strcmp(argv[ARGC1], COMMAND_LOAD) == 0) /*If the second item in the argv array matches COMMAND_LOAD*/
        {
            printf("> Opening the file %s.\n", argv[ARGC2]);
            list = commandLoad(argv[ARGC2]); /*Load the filename passed into the commandLoad*/
        }
        else
        {
            printf("> Error: Attempted to load file from command line. Load not found.\n"); /* Load was not found, however there was an unknown command called.*/
        }
    }
    do
    {
        printf("\nEnter your command: ");
        input = fgets(usertext, FULLSIZE, stdin); /*Ask user for input*/
        if(input[strlen(input)-ARGC1] != '\n') /*Buffer overflow protection */
        {
            readRestOfLine();
            printf("> Error: Please enter a valid option\n");
        }
        else
        {
            input[strlen(input)-1] = '\0';
            token = strtok(input, DELIMS);

            while(token != NULL)
            {
                if(strcmp(token, COMMAND_QUIT) == 0) /*User input matches quit*/
                {
                    printf("> Goodbye.\n\n");
                }
                else if(strncmp(token, COMMAND_LOAD, 3) == 0) /* User input matches load*/
                {
                    list = loadFile(token); /* Pass the token to a self-made function: loadFile()*/
                    if(list == NULL) /* If the list returns empty, break*/
                    {
                        break;
                    }
                }
                else if(strcmp(token, COMMAND_DISPLAY) == 0) /* User input matches display*/
                {
                    if(list == NULL) /* If the list is empty*/
                    {
                        list = createTelephoneBookList(); /* Create an instances of the list*/
                        commandDisplay(list);/* Display the list*/
                        free(list); /* Free empty allocated list*/
                        list = NULL; /*List = NULL */
                    }
                    else
                    {
                        commandDisplay(list); /*If the list is not empty, display the list */
                    }
                }
                else if(strcmp(token, COMMAND_UNLOAD) == 0) /* User input matches unload*/
                {
                    commandUnload(list); /* Command unload list*/
                    list = NULL;
                    printf("> The list is unloaded.\n");
                    break;
                }
                else if(strcmp(token, COMMAND_FORWARD) == 0) /*User input matches forward */
                {
                    token = strtok(NULL, DELIMS);
                    if(token != NULL)
                    {
                        shiftPosition = strtol(token, &token, 0); /* strtol the token, to obtain number of moves*/
                        commandForward(list, shiftPosition); 
                    }
                    else
                    {
                        ERRORM; /*Display generic error message if token is NULL */
                    }
                }
                else if(strcmp(token, COMMAND_BACKWARD) == 0) /*User input is backward*/
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
                else if(strcmp(token, COMMAND_INSERT) == 0) /* User input matches insert*/
                {
                    if(list == NULL)
                    {
                        list = createTelephoneBookList();
                        tokenInsert(list, token); /* Call selfmade function tokenInsert()*/
                    }
                    else
                    {
                        tokenInsert(list, token);
                    }
                }
                else if(strcmp(token, COMMAND_FIND) == 0) /* User input matches find*/
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
                else if(strcmp(token, COMMAND_DELETE) == 0) /* user input matches delete*/
                {
                    if(list != NULL)
                    {
                        commandDelete(list);    
                    }
                    else /* The list is empty, cannot delete anything*/
                    {
                        printf("> Error: Cannot delete node, as the list is empty.\n");
                    }
                }
                else if(strcmp(token, COMMAND_REVERSE) == 0) /*User input matches reverse*/
                {
                    if(list != NULL)
                    {
                        commandReverse(list);
                    }
                    else /*List is empty, cannot reverse empty list */
                    {
                        printf("> Error: Cannot reverse an empty list.\n");
                    }
                }
                else if(strcmp(token, COMMAND_SAVE) == 0) /*User input matches save*/
                {
                    token = strtok(NULL, DELIMS);
                    commandSave(list, token); 
                }
                /*Input does not match anything in the commands*/
                else
                {
                    printf("> Input not recognised.\n");
                }
                token = strtok(NULL, DELIMS);
            }
        }
    }while(strcmp(input, COMMAND_QUIT) != 0);
    if(list != NULL) /*If the user has called quit, without unloading the list, this will unload before exiting */
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

    if(token == NULL)/*User has not specififed a file*/
    {
        printf("> Error: Please specify a file\n");
        return NULL;
    }
    else
    {
        printf("> Opening the file %s.\n", token); 
        list = commandLoad(token); /* Pass the token / file name to the commandLoad */
        return list;
    }
}

void tokenInsert(TelephoneBookList * list, char * token)
{
    char name[MAX];
    char telephone[MAX];
    int id;

        token = strtok(NULL, DELIMS);
        if(token != NULL) /* As long as the next token in the string is not NULL*/
        {
            id = strtol(token, &token, 0); /* strtol the string */
            token = strtok(NULL, DELIMS);
            if(token != NULL) /* As long as the next token in the string is not NULL*/
            {
                strcpy(name, token); /* Copy the string to the name array*/
                token= strtok(NULL, DELIMS);
                if(token != NULL) /* As long as the next and last token in the string is not NULL*/
                {
                    strcpy(telephone, token); /* Copy the string to the telephone array*/
                    commandInsert(list, id, name, telephone); /* Command insert the node*/
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

