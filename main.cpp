#include <iostream>
#include "raylib.h"

int main(int, char**){
    InitWindow(800, 800, "test");
    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        EndDrawing();
    }
}