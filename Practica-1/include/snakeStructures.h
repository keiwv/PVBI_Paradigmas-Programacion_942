typedef struct _Snake 
{
    int posX;
    int posY;
} Snake;

typedef struct _SnakeNode
{
    Snake MainSnake;
    struct _SnakeNode *next;
} SnakeNode;

typedef struct _Fruit
{
    int posX;
    int posY;
} Fruit;

SnakeNode *createNode();
void deleteSnake(SnakeNode *head);
void addNode(SnakeNode *head);