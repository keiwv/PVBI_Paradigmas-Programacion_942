typedef struct _Snake 
{
    int score;
    int tailLength;
} Snake;

typedef struct _SnakeNode
{
    Snake MainSnake;
    struct _SnakeNode *next;
} SnakeNode;