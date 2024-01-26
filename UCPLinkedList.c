#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "UCPLinkedList.h"

/*
Title:      		UCPLinkedList.c
Author:     		Jet Ng
Date/LastModified:  31/05/2023
Description:       	Linked List dada structure for the Box game, Assignment 2 COMP1000 - UCP

                    Implements generic doubly ended linked list functionality to be used in the
                    box game, where it is used to store structs containing the game state as the
                    user inputs and updates the game. 

                    Game loads -> gameState is saved to linked list -> player inputs update -> loop back
*/

/*
METHOD: 	insertFirst
IMPORT: 	pList (UCPLinkedList*), pValue (void*)
EXPORT: 	none, creates node and inserts into first position in linked list pList
ASSERTION: 	pList will be updated with a new node at the head with nodeValue of pValue
ALGORITHM:
			Malloc and update a node to be added into the linked list.
            Update the linked list head/tail as needed to point to the new node
            as the first entry.
*/
void insertFirst(UCPLinkedList* pList, void* pValue) 
{
    UCPGameNode* newNode = (UCPGameNode*)malloc(sizeof(UCPGameNode));
    newNode->nodeValue = pValue;
    newNode->nextP = NULL;
    newNode->prevP = NULL;

    if (pList->listHead == NULL) 
    {
        pList->listHead = newNode;
        pList->listTail = newNode;
    } 
    else 
    {
        newNode->nextP = pList->listHead;
        pList->listHead->prevP = newNode;
        pList->listHead = newNode;
    }
}

/*
METHOD: 	insertLast
IMPORT: 	pList (UCPLinkedList*), pValue (void*)
EXPORT: 	none, creates node and inserts into last position in linked list pList
ASSERTION: 	pList will be updated with a new node at the tail with nodeValue of pValue
ALGORITHM:
			Malloc and update a node to be added into the linked list.
            Update the linked list head/tail as needed to point to the new node
            as the last entry. This wasn't used/needed in the box game, but is a normal
            function to have in a doubly ended linked list.
*/
void insertLast(UCPLinkedList* pList, void* pValue) 
{
    UCPGameNode* newNode = (UCPGameNode*)malloc(sizeof(UCPGameNode));
    newNode->nodeValue = pValue;
    newNode->nextP = NULL;
    newNode->prevP = NULL;

    if (pList->listHead == NULL) 
    {
        pList->listHead = newNode;
        pList->listTail = newNode;
    } 
    else 
    {
        newNode->prevP = pList->listTail;
        pList->listTail->nextP = newNode;
        pList->listTail = newNode;
    }
}

/*
METHOD: 	removeFirst
IMPORT: 	pList (UCPLinkedList*)
EXPORT: 	value (void*)
ASSERTION: 	First node in the linked list pList will be removed and the nodeValue exported from the function
ALGORITHM:
			Take first node in linked list, get the nodeValue from it to be returned, and update head/tail
            as needed to reflect the removal of the first node (second node then gets updated to first).
*/
void* removeFirst(UCPLinkedList* pList) 
{
    if (pList->listHead == NULL) 
    {
        return NULL;
    } 
    else 
    {
        UCPGameNode* firstNode = pList->listHead;
        void* value = firstNode->nodeValue;
        pList->listHead = firstNode->nextP;

        if (pList->listHead != NULL) 
        {
            pList->listHead->prevP = NULL;
        } 
        else 
        {
            pList->listTail = NULL;
        }

        firstNode->nextP = NULL;
        firstNode->prevP = NULL;

        free(firstNode);
        return value;
    }
}

/*
METHOD: 	removeLast
IMPORT: 	pList (UCPLinkedList*)
EXPORT: 	value (void*)
ASSERTION: 	Last node in the linked list pList will be removed and the nodeValue exported from the function
ALGORITHM:
			Take last node in linked list, get the nodeValue from it to be returned, and update head/tail
            as needed to reflect the removal of the first node (penultimate node then gets updated to last).
            This was not used in the box game, but same as insertLast() is part of normal functionality for
            a doubly ended linked list.
*/
void* removeLast(UCPLinkedList* pList) 
{
    if (pList->listHead == NULL) 
    {
        return NULL;
    } 
    else if (pList->listHead == pList->listTail) 
    {
        void* lastValue = pList->listHead->nodeValue;
        removeFirst(pList);
        return lastValue;
    } 
    else 
    {
        UCPGameNode* lastNode = pList->listTail;
        void* value = lastNode->nodeValue;
        pList->listTail = lastNode->prevP;
        pList->listTail->nextP = NULL;

        free(lastNode);
        return value;
    }
}

/*
METHOD: 	peekFirst
IMPORT: 	pList (UCPLinkedList*)
EXPORT: 	nodeValue (void*)
ASSERTION: 	Return/export nodeValue of the head of the linked list.
ALGORITHM:
			Take first node in linked list, get the nodeValue from it to be returned.
*/
void* peekFirst(UCPLinkedList* pList)
{
    if (pList->listHead == NULL)
    {
        return NULL;
    }
    else
    {
        return (pList->listHead->nodeValue);
    }
}

/*
METHOD: 	printLinkedList
IMPORT: 	pList (UCPLinkedList*)
EXPORT: 	none, prints nodeValue to terminal
ASSERTION: 	nodeValue can be printed to terminal
ALGORITHM:
			Generic function to iterate over the linked list and print the nodeValue to terminal/printf.
            For box game this function is not really useable as nodeValue was a struct, but if nodeValue
            was a primitive type like an int or char, then it would print those values to terminal.
*/
void printLinkedList(UCPLinkedList* pList) 
{
    UCPGameNode* currentNode = pList->listHead;
    printf("[ ");
    while (currentNode != NULL) 
    {
        printf("%p ", currentNode->nodeValue);
        currentNode = currentNode->nextP;
    }
    printf("]\n");
}

/*
METHOD: 	freeListNodes
IMPORT: 	pList (UCPLinkedList*)
EXPORT: 	none
ASSERTION: 	Iterate through the linked list, freeing individual nodes in the linked list pList.
ALGORITHM:
			All nodes will be free'd one by one as the linked list is iterated through.
*/
void freeListNodes(UCPLinkedList* pList)
{
    UCPGameNode* currentNode = pList->listHead;
    while (currentNode != NULL) 
    {
        UCPGameNode* nextNode = currentNode->nextP;
        free(currentNode);
        currentNode = nextNode;
    }
    pList->listHead = NULL;
    pList->listTail = NULL;
}