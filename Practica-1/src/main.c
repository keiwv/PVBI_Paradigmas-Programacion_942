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

#define BLACKOPACITY \
    CLITERAL(Color) { 0, 0, 0, 50 }

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
    GAME_OVER,
    LEAVE,
} GameScene;

//***************** SCENES FUNCTIONS **************
GameScene updateMenu(bool *isMouseOnTextJugar, bool *isMouseOnTextSalir);
void drawMenu(bool *isMouseOnTextJugar, bool *isMouseOnTextSalir, Texture background);

void updateGame(SnakeNode *head, Fruit *fruit);
void drawGame(SnakeNode *head, Fruit fruit, float deltaTime, Texture snakeBody, Texture snakeHead, Texture apple, Texture background);

//***************** USEFUL FUNCTIONS **************
void centerTextYandX(const char *text, int fontSize, int y, int x, Color color);
Fruit getFruitRandom(SnakeNode *head);
void updatePosition(int buttonPressed, SnakeNode *head, GameScene *Scene);
void updateDirection(int *buttonPressed);
void drawSnake(SnakeNode *head, Vector2 start, Texture snakeBody, Texture snakeHead);
bool verifyTextPosition(const char *text, int fontSize, int x, int y);

int main()
{

    srand(time(NULL));
    InitWindow(screenWidth, screenHeight, "Snake Game");

    GameScene Scene = MAIN_MENU;
    SnakeNode *head = initializeSnake((int)MAX_COL / 2, (int)MAX_ROWS / 2);
    Fruit fruit = getFruitRandom(head);

    int buttonPressed = STOP;
    float deltaTime;
    float elapsedTime = 0.0f;
    bool isMouseOnTextJugar = false;
    bool isMouseOnTextSalir = false;
    bool closeGame = false;
    SetTargetFPS(165);

    Texture apple = LoadTexture("assets/textures/FoodApple.png");
    Texture snakeBody = LoadTexture("assets/textures/SnakeBody.png");
    Texture snakeHead = LoadTexture("assets/textures/SnakeHead.png");
    Texture background = LoadTexture("assets/background/pxfuel.png");

    apple.height = RECT_HEIGHT;
    apple.width = RECT_WIDTH;

    snakeBody.height = RECT_HEIGHT + 10;
    snakeBody.width = RECT_WIDTH + 10;

    snakeHead.height = RECT_HEIGHT + 10;
    snakeHead.width = RECT_WIDTH + 10;

    while (!WindowShouldClose() && !closeGame)
    {
        deltaTime = GetFrameTime();
        elapsedTime += deltaTime;
        if (IsKeyPressed(KEY_O))
        {
            ToggleFullscreen();
        }

        switch (Scene)
        {
        case MAIN_MENU:
            Scene = updateMenu(&isMouseOnTextJugar, &isMouseOnTextSalir);
            drawMenu(&isMouseOnTextJugar, &isMouseOnTextSalir, background);
            break;
        case PLAY:
            updateDirection(&buttonPressed);

            if (elapsedTime >= 1.0f / SNAKE_SPEED) // Modify snake speed
            {
                updatePosition(buttonPressed, head, &Scene);
                elapsedTime = 0.0f;
            }

            updateGame(head, &fruit);
            drawGame(head, fruit, deltaTime, snakeBody, snakeHead, apple, background);

            break;
        case GAME_OVER:
            BeginDrawing();
            DrawTexture(background, 0, 0, WHITELIGHT);
            centerTextYandX("HAS PERDIDO", 70, -95, 0, DARKPURPLE);
            centerTextYandX("HAS PERDIDO", 70, -100, 0, WHITE);
            centerTextYandX("Presione ENTER para volver al menu", 40, 3, 0, DARKGREEN);
            centerTextYandX("Presione ENTER para volver al menu", 40, 0, 0, GREEN);
            EndDrawing();

            if (IsKeyPressed(KEY_ENTER))
            {
                deleteSnake(head);
                head = initializeSnake((int)MAX_COL / 2, (int)MAX_ROWS / 2);
                buttonPressed = STOP;
                Scene = MAIN_MENU;
            }

            break;
        case LEAVE:
            closeGame = true;
            break;
        default:
            break;
        }
    }

    deleteSnake(head);
    UnloadTexture(apple);
    UnloadTexture(snakeBody);
    UnloadTexture(snakeHead);
    CloseWindow();
    return 0;
}

