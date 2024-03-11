#include "raylib.h"
#include <stdio.h>
#include "Snake.h"
#include <time.h>

#define MAX_COL 30
#define MAX_ROWS 16

#define RECT_WIDTH 35
#define RECT_HEIGHT 35

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

Fruit updateGame(SnakeNode *head, Fruit fruit);
void drawGame(SnakeNode *head, Fruit fruit);

//***************** USEFUL FUNCTIONS **************
void centerTextYandX(const char *text, int fontSize, int y, int x, Color color);
Fruit getFruitRandom();

int main()
{

    srand(time(NULL));
    InitWindow(screenWidth, screenHeight, "Snake Game");

    SetTargetFPS(5);
    GameScene Scene = PLAY;
    SnakeNode *head = initializeSnake((int)MAX_COL / 2, (int)MAX_ROWS / 2);
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
            fruit = updateGame(head, fruit);
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

Fruit updateGame(SnakeNode *head, Fruit fruit)
{
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
    currentNode->MainSnake.posX++;
    BeginDrawing();

    ClearBackground(BLACK);
    for (int i = 0; i < MAX_COL; i++)
    {
        for (int j = 0; j < MAX_ROWS; j++)
        {
            posX = startX + i * (RECT_WIDTH + 2);
            posY = startY + j * (RECT_HEIGHT + 2);

            DrawRectangle(posX, posY, RECT_WIDTH, RECT_HEIGHT, WHITE);
        }
    }

    while (currentNode != NULL)
    {
        posXSnake = startX + currentNode->MainSnake.posX * (RECT_WIDTH + 2);
        posYSnake = startY + currentNode->MainSnake.posY * (RECT_HEIGHT + 2);

        DrawRectangle(posXSnake, posYSnake, RECT_WIDTH, RECT_HEIGHT, GREEN);
        currentNode = currentNode->next;
    }

    posFruitX = startX + fruit.posX * (RECT_WIDTH + 2);
    posFruitY = startY + fruit.posY * (RECT_HEIGHT + 2);
    DrawRectangle(posFruitX, posFruitY, RECT_WIDTH, RECT_HEIGHT, RED);

    EndDrawing();
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
