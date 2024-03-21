#include "raylib.h"
#include <stdio.h>
#include "Snake.h"
#include <time.h>

#define MAX_COL 30
#define MAX_ROWS 16

#define RECT_WIDTH 35
#define RECT_HEIGHT 35

#define LEFT 1
#define RIGHT 2
#define TOP 3
#define DOWN 4
#define STOP 0

int screenWidth = 1280;
int screenHeight = 720;
typedef enum
{
    MAIN_MENU,
    PLAY,
    PAUSE_MENU,
    GAME_OVER
} GameScene;

//***************** SCENES FUNCTIONS **************
// GameScene updateMenu();
void drawMenu();

Fruit updateGame(SnakeNode *head, Fruit fruit, int *buttonPressed);
void drawGame(SnakeNode *head, Fruit fruit);

//***************** USEFUL FUNCTIONS **************
void centerTextYandX(const char *text, int fontSize, int y, int x, Color color);
Fruit getFruitRandom();
void updatePosition(int *buttonPressed, SnakeNode *head);

int main()
{

    srand(time(NULL));
    InitWindow(screenWidth, screenHeight, "Snake Game");

    SetTargetFPS(10);
    GameScene Scene = PLAY;
    SnakeNode *head = initializeSnake((int)MAX_COL / 2, (int)MAX_ROWS / 2);
    int buttonPressed = STOP;
    Fruit fruit = getFruitRandom();

    while (!WindowShouldClose())
    {
        switch (Scene)
        {
        case MAIN_MENU:
            // Scene = updateMenu();
            drawMenu();
            break;
        case PLAY:
            fruit = updateGame(head, fruit, &buttonPressed);
            drawGame(head, fruit);
            break;

        default:
            break;
        }
    }

    CloseWindow();
    return 0;
}

/*GameScene updateMenu()
{

}*/

void drawMenu()
{
    BeginDrawing();
    ClearBackground(BLACK);
    centerTextYandX("JUGAR", 60, 0, 0, WHITE);
    centerTextYandX("SALIR", 30, 50, 0, WHITE);
    EndDrawing();
}

Fruit updateGame(SnakeNode *head, Fruit fruit, int *buttonPressed)
{
    updatePosition(buttonPressed, head);
    if (head->MainSnake.posX == fruit.posX)
    {
        if (head->MainSnake.posY == fruit.posY)
        {
            addNode(head);
            return getFruitRandom();
        }
    }
    return fruit;
}

void drawGame(SnakeNode *head, Fruit fruit)
{
    int totalHeight = MAX_ROWS * (RECT_HEIGHT + 2);
    int totalWidth = MAX_COL * (RECT_WIDTH + 2);

    int startX = (screenWidth - totalWidth) / 2;
    int startY = (screenHeight - totalHeight) / 2;

    int posXSnake;
    int posYSnake;

    int posX;
    int posY;

    int posFruitX;
    int posFruitY;

    SnakeNode *currentNode = head;
    BeginDrawing();

    ClearBackground(BLACK);
    for (int i = 0; i < MAX_COL; i++)
    {
        for (int j = 0; j < MAX_ROWS; j++)
        {
            posX = startX + i * (RECT_WIDTH + 1);
            posY = startY + j * (RECT_HEIGHT + 1);

            DrawRectangle(posX, posY, RECT_WIDTH, RECT_HEIGHT, WHITE);
        }
    }

    while (currentNode != NULL)
    {
        posXSnake = startX + currentNode->MainSnake.posX * (RECT_WIDTH + 1);
        posYSnake = startY + currentNode->MainSnake.posY * (RECT_HEIGHT + 1);

        DrawRectangle(posXSnake, posYSnake, RECT_WIDTH, RECT_HEIGHT, GREEN);
        currentNode = currentNode->next;
    }

    posFruitX = startX + fruit.posX * (RECT_WIDTH + 1);
    posFruitY = startY + fruit.posY * (RECT_HEIGHT + 1);
    DrawRectangle(posFruitX, posFruitY, RECT_WIDTH, RECT_HEIGHT, RED);

    EndDrawing();
}
void updatePosition(int *buttonPressed, SnakeNode *head)
{
    switch (*buttonPressed)
    {
    case STOP:
        // Snake doesn't move until the player presses a key.
        break;
    case LEFT:
        head->MainSnake.posX--;
        break;
    case RIGHT:
        head->MainSnake.posX++;
        break;
    case TOP:
        head->MainSnake.posY--;
        break;
    case DOWN:
        head->MainSnake.posY++;
        break;
    }
    
    if (IsKeyPressed(KEY_S))
    {
        *buttonPressed = DOWN;
    }
    if (IsKeyPressed(KEY_W))
    {
        *buttonPressed = TOP;
    }
    if (IsKeyPressed(KEY_D))
    {
        *buttonPressed = RIGHT;
    }

    if (IsKeyPressed(KEY_A))
    {
        *buttonPressed = LEFT;
    }

    
}

//****************** USEFUL FUNCTIONS *************************
void centerTextYandX(const char *text, int fontSize, int y, int x, Color color)
{
    int textWidth;
    int PosX;
    int PosY;

    textWidth = MeasureText(text, fontSize);
    PosX = ((screenWidth - textWidth) / 2) + x;
    PosY = ((screenHeight - fontSize) / 2) + y;

    DrawText(text, PosX, PosY, fontSize, color);
}

Fruit getFruitRandom()
{
    Fruit fruitTemp;
    fruitTemp.posX = rand() % (MAX_COL - MAX_ROWS + 1);
    fruitTemp.posY = rand() % (MAX_COL - MAX_ROWS + 1);
    return fruitTemp;
}
