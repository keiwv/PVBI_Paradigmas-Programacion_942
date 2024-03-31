#include "raylib.h"
#include <stdio.h>
#include "Snake.h"
#include <time.h>

#define GREENSNAKE \
    CLITERAL(Color) { 131, 191, 114, 255 }
#define GREENSNAKEDARK \
    CLITERAL(Color) { 64, 123, 51, 255 }

#define WHITELIGHT \
    CLITERAL(Color) { 255, 255, 255, 180 }

#define MAX_COL 30
#define MAX_ROWS 16

#define RECT_WIDTH 40
#define RECT_HEIGHT 40
#define SNAKE_SPEED 5

#define LEFT 1
#define RIGHT 2
#define TOP 3
#define DOWN 4
#define STOP 0

int screenWidth = 1920;
int screenHeight = 1080;
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
void drawGame(SnakeNode *head, Fruit fruit, float deltaTime, Texture snakeBody, Texture snakeHead, Texture apple, Texture background);

//***************** USEFUL FUNCTIONS **************
void centerTextYandX(const char *text, int fontSize, int y, int x, Color color);
Fruit getFruitRandom(SnakeNode *head);
void updatePosition(int buttonPressed, SnakeNode *head, GameScene *Scene);
void updateDirection(int *buttonPressed);
void drawSnake(SnakeNode *head, Vector2 start, Texture snakeBody, Texture snakeHead);

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
    Fruit fruit = getFruitRandom(head);

    Texture apple = LoadTexture("assets/textures/FoodApple.png");
    Texture snakeBody = LoadTexture("assets/textures/SnakeBody.png");
    Texture snakeHead = LoadTexture("assets/textures/SnakeHead.png");
    Texture background = LoadTexture("assets/background/pxfuel.png");

    // background.height = screenHeight;
    // background.width = screenWidth;

    apple.height = RECT_HEIGHT;
    apple.width = RECT_WIDTH;

    snakeBody.height = RECT_HEIGHT + 10;
    snakeBody.width = RECT_WIDTH + 10;

    snakeHead.height = RECT_HEIGHT + 10;
    snakeHead.width = RECT_WIDTH + 10;

    while (!WindowShouldClose())
    {
        deltaTime = GetFrameTime();
        elapsedTime += deltaTime;
        if (IsKeyPressed(KEY_O))
        {
            ToggleFullscreen();
        }

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

            drawGame(head, fruit, deltaTime, snakeBody, snakeHead, apple, background);
            break;

        default:
            break;
        }
    }

    CloseWindow();

    deleteSnake(head);
    UnloadTexture(apple);
    UnloadTexture(snakeBody);
    UnloadTexture(snakeHead);

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
            addNode(head, fruitPosition, head->MainSnake.degrees);
            *fruit = getFruitRandom(head);
        }
    }
}

void drawGame(SnakeNode *head, Fruit fruit, float deltaTime, Texture snakeBody, Texture snakeHead, Texture apple, Texture background)
{
    int totalHeight = MAX_ROWS * (RECT_HEIGHT + 2);
    int totalWidth = MAX_COL * (RECT_WIDTH + 2);

    int startX = (screenWidth - totalWidth) / 2;
    int startY = (screenHeight - totalHeight) / 2;

    int posX;
    int posY;

    int posFruitX;
    int posFruitY;

    bool switchGreen = false;

    BeginDrawing();
    ClearBackground(BLACK);
    DrawTexture(background, 0, 0, WHITELIGHT);
    for (int i = 0; i < MAX_COL; i++)
    {
        for (int j = 0; j < MAX_ROWS; j++)
        {
            posX = startX + i * (RECT_WIDTH + 1);
            posY = startY + j * (RECT_HEIGHT + 1);
            if (switchGreen)
            {
                DrawRectangle(posX, posY, RECT_WIDTH, RECT_HEIGHT, GREENSNAKE);
                switchGreen = false;
            }
            else
            {
                DrawRectangle(posX, posY, RECT_WIDTH, RECT_HEIGHT, GREENSNAKEDARK);
                switchGreen = true;
            }
        }
    }

    Vector2 start = {(float)startX, (float)startY};
    drawSnake(head, start, snakeBody, snakeHead);

    posFruitX = startX + fruit.posX * (RECT_WIDTH + 1);
    posFruitY = startY + fruit.posY * (RECT_HEIGHT + 1);
    DrawTexture(apple, posFruitX, posFruitY, WHITE);

    EndDrawing();
}

