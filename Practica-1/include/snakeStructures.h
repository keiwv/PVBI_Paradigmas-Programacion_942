typedef struct _Snake 
{
    int right;
    int left;
    int top;
    int bottom;
} Snake;

typedef struct _SnakeNode
{
    Snake MainSnake;
    struct _SnakeNode *next;
} SnakeNode;

SnakeNode *createNodo();
void deleteSnake(SnakeNode **head);
void addNode(SnakeNode **head);