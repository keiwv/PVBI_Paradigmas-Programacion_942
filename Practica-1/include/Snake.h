#include <stdlib.h>
#include <stdio.h>
#include "snakeStructures.h"


SnakeNode *createNode()
{
    SnakeNode *NewNode = (SnakeNode * )malloc(sizeof(SnakeNode));
    if (NewNode == NULL)
    {
        printf("Node couldn't be created. Missing memory.");
        return 0;
    }
    NewNode->next = NULL;
    return NewNode;
}

void deleteSnake(SnakeNode **head)
{
    SnakeNode *tempNode = *head;
    while (tempNode != NULL)
    {
        SnakeNode *nextNode = tempNode->next;
        free(tempNode);
        tempNode = nextNode;
    }

    *head = NULL;
}

void addNode(SnakeNode **head)
{
    SnakeNode *newNode = createNode();
    if (newNode == NULL)
    {
        printf("Failed to create a new node.");
        return;
    }

    newNode->next = *head;
    *head = newNode;
}