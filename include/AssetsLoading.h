#ifndef ASSETSLOADING_H
#define ASSETSLOADING_H

#include "raylib.h"
#include "entity.h"

struct player_texture
{
    Texture2D idle;
    Texture2D walk;
    Texture2D run;
};

void LoadAssets();

#endif

