#include "raylib.h"
#include "object.h"
#include "map.h"
#include "EntityList.hpp"
#include <iostream>
#include "settings.h"
#include "GameRule.h"

Object::Object(Vector2 _position)
{
    position = _position;
    tex_list.TilesetTexture = LoadTexture("./assets/object/tileset/Overworld_Tileset.png");
}
Object::Object()
{
    tex_list.TilesetTexture = LoadTexture("./assets/object/tileset/Overworld_Tileset.png");
}
Object::~Object()
{

}
Vector2 Object::GetPosition()
{
    return position;
}
void Object::SetPosition(Vector2 _position)
{
    position = _position;
}
void Object::draw()
{
    //DrawRectangleRec(hitbox, WHITE);
    DrawTexturePro(texture, TextureFrame, DestFrame, {DestFrame.width/2.0f, DestFrame.height/2.0f}, 0, WHITE);
    
}
Rectangle Object::GetHitbox()
{
    return hitbox;
}


Tile::Tile(Vector2 _position):Object(_position)
{
    position = _position;
    texture = tex_list.TilesetTexture;
    TextureFrame = {162, 68, 13, 13};
    DestFrame = {position.x, position.y, TextureFrame.width*4, TextureFrame.height*4};
}
Tile::Tile():Object()
{
    texture = tex_list.TilesetTexture;
    TextureFrame = {162, 68, 13, 12};
    DestFrame = {position.x, position.y, TextureFrame.width*4, TextureFrame.height*4};
}
Tile::~Tile()
{
    //UnloadTexture(texture);
}
void Tile::DrawTile()
{
    int posY = -WORLD_SIZE;
    int posX = -WORLD_SIZE;
    for(int j = 0; posX <= WORLD_SIZE; j++)
    {
        for(int i = 0; posY <= WORLD_SIZE; i++)
        {
            DrawTexturePro(texture, TextureFrame, {float(posX), float(posY), DestFrame.width, DestFrame.height}, {DestFrame.width/2.0f, DestFrame.height/2.0f}, 0, WHITE);
            posY += int(DestFrame.height);
        }
        //DrawTexturePro(texture, TextureFrame, {float(posX), float(posY), DestFrame.width, DestFrame.height}, {DestFrame.width/2.0f, DestFrame.height/2.0f}, 0, WHITE);
        posX += int(DestFrame.width);
        posY = -WORLD_SIZE;
    }
}

Tree::Tree(Vector2 _position):Object(_position)
{
    position = _position;
    texture = tex_list.TilesetTexture;
    TextureFrame = {47, 145, 34, 43};
    DestFrame = {position.x, position.y, TextureFrame.width*4, TextureFrame.height*4};
    hitbox = {DestFrame.x - hitbox.width/2.0f, DestFrame.y - hitbox.height/2.0f + 20, DestFrame.width-60, DestFrame.height-100};
}
Tree::Tree():Object()
{
    texture = tex_list.TilesetTexture;
    TextureFrame = {47, 145, 34, 43};
    DestFrame = {position.x, position.y, TextureFrame.width*4, TextureFrame.height*4};
    hitbox = {DestFrame.x - hitbox.width/2.0f, DestFrame.y - hitbox.height/2.0f + 20, DestFrame.width-60, DestFrame.height-100};
}
Tree::~Tree()
{
    //UnloadTexture(texture);
}
void Tree::collision(EntityList &entity)
{

    if(CheckCollisionRecs(hitbox, entity.player.GetHitbox()) && entity.player.IsAlive())
    {
        std::cout<<"collision"<<std::endl;
        if(entity.player.GetPosition().x < hitbox.x && entity.player.GetPosition().y > hitbox.y && entity.player.GetPosition().y < hitbox.y+hitbox.height)
        {
            entity.player.Displace({0-entity.player.GetSpeed(), 0});
        }
        else if(entity.player.GetPosition().x > hitbox.x+hitbox.width && entity.player.GetPosition().y > hitbox.y && entity.player.GetPosition().y < hitbox.y+hitbox.height)
        {
            entity.player.Displace({entity.player.GetSpeed(), 0});
        }
        if(entity.player.GetPosition().y < hitbox.y && entity.player.GetPosition().x < hitbox.x+hitbox.width && entity.player.GetPosition().x > hitbox.x)
        {
            entity.player.Displace({0, 0-entity.player.GetSpeed()});
        }
        else if(entity.player.GetPosition().y > hitbox.y+hitbox.height && entity.player.GetPosition().x < hitbox.x+hitbox.width && entity.player.GetPosition().x > hitbox.x)
        {
            entity.player.Displace({0, entity.player.GetSpeed()});
        }
    }
    
}