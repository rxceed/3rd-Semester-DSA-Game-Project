#include <iostream>
#include "raylib.h"
#include "entity.h"
#include "camera.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

using namespace std;

int main()
{
    InitWindow(800, 800, "test");
    Player player({400, 400});
    PlayerCamera camera(player);
    while(!WindowShouldClose())
    {
        player.update();
        camera.update();
        BeginDrawing();
        ClearBackground(WHITE);
        BeginMode2D(camera.GetCamera());
        player.draw();
        EndMode2D();

        EndDrawing();
    }
}