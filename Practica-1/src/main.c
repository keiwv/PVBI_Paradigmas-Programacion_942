#include "raylib.h"
#include <stdio.h>
#include "Snake.h"
#include <time.h>

#define MAX_COL 30
#define MAX_ROWS 16

#define RECT_WIDTH 35
#define RECT_HEIGHT 35
#define SNAKE_SPEED 5

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

void updateGame(SnakeNode *head, Fruit *fruit);
void drawGame(SnakeNode *head, Fruit fruit, float deltaTime);

//***************** USEFUL FUNCTIONS **************
void centerTextYandX(const char *text, int fontSize, int y, int x, Color color);
Fruit getFruitRandom();
void updatePosition(int buttonPressed, SnakeNode *head, GameScene *Scene);
void updateDirection(int *buttonPressed);
void drawSnake(SnakeNode *head, Vector2 start);
int main()
{

    srand(time(NULL));
    InitWindow(screenWidth, screenHeight, "Snake Game");

    SetTargetFPS(10);
    GameScene Scene = PLAY;
    SnakeNode *head = initializeSnake((int)MAX_COL / 2, (int)MAX_ROWS / 2);
    int buttonPressed = STOP;
    float deltaTime;
    float elapsedTime = 0.0f;
    SetTargetFPS(165);
    Fruit fruit = getFruitRandom();

    while (!WindowShouldClose())
    {
        deltaTime = GetFrameTime();
        elapsedTime += deltaTime;
        // printf("X: %d, Y: %d\n", head->MainSnake.posX, head->MainSnake.posY);
        // printf("DELTATIME: %f\n", deltaTime);
        switch (Scene)
        {
        case MAIN_MENU:
            // Scene = updateMenu();
            drawMenu();
            break;
        case PLAY:
            updateDirection(&buttonPressed);
            if (elapsedTime >= 1.0f / SNAKE_SPEED)
            {
                updatePosition(buttonPressed, head, &Scene);
                elapsedTime = 0.0f;
            }

            updateGame(head, &fruit);
            // printf("%.2f\n", elapsedTime);

            drawGame(head, fruit, deltaTime);
            break;

        default:
            break;
        }
    }

    CloseWindow();

    deleteSnake(head);
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

void updateGame(SnakeNode *head, Fruit *fruit)
{

    Vector2 fruitPosition = {(float)fruit->posX, (float)fruit->posY};
    if (head->MainSnake.posX == fruit->posX)
    {
        if (head->MainSnake.posY == fruit->posY)
        {
            addNode(head, fruitPosition);
            *fruit = getFruitRandom();
        }
    }
}

void drawGame(SnakeNode *head, Fruit fruit, float deltaTime)
{
    int totalHeight = MAX_ROWS * (RECT_HEIGHT + 2);
    int totalWidth = MAX_COL * (RECT_WIDTH + 2);

    int startX = (screenWidth - totalWidth) / 2;
    int startY = (screenHeight - totalHeight) / 2;

    int posX;
    int posY;

    int posFruitX;
    int posFruitY;

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
    
    Vector2 start = {(float)startX, (float)startY};
    drawSnake(head, start);

    posFruitX = startX + fruit.posX * (RECT_WIDTH + 1);
    posFruitY = startY + fruit.posY * (RECT_HEIGHT + 1);
    DrawRectangle(posFruitX, posFruitY, RECT_WIDTH, RECT_HEIGHT, RED);

    EndDrawing();
}

void updatePosition(int buttonPressed, SnakeNode *head, GameScene *Scene)
{
    SnakeNode *current = head->next;
    int prevX;
    int prevY;
    int tempX;
    int tempY;
    prevX = head->MainSnake.posX;
    prevY = head->MainSnake.posY;

    while (current != NULL)
    {
        tempX = current->MainSnake.posX;
        tempY = current->MainSnake.posY;
        current->MainSnake.posX = prevX;
        current->MainSnake.posY = prevY;
        prevX = tempX;
        prevY = tempY;

        current = current->next;
    }

    switch (buttonPressed)
    {
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
    current = head->next;
    while (current != NULL)
    {
        if (head->MainSnake.posX == current->MainSnake.posX)
        {
            if (head->MainSnake.posY == current->MainSnake.posY)
            {
                *Scene = GAME_OVER;
            }
        }
        current = current->next;
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

void updateDirection(int *buttonPressed)
{
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

void drawSnake(SnakeNode *head, Vector2 start)
{
    SnakeNode *currentNode = head;
    int posXSnake;
    int posYSnake;
    while (currentNode != NULL)
    {
        posXSnake = start.x + currentNode->MainSnake.posX * (RECT_WIDTH + 1);
        posYSnake = start.y + currentNode->MainSnake.posY * (RECT_HEIGHT + 1);

        DrawRectangle(posXSnake, posYSnake, RECT_WIDTH, RECT_HEIGHT, GREEN);
        // printf("X: %d, Y: %d\n", currentNode->MainSnake.posX, currentNode->MainSnake.posY);
        currentNode = currentNode->next;
    }
}
