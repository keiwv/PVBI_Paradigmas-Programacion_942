#include <stdlib.h>
#include <stdio.h>
#include "snakeStructures.h"

  

SnakeNode *createNode(Vector2 position, float degrees)
{
    SnakeNode *NewNode = (SnakeNode *)malloc(sizeof(SnakeNode));
    if (NewNode == NULL)
    {
        printf("Node couldn't be created. Missing memory.");
        return 0;
    }
    NewNode->MainSnake.posX = position.x;
    NewNode->MainSnake.posY = position.y;
    NewNode->MainSnake.degrees = degrees;
    NewNode->next = NULL;
    return NewNode;
}

void deleteSnake(SnakeNode *head)
{
    SnakeNode *tempNode = head;
    SnakeNode *nextNode;
    while (tempNode != NULL)
    {
        nextNode = tempNode->next;
        free(tempNode);
        tempNode = nextNode;
    }

    head = NULL;
    printf("INFO: Snake deleted successfully\n");
}

void addNode(SnakeNode *head, Vector2 position, float degrees)
{
    if (head == NULL)
    {
        printf("Error: Cannot add node to NULL pointer.\n");
        return;
    }

    SnakeNode *newNode = createNode(position, degrees);
    if (newNode == NULL)
    {
        printf("Memory allocation failed for new node.\n");
        return;
    }

    SnakeNode *current = head;
    while (current->next != NULL)
    {
        current = current->next;
    }

    current->next = newNode;
}

SnakeNode *initializeSnake(int posX, int posY)
{
    Vector2 position = {(float)posX, (float)posY};
    SnakeNode *head = createNode(position, 0.0f);

    if (head == NULL)
    {
        printf("Error: Could not initialize snake.\n");
        return NULL;
    }

    head->MainSnake.posX = posX;
    head->MainSnake.posY = posY;
    head->MainSnake.degrees = 0.0f;

    return head;
}
