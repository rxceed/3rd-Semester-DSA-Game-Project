#include "raylib.h"
#include "map.h"
#include "object.h"
#include "EntityList.hpp"
#include "GameRule.h"
#include "settings.h"
#include "camera.h"
#include "AttackList.h"
#include <iostream>

Map::Map()
{
    camera = PlayerCamera::PlayerCamera(entity.player);
    for(int i = 0; i < 1000; i++)
    { 
        tree.push_back(Tree(Vector2{float((rand()-RAND_MAX/2)%5000), float((rand()-RAND_MAX/2)%5000)}));
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
    //DrawText("GAME OVER", GetScreenToWorld2D({WINDOW_WIDTH/2, 0}, camera.GetCamera()).x-TextLength("GAME OVER")/2.0f, GetScreenToWorld2D({0, WINDOW_HEIGHT/2}, camera.GetCamera()).x, 50, RED);
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
    
    if(rand()%25 == 5)
    {
        entity.SpawnOrc({float((rand()-RAND_MAX/2)%2000), float((rand()-RAND_MAX/2)%2000)});
    }
    
    //Tree collision
    for(int i = 0; i < 1000; i++)
    { 
        tree[i].collision(entity);
    }
    camera.update();

    //Attack related
    //Plyer attack
    if(entity.player.GetAttackState())
    {
        for(int i = 0; i < entity.EnemyList_Orc.GetSize(); i++)
        {
            entity.player.UpdateMelee(entity.EnemyList_Orc.GetNode(i+1)->data);
        }
    }
    else
    {
        for(int i = 0; i < entity.EnemyList_Orc.GetSize(); i++)
        {
            entity.EnemyList_Orc.GetNode(i+1)->data.SetHasMeleeBeenHit(false);
        }
    }
    
    //Enemy Movement
    for(int i = 0; i < entity.EnemyList_Orc.GetSize(); i++)
    {
        entity.EnemyList_Orc.GetNode(i+1)->data.RecordPosition();
    }
    for(int i = 0; i < entity.EnemyList_Orc.GetSize(); i++)
    {
        if(entity.EnemyList_Orc.GetNode(i+1)->data.IsAlive())
        {
            if(entity.EnemyList_Orc.GetNode(i+1)->data.GetPosition().x < entity.player.GetPosition().x-30)
            {
                entity.EnemyList_Orc.GetNode(i+1)->data.MoveRight();
            }
            else if(entity.EnemyList_Orc.GetNode(i+1)->data.GetPosition().x > entity.player.GetPosition().x+30)
            {
                entity.EnemyList_Orc.GetNode(i+1)->data.MoveLeft();
            }
            if(entity.EnemyList_Orc.GetNode(i+1)->data.GetPosition().y < entity.player.GetPosition().y-30)
            {
                entity.EnemyList_Orc.GetNode(i+1)->data.MoveDown();
            }
            else if(entity.EnemyList_Orc.GetNode(i+1)->data.GetPosition().y > entity.player.GetPosition().y+30)
            {
                entity.EnemyList_Orc.GetNode(i+1)->data.MoveUp();
            }
        }
    }
    //enemyupdate
    for(int i = 0; i < entity.EnemyList_Orc.GetSize(); i++)
    {
        entity.EnemyList_Orc.GetNode(i+1)->data.DetectMovement();
        entity.EnemyList_Orc.GetNode(i+1)->data.update();
    }
    
    for(int i = 0; i < entity.EnemyList_Orc.GetSize(); i++)
    {
        if(CheckCollisionRecs(entity.EnemyList_Orc.GetNode(i+1)->data.GetHitbox(), entity.player.GetHitbox()))
        {
            entity.EnemyList_Orc.GetNode(i+1)->data.SetAttackState(true);
        }
    }

    for(int i = 0; i < entity.EnemyList_Orc.GetSize(); i++)
    {
        if(entity.EnemyList_Orc.GetNode(i+1)->data.GetAttackState())
        {
            entity.EnemyList_Orc.GetNode(i+1)->data.UpdateMelee(entity.player);
        }
        else
        {
            entity.player.SetHasMeleeBeenHit(false);
        }
    }

    if(entity.player.GetAttackState())
    {
        for(int i = 0; i < entity.EnemyList_Orc.GetSize(); i++)
        {
            entity.player.UpdateMelee(entity.EnemyList_Orc.GetNode(i+1)->data);
        }
    }
    else
    {
        for(int i = 0; i < entity.EnemyList_Orc.GetSize(); i++)
        {
            entity.EnemyList_Orc.GetNode(i+1)->data.SetHasMeleeBeenHit(false);
        }
    }

    //Deletion
    for(int i = 0; i < entity.EnemyList_Orc.GetSize(); i++)
    {
        if(entity.EnemyList_Orc.GetNode(i+1)->data.IsDespawned())
        {
            entity.EnemyList_Orc.Delete(i+1);
            break;
        }
    }
    
}

EntityList Map::GetEntityList()
{
    return entity;
}
PlayerCamera Map::GetCamera()
{
    return camera;
}

bool Map::GetPlayerState()
{
    if(entity.player.IsAlive())
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Map::ResetMap()
{
    entity = EntityList::EntityList();
    camera = PlayerCamera::PlayerCamera(entity.player);
}