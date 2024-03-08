#include "raylib.h"
#include <stdio.h>
#include "Snake.h"

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

// void updateGame();
void drawGame();

//***************** USEFUL FUNCTIONS **************
void centerTextYandX(const char *text, int fontSize, int y, int x, Color color);

int main()
{

    InitWindow(screenWidth, screenHeight, "Snake Game");

    SetTargetFPS(60);
    GameScene Scene = PLAY;

    while (!WindowShouldClose())
    {
        switch (Scene)
        {
        case MAIN_MENU:
            // Scene = updateMenu();
            drawMenu();
            break;
        case PLAY:
            // updateGame();
            drawGame();
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

/*void updateGame()
{
}*/
void drawGame()
{
    int totalHeight = MAX_ROWS * (RECT_HEIGHT + 2);
    int totalWidth = MAX_COL * (RECT_WIDTH + 2);

    int startX = (screenWidth - totalWidth) / 2;
    int startY = (screenHeight - totalHeight) / 2;
    BeginDrawing();
    for (int i = 0; i < MAX_COL; i++)
    {
        for (int j = 0; j < MAX_ROWS; j++)
        {
            int posX = startX + i * (RECT_WIDTH + 2);
            int posY = startY + j * (RECT_HEIGHT + 2);

            DrawRectangle(posX, posY, RECT_HEIGHT, RECT_WIDTH, WHITE);
        }
    }
    EndDrawing();
}

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
