#include "addressbook_list.h"

TelephoneBookList * createTelephoneBookList()
{
    TelephoneBookList * telephonebooklist = malloc(sizeof(*telephonebooklist));

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
    TelephoneBookNode * newNode = malloc(sizeof(*newNode));
    if(newNode != NULL)
    {
        newNode->nextNode = NULL;
        newNode->previousNode = NULL;
        return newNode;
    }
    else
    {
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
    }

    else if(list->head != NULL)
    {
        prevNode->nextNode = node;
        node->nextNode = curNode;
        node->previousNode = prevNode;
    }
    list->size++;
    return TRUE;
}

Boolean forward(TelephoneBookList * list, int forward)
{
    TelephoneBookNode * firstNode = list->current;
    int i;
    if(forward < list->size)
    {
        while(i < forward)
        {
            if(firstNode->nextNode == NULL)
            {
                return FALSE;
            }
            list->current = firstNode->nextNode;
            firstNode = list->current;
            i++;
        }
    }
    else
    {
        return FALSE;
    }
    return TRUE;
}

Boolean backward(TelephoneBookList * list, int backward)
{
    TelephoneBookNode * firstNode = list->current;
    int i;
    if(backward < list->size)
    {
        while(i < backward)
        {
            if(firstNode->previousNode == NULL)
            {
                return FALSE;
            }
            list->current = firstNode->previousNode;
            firstNode = list->current;
            i++;
        }
    }
    else
    {
        return FALSE;
    }
    return TRUE;
}

Boolean delete(TelephoneBookList * list)
{
    return FALSE;
}

TelephoneBookNode * findByID(TelephoneBookList * list, int id)
{
    return NULL;
}

TelephoneBookNode * findByName(TelephoneBookList * list, char * name)
{
    return NULL;
}
