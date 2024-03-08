#include <stdlib.h>
#include <stdio.h>
#include "snakeStructures.h"

SnakeNode *createNode()
{
    SnakeNode *NewNode = (SnakeNode *)malloc(sizeof(SnakeNode));
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

void addNode(SnakeNode *head)
{
    SnakeNode *newNode = (SnakeNode *)malloc(sizeof(SnakeNode));
    SnakeNode *current = head;

    if (newNode == NULL)
    {
        printf("Memory allocation failed for new node.\n");
        return;
    }
    if (head == NULL) {
        printf("Error: Cannot add node to NULL pointer.\n");
        return;
    }

    while (current->next != NULL)
    {
        current = current->next;
    }

    newNode->MainSnake.posX = current->MainSnake.posX;
    newNode->MainSnake.posY = current->MainSnake.posY;
    newNode->next = NULL;

    current->next = newNode;
}

SnakeNode* initializeSnake(int posX, int posY) {
    SnakeNode* head = createNode();
    if (head == NULL) {
        printf("Error: Could not initialize snake.\n");
        return NULL;
    }

    head->MainSnake.posX = posX;
    head->MainSnake.posY = posY;

    return head;
}

