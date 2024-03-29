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

SnakeNode *createNode(Vector2 position);
void deleteSnake(SnakeNode *head);
void addNode(SnakeNode *head, Vector2 position);