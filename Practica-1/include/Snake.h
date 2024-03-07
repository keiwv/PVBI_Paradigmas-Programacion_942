#include <stdlib.h>
#include <stdio.h>
#include "snakeStructures.h"


SnakeNode *CreateNodo(int score, int tailLength)
{
    SnakeNode *NewNode = (SnakeNode * )malloc(sizeof(SnakeNode));
    if (NewNode == NULL)
    {
        printf("Node couldn't be created. Missing memory.");
        return 0;
    }
    NewNode->MainSnake.score = score;
    NewNode->MainSnake.tailLength = tailLength;
    NewNode->next = NULL;
    return NewNode;
}

void DeleteNode(SnakeNode *head)
{
    SnakeNode *tempNode = CreateNodo(0,0);
    tempNode = head;

    while (tempNode->next)
    {
        
    }
    
}