#include "addressbook.h"

int main(int argc, char ** argv)
{
    char usertext[FULLSIZE];
    char *token;
    char *input;
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
            }
            else if(strcmp(token, COMMAND_DISPLAY) == 0)
            {
                if(list == NULL)
                {
                    list = createTelephoneBookList();
                    commandDisplay(list);
                }
                else
                {
                    commandDisplay(list);
                }
            }
            /*Input does not match / Buffer overflow*/
            else
            {
                printf("> Input not recognised.\n");
            }
            token = strtok(NULL, DELIMS);
        }
    }while(strcmp(input, COMMAND_QUIT) != 0);
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