GameScene updateMenu(bool *isMouseOnTextJugar, bool *isMouseOnTextSalir)
{

    if (verifyTextPosition("JUGAR", 60, 0, 0))
    {
        *isMouseOnTextJugar = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            return PLAY;
        }
    }
    else
    {
        *isMouseOnTextJugar = false;
    }

    if (verifyTextPosition("SALIR", 30, 0, 50))
    {
        *isMouseOnTextSalir = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            return LEAVE;
        }
    }
    else
    {
        *isMouseOnTextSalir = false;
    }

    return MAIN_MENU;
}

void drawMenu(bool *isMouseOnTextJugar, bool *isMouseOnTextSalir, Texture background)
{
    BeginDrawing();

    DrawTexture(background, 0, 0, WHITELIGHT);

    centerTextYandX("SNAKE GAME", 100, -85, 0, DARKPURPLE);
    centerTextYandX("SNAKE GAME", 100, -90, 0, PURPLE);

    centerTextYandX("JUGAR", 60, 5, 0, GRAY);
    centerTextYandX("SALIR", 30, 53, 0, GRAY);

    if (*isMouseOnTextJugar)
    {
        centerTextYandX("JUGAR", 60, 0, 0, YELLOW);
    }
    else
    {

        centerTextYandX("JUGAR", 60, 0, 0, WHITE);
    }

    if (*isMouseOnTextSalir)
    {
        centerTextYandX("SALIR", 30, 50, 0, YELLOW);
    }
    else
    {

        centerTextYandX("SALIR", 30, 50, 0, WHITE);
    }

    EndDrawing();
}

void updateGame(SnakeNode *head, Fruit *fruit)
{
    Vector2 fruitPosition = {(float)fruit->posX, (float)fruit->posY}; /* Add node if the snake head position is in fruit position*/
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

    // Draw background
    BeginDrawing();
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

    //Draw Text
    centerTextYandX("SNAKE GAME", 100, -397, 0, DARKPURPLE);
    centerTextYandX("SNAKE GAME", 100, -400, 0, PURPLE);

    // Draw Snake
    Vector2 start = {(float)startX, (float)startY};
    drawSnake(head, start, snakeBody, snakeHead);

    // Draw fruit
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

    // Copy position from the head to each part of the body
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

    // Move snake depending what button was pressed.
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

    // Verify Collision
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

    // Verify collision with walls
    if (head->MainSnake.posX >= MAX_COL)
    {
        *Scene = GAME_OVER;
    }
    if (head->MainSnake.posY >= MAX_ROWS)
    {
        *Scene = GAME_OVER;
    }

    if (head->MainSnake.posY <= -1)
    {
        *Scene = GAME_OVER;
    }

    if (head->MainSnake.posX <= -1)
    {
        *Scene = GAME_OVER;
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
    Vector2 origin = {(float)snakeBody.width / 2, (float)snakeBody.height / 2}; // WARNING: Assuming snakebody (width and height) are int.

    if (currentNode != NULL) // Draw the head
    {
        posXSnake = start.x + currentNode->MainSnake.posX * (RECT_WIDTH + 1);
        posYSnake = start.y + currentNode->MainSnake.posY * (RECT_HEIGHT + 1);

        DrawTexturePro(snakeHead, (Rectangle){0, 0, RECT_HEIGHT, RECT_WIDTH}, (Rectangle){(float)posXSnake + 20, (float)posYSnake + 20, RECT_WIDTH, RECT_HEIGHT}, origin, currentNode->MainSnake.degrees, WHITE);
        currentNode = currentNode->next;
    }

    while (currentNode != NULL) // Draw the body
    {
        posXSnake = start.x + currentNode->MainSnake.posX * (RECT_WIDTH + 1);
        posYSnake = start.y + currentNode->MainSnake.posY * (RECT_HEIGHT + 1);

        DrawTexturePro(snakeBody, (Rectangle){0, 0, RECT_HEIGHT, RECT_WIDTH}, (Rectangle){(float)posXSnake + 20, (float)posYSnake + 20, RECT_WIDTH, RECT_HEIGHT}, origin, currentNode->MainSnake.degrees, WHITE);

        currentNode = currentNode->next;
    }
}

bool verifyTextPosition(const char *text, int fontSize, int x, int y)
{
    Vector2 mousePosition = GetMousePosition();

    int textWidth;
    int PosX;
    int PosY;

    textWidth = MeasureText(text, fontSize);
    PosX = ((screenWidth - textWidth) / 2) + x;
    PosY = ((screenHeight - fontSize) / 2) + y;

    bool isMouseInside = (mousePosition.x >= PosX) &&
                         (mousePosition.x <= PosX + textWidth) &&
                         (mousePosition.y >= PosY) &&
                         (mousePosition.y <= PosY + fontSize);

    return isMouseInside;
}
