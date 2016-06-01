/* Author: James McLennan / s3543182 2016 RMIT*/
#include "addressbook_list.h"

TelephoneBookList * createTelephoneBookList()
{
    TelephoneBookList * telephonebooklist = malloc(sizeof(TelephoneBookList)); /* Allocate memory for the new list*/

    if(telephonebooklist != NULL) /* If the list has been created*/
    {
        telephonebooklist->head = NULL; /* Initialise all members of the list*/
        telephonebooklist->tail = NULL;
        telephonebooklist->current = NULL;
        telephonebooklist->size = 0;
        return telephonebooklist;
    }
    else /*CPU could not allocate memory for the list*/
    {
        freeTelephoneBookList(telephonebooklist);
        printf("> Error: Unable to allocate memory for the list. Please contact with the system administator\n"); /* Generic fail message*/
        return NULL;
    }
}

void freeTelephoneBookList(TelephoneBookList* list)
{
    free(list); /* Free the memory allocated for the list*/
}

TelephoneBookNode * createTelephoneBookNode()
{
    TelephoneBookNode * newNode = malloc(sizeof(TelephoneBookNode));/* Allocate memory for the new node*/
    if(newNode != NULL) 
    {
        newNode->nextNode = NULL;/* Initialise next + previous node pointers*/
        newNode->previousNode = NULL;
        return newNode;
    }
    else
    {
        freeTelephoneBookNode(newNode);
        printf("> Error: Unable to allocate memory for the node. Please contact the system administrator.\n"); /* Generic fail message */
        return NULL;
    }
}

void freeTelephoneBookNode(TelephoneBookNode * node)
{
    while(node != NULL) /* While the node exists*/
    {
        TelephoneBookNode * deleteNode = node; /*Assign a pointer to the current node */
        node = node->nextNode; /* current nodes next node is assigned to the while conditioned node*/

        free(deleteNode); /*Free the node*/
    }
}

Boolean insert(TelephoneBookList * list, TelephoneBookNode * node)
{
    TelephoneBookNode * prevNode, * curNode;
    
    prevNode = NULL;
    curNode = list->head;

    while(curNode != NULL) /* Creates the prevNode position*/
    {
        prevNode = curNode;
        curNode = curNode->nextNode;
    }
    if(list->head == NULL)
    {
        list->head = node; /* When the list is empty, assign the list members to the first node.*/
        list->current = node;
        list->tail = node;
        node->previousNode = NULL; /* Previous node of the first entry will ALWAYS be NULL*/
        node->nextNode = NULL; /* Temp assign the nextNode to NULL. This will be updated during the list load. However, if only 1 member is loaded, the nextNode is NULL*/
    }

    else if(list->head != NULL)
    {
        prevNode->nextNode = node; /* The prevNode position created in the while loop, points to the next node*/
        node->nextNode = NULL; /* Update the nextNode to point to NULL*/
        node->previousNode = prevNode; /* assign the previous node pointer to the prevNode*/
        list->tail = node; /* Update tail to = node, this will update until the last node is loaded in which that is now the tail.*/
    }
    
    list->size++; /*Increase the size of the list */
    return TRUE;
}

Boolean forward(TelephoneBookList * list, int forward)
{
    TelephoneBookNode * firstNode = list->current, * originalNode = list->current;
    int i;

    for(i = 0; i < forward; i++)
    {
        if(firstNode->nextNode == NULL)/* If the user attempts to move forward from the last position in the last*/
        {
            list->current = originalNode; /* Return the CUR to the orginal node*/
            return FALSE;
        }
        list->current = firstNode->nextNode; /* Move the current forward one node at a time*/
        firstNode = list->current; /* The current node is re-assigned*/
    }
    return TRUE;
}

Boolean backward(TelephoneBookList * list, int backward)
{
    TelephoneBookNode * firstNode = list->current, * originalNode = list->current;
    int i;
    for(i = 0; i < backward; i++)
    {
        if(firstNode->previousNode == NULL) /* If the user attempts to move bacwkard from the first position in the list*/
        {
            list->current = originalNode; /* Return the CUR to the original node*/
            return FALSE;
        }
        list->current = firstNode->previousNode; /* Move the current node backward one node at a time*/
        firstNode = list->current; /* Re-assign the node to the current*/
    }
    return TRUE;
}

Boolean delete(TelephoneBookList * list)
{
    TelephoneBookNode *prevNode , * nextNode, * deletedNode = list->current;

    if(deletedNode->previousNode == NULL)/* If the current node is at the head*/
    {
        nextNode = deletedNode->nextNode; /* Assign the currentNodes next node to the holding node.*/
        nextNode->previousNode = NULL;/*previousNode of the current nodes next position is null */

        list->head = nextNode; /*The list head now = nextNode, which is the currentnodes next node */

        free(deletedNode); /* Free the current node*/

        list->current = nextNode; /* re-assign the current node to the nextNode*/
        list->size--;/*Reduce the size of the list */
    }
    else if(deletedNode->nextNode == NULL) /* If the current node is at the tail*/
    {
        prevNode = deletedNode->previousNode; /* Assign the current nodes previous node to the prevNode*/
        prevNode->nextNode = NULL; /* the nextNode from the current nodes previous node, is NULL*/

        list->tail = prevNode; /* The list tail is now = prevNode, which is the current nodes previous node*/

        free(deletedNode); /* Free the current node*/
        
        list->current = prevNode; /* Assign the current to the previous position, from the previous Current*/
        list->size--; /* Reduce the size of the list*/
    }
    else
    {
        prevNode = deletedNode->previousNode; /*Assign the previous node of the current */
        nextNode = deletedNode->nextNode; /*Assign the next node of the current */

        prevNode->nextNode = nextNode; /* Assign the node's next and previous positions*/
        nextNode->previousNode = prevNode;

        free(deletedNode); /* Free the deleted node*/

        list->current = nextNode; /* Re assign the current node*/
        list->size--; /* Reduce the size*/
    }
    return FALSE;
}

TelephoneBookNode * findByID(TelephoneBookList * list, int id)
{
    TelephoneBookNode * findNode = list->head;
    while(findNode != NULL) /* While the findNode does not = NULL*/
    {
        if(id == findNode->id) /* Check if the ID passed is equal to the current node's ID*/
        {
            return findNode; /* If true, return the ID*/
        }
        findNode = findNode->nextNode; /* Move to the next node and check*/
    }
    return NULL; /* Return NULL if no ID matches.*/
}

TelephoneBookNode * findByName(TelephoneBookList * list, char * name)
{
    TelephoneBookNode * findNode = list->head;
    while(findNode != NULL) /* While the findNode does not = NULL*/
    {
        if(strcmp(findNode->name, name) == 0) /* If the node's name member matches the name passed*/
        {
            list->current = findNode; /* Change the current position to this node*/
            return findNode;/* Return the node*/
        }
        findNode = findNode->nextNode; /* If the node does match in the if statement, move to the next node*/
    }
    return NULL; /* If no name matches, return NULL*/
}