void updatePosition(int buttonPressed, SnakeNode *head, GameScene *Scene)
{
    SnakeNode *current = head->next;
    int prevX;
    int prevY;
    int tempX;
    int tempY;
    float tempDegrees;
    float prevDegrees;
    prevX = head->MainSnake.posX;
    prevY = head->MainSnake.posY;
    prevDegrees = head->MainSnake.degrees;

    while (current != NULL)
    {
        tempX = current->MainSnake.posX;
        tempY = current->MainSnake.posY;
        tempDegrees = current->MainSnake.degrees;

        current->MainSnake.posX = prevX;
        current->MainSnake.posY = prevY;
        current->MainSnake.degrees = prevDegrees;

        prevX = tempX;
        prevY = tempY;
        prevDegrees = tempDegrees;

        current = current->next;
    }

    switch (buttonPressed)
    {
    case LEFT:
        head->MainSnake.posX--;
        head->MainSnake.degrees = -90.0f;
        break;
    case RIGHT:
        head->MainSnake.posX++;
        head->MainSnake.degrees = 90.0f;
        break;
    case TOP:
        head->MainSnake.posY--;
        head->MainSnake.degrees = 0.0f;
        break;
    case DOWN:
        head->MainSnake.posY++;
        head->MainSnake.degrees = 180.0f;
        break;
    }
    current = head->next;
    while (current != NULL)
    {
        if (head->MainSnake.posX == current->MainSnake.posX)
        {
            if (head->MainSnake.posY == current->MainSnake.posY)
            {
                // *Scene = GAME_OVER;
                printf("GAME OVER\n");
            }
        }
        current = current->next;
    }

    if (head->MainSnake.posX >= MAX_COL)
    {
        printf("GAME OVER\n");
    }
    if (head->MainSnake.posY >= MAX_ROWS)
    {
        printf("GAME OVER\n");
    }

    if (head->MainSnake.posY <= -1)
    {
        printf("GAME OVER\n");
    }

    if (head->MainSnake.posX <= -1)
    {
        printf("GAME OVER\n");
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

Fruit getFruitRandom(SnakeNode *head)
{
    Fruit fruitTemp;
    SnakeNode *currentNode = head;

    fruitTemp.posX = rand() % MAX_COL;
    fruitTemp.posY = rand() % MAX_ROWS;

    while (currentNode != NULL)
    {
        if (fruitTemp.posX == currentNode->MainSnake.posX)
        {
            if (fruitTemp.posY == currentNode->MainSnake.posY)
            {
                fruitTemp = getFruitRandom(head);
            }
        }
        currentNode = currentNode->next;
    }

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

void drawSnake(SnakeNode *head, Vector2 start, Texture snakeBody, Texture snakeHead)
{
    SnakeNode *currentNode = head;
    int posXSnake;
    int posYSnake;
    Vector2 origin = {(float)snakeBody.width / 2, (float)snakeBody.height / 2};

    if (currentNode != NULL) // Draw the head
    {
        posXSnake = start.x + currentNode->MainSnake.posX * (RECT_WIDTH + 1);
        posYSnake = start.y + currentNode->MainSnake.posY * (RECT_HEIGHT + 1);

        DrawTexturePro(snakeHead, (Rectangle){0, 0, RECT_HEIGHT, RECT_WIDTH}, (Rectangle){(float)posXSnake + 20, (float)posYSnake + 20, RECT_WIDTH, RECT_HEIGHT}, origin, currentNode->MainSnake.degrees, WHITE);
        currentNode = currentNode->next;
    }

    while (currentNode != NULL) // Draw the Body
    {
        posXSnake = start.x + currentNode->MainSnake.posX * (RECT_WIDTH + 1);
        posYSnake = start.y + currentNode->MainSnake.posY * (RECT_HEIGHT + 1);

        DrawTexturePro(snakeBody, (Rectangle){0, 0, RECT_HEIGHT, RECT_WIDTH}, (Rectangle){(float)posXSnake + 20, (float)posYSnake + 20, RECT_WIDTH, RECT_HEIGHT}, origin, currentNode->MainSnake.degrees, WHITE);

        currentNode = currentNode->next;
    }
}
