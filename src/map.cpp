#include "raylib.h"
#include "map.h"
#include "object.h"
#include "EntityList.hpp"
#include "GameRule.h"
#include "settings.h"
#include "camera.h"
#include <iostream>

Map::Map()
{
    camera = PlayerCamera::PlayerCamera(entity.player);
    for(int i = 0; i < 1000; i++)
    { 
        //srand(i);
        //std::cout<<(rand()-RAND_MAX/2)%10000<<std::endl;
        tree.push_back(Tree(Vector2{float((rand()-RAND_MAX/2)%10000), float((rand()-RAND_MAX/2)%10000)}));
        //std::cout<<(rand()-RAND_MAX/2)%10000<<std::endl;
        
    }
}
Map::~Map()
{

}
void Map::DrawBackgroundTile()
{
    tile.DrawTile();
}
void Map::draw()
{
    for(float posY = GetScreenToWorld2D({0,0}, camera.GetCamera()).y; posY <= GetScreenToWorld2D({0,WINDOW_HEIGHT}, camera.GetCamera()).y; posY++)
    {
        //Entity
        //Player
        if(entity.player.GetPosition().y >= posY-0.5 && entity.player.GetPosition().y <= posY+0.5)
        {
            entity.player.draw();
        }
        //Orc
        for(int i = 0; i < entity.EnemyList_Orc.GetSize(); i++)
        {
            if(entity.EnemyList_Orc.GetNode(i+1)->data.GetPosition().y >= posY-0.5 && entity.EnemyList_Orc.GetNode(i+1)->data.GetPosition().y <= posY+0.5)
            {
                entity.EnemyList_Orc.GetNode(i+1)->data.draw();
            }
        }

        //Object
        //Tree
        for(int i = 0; i < 1000; i++)
        {
            if(tree[i].GetPosition().y >= posY-0.5 && tree[i].GetPosition().y <= posY+0.5)
            {
                tree[i].draw();
            }
        }
    }
}
void Map::DrawGrid()
{
    for(int i = 0; i < WINDOW_WIDTH; i++)
    {
        DrawLine(i*GRID_SIZE, 0, i*GRID_SIZE, WINDOW_HEIGHT, BLACK);
    }
    for(int i = 0; i < WINDOW_HEIGHT; i++)
    {
        DrawLine(0, i*GRID_SIZE, WINDOW_WIDTH, i*GRID_SIZE, BLACK);
    }
}
void Map::update()
{
    entity.player.update();
    
    for(int i = 0; i < entity.EnemyList_Orc.GetSize(); i++)
    {
        entity.EnemyList_Orc.GetNode(i+1)->data.update();
    }  
    //Tree collision
    for(int i = 0; i < 1000; i++)
    { 
        tree[i].collision(entity);
    }
    camera.update();
}

EntityList Map::GetEntityList()
{
    return entity;
}
PlayerCamera Map::GetCamera()
{
    return camera;
}