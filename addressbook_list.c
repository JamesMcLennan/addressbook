#include "addressbook_list.h"

TelephoneBookList * createTelephoneBookList()
{
    TelephoneBookList * telephonebooklist = malloc(sizeof(TelephoneBookList));

    if(telephonebooklist != NULL)
    {
        telephonebooklist->head = NULL;
        telephonebooklist->tail = NULL;
        telephonebooklist->current = NULL;
        telephonebooklist->size = 0;
        return telephonebooklist;
    }
    else
    {
        freeTelephoneBookList(telephonebooklist);
        return NULL;
    }
}

void freeTelephoneBookList(TelephoneBookList* list)
{
    free(list);
}

TelephoneBookNode * createTelephoneBookNode()
{
    TelephoneBookNode * newNode = malloc(sizeof(TelephoneBookNode));
    if(newNode != NULL)
    {
        newNode->nextNode = NULL;
        newNode->previousNode = NULL;
        return newNode;
    }
    else
    {
        freeTelephoneBookNode(newNode);
        return NULL;
    }
}

void freeTelephoneBookNode(TelephoneBookNode * node)
{
    while(node != NULL)
    {
        TelephoneBookNode * deleteNode = node;
        node = node->nextNode;

        free(deleteNode);
    }
}

Boolean insert(TelephoneBookList * list, TelephoneBookNode * node)
{
    TelephoneBookNode * prevNode, * curNode;
    
    prevNode = NULL;
    curNode = list->head;

    while(curNode != NULL)
    {
        prevNode = curNode;
        curNode = curNode->nextNode;
    }
    if(list->head == NULL)
    {
        list->head = node;
        list->current = node;
        list->tail = node;
        node->previousNode = NULL;
        node->nextNode = NULL;
    }

    else if(list->head != NULL)
    {
        prevNode->nextNode = node;
        node->nextNode = NULL;
        node->previousNode = prevNode;
        list->tail = node;
    }
    
    list->size++;
    return TRUE;
}

Boolean forward(TelephoneBookList * list, int forward)
{
    TelephoneBookNode * firstNode = list->current, * originalNode = list->current;
    int i;
    for(i = 0; i < forward; i++)
    {
        if(firstNode->nextNode == NULL)
        {
            list->current = originalNode;
            return FALSE;
        }
        list->current = firstNode->nextNode;
        firstNode = list->current;
    }
    return TRUE;
}

Boolean backward(TelephoneBookList * list, int backward)
{
    TelephoneBookNode * firstNode = list->current, * originalNode = list->current;
    int i;
    for(i = 0; i < backward; i++)
    {
        if(firstNode->previousNode == NULL)
        {
            list->current = originalNode;
            return FALSE;
        }
        list->current = firstNode->previousNode;
        firstNode = list->current;
    }
    return TRUE;
}

Boolean delete(TelephoneBookList * list)
{
    TelephoneBookNode *prevNode , * nextNode, * deletedNode = list->current;

    if(deletedNode->previousNode == NULL)
    {
        nextNode = deletedNode->nextNode;
        nextNode->previousNode = NULL;

        list->head = nextNode;

        free(deletedNode);

        list->current = nextNode;
        list->size--;
    }
    else if(deletedNode->nextNode == NULL)
    {
        prevNode = deletedNode->previousNode;
        prevNode->nextNode = NULL;

        list->tail = prevNode;

        free(deletedNode);
        
        list->current = prevNode;
        list->size--;
    }
    else
    {
        prevNode = deletedNode->previousNode;
        nextNode = deletedNode->nextNode;

        prevNode->nextNode = nextNode;
        nextNode->previousNode = prevNode;

        free(deletedNode);

        list->current = nextNode;
        list->size--;
    }
    return FALSE;
}

TelephoneBookNode * findByID(TelephoneBookList * list, int id)
{
    TelephoneBookNode * findNode = list->head;
    while(findNode != NULL)
    {
        if(id == findNode->id)
        {
            printf("sokdao\n");
            return findNode;       
        }
        findNode = findNode->nextNode;
    }
    return NULL;
}

TelephoneBookNode * findByName(TelephoneBookList * list, char * name)
{
    TelephoneBookNode * findNode = list->head;
    while(findNode != NULL)
    {
        if(strcmp(findNode->name, name) == 0)
        {
            list->current = findNode;
            return findNode;
        }
        findNode = findNode->nextNode;
    }
    return NULL;
}
