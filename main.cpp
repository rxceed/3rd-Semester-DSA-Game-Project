#include <iostream>
#include "raylib.h"
#include "Entity.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

using namespace std;

int main(int, char**){
    InitWindow(800, 800, "test");
    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        
    }
}