#ifndef UCPLINKEDLIST_H
#define UCPLINKEDLIST_H

typedef struct UCPGameNode 
{
    void* nodeValue;
    struct UCPGameNode* nextP;
    struct UCPGameNode* prevP;
} UCPGameNode;

typedef struct 
{
    UCPGameNode* listHead;
    UCPGameNode* listTail;
} UCPLinkedList;

void insertFirst(UCPLinkedList* pList, void* pValue);
void insertLast(UCPLinkedList* pList, void* pValue);
void* removeFirst(UCPLinkedList* pList);
void* removeLast(UCPLinkedList* pList);
void printLinkedList(UCPLinkedList* pList);
void* peekFirst(UCPLinkedList* pList);
void freeListNodes(UCPLinkedList* pList);

#endif