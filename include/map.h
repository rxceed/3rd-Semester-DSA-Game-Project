#ifndef MAP_H
#define MAP_H


#include "raylib.h"
#include "EntityList.hpp"
#include <vector>
#include "object.h"
#include "camera.h"

class Map
{
    private:
    bool ToggleGrid;

    //Entity
    EntityList entity;

    PlayerCamera camera;


    //Object
    Tile tile;
    std::vector<Tree> tree;

    public:
    Map();
    ~Map();

    void draw();
    void DrawBackgroundTile();
    void DrawGrid();

    void update();

    EntityList GetEntityList();
    PlayerCamera GetCamera();


};





#endif