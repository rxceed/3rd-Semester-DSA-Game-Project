#include <iostream>
#include "settings.h"
#include "raylib.h"
#include "entity.h"
#include "camera.h"
#include "map.h"


#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

using namespace std;

int main()
{
    SetTargetFPS(MAX_FPS);
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "test");

    int WndowReadyCount = 0;

    Map map;
    EntityList *entity = &map.GetEntityList();

    PlayerCamera *camera = &map.GetCamera();
    while(!WindowShouldClose())
    {

        //Update related
        map.update();
        camera->update();

        //Drawing related
        BeginDrawing();
        
        ClearBackground(WHITE);
        

        BeginMode2D(camera->GetCamera());
        map.DrawBackgroundTile();
        map.draw();
        //entity->draw();

        EndMode2D();

        //map.DrawGrid();
        EndDrawing();

        //
        if(WndowReadyCount <= 5)
        {
            WndowReadyCount++;
            entity->ResetAllEntityAnimationTime();
            continue;
        }
    }
}