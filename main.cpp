#include <iostream>
#include "settings.h"
#include "raylib.h"
#include "entity.h"
#include "camera.h"
#include "map.h"

using namespace std;

int main()
{
    SetTargetFPS(MAX_FPS);
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "test");
    ToggleFullscreen();
    bool IsGameOver = false;

    int WndowReadyCount = 0;

    Map *map = new Map;
    EntityList *entity = &map->GetEntityList();

    PlayerCamera *camera = &map->GetCamera();
    while(!WindowShouldClose())
    {
        //Update related
        map->update();
        entity = &map->GetEntityList();
        camera->update();
        IsGameOver = !map->GetPlayerState();

        //Drawing related
        BeginDrawing();
        
        ClearBackground(WHITE);
        

        BeginMode2D(camera->GetCamera());
        map->DrawBackgroundTile();
        map->draw();
        //entity->draw();

        EndMode2D();

        if(IsGameOver)
        {
            DrawText("GAME OVER", WINDOW_WIDTH/2.0-MeasureText("GAME OVER", 20), WINDOW_HEIGHT/2.0, 50, RED);
            DrawText("PRESS R TO RETRY", WINDOW_WIDTH/2.0-MeasureText("GAME OVER", 20), WINDOW_HEIGHT/2.0+60, 20, RED);
        }
        DrawText(TextFormat("%.2f/500", entity->player.GetHealth()), 50, 30, 30, RED);
        EndDrawing();

        //
        if(WndowReadyCount <= 5)
        {
            WndowReadyCount++;
            entity->ResetAllEntityAnimationTime();
            continue;
        }
        //Reset Stage
        if(IsGameOver && IsKeyPressed(KEY_R))
        {
            map->ResetMap();
            IsGameOver = false;
        }
    }
}
