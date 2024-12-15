#ifndef OBJECT_H
#define OBJECT_H

#include "raylib.h"
#include "EntityList.hpp"

class Object
{
    protected:
    struct TextureList
    {
        Texture2D TilesetTexture;
    };
    
    TextureList tex_list;

    Texture2D texture;
    Rectangle TextureFrame;
    Rectangle DestFrame;
    Rectangle hitbox;

    Vector2 position;

    public:
    Object(Vector2 _postiion);
    Object();
    ~Object();

    Vector2 GetPosition();

    void SetPosition(Vector2 _position);
    void draw();

};

class Tile:public Object
{
    private:

    public:
    Tile(Vector2 _position);
    Tile();
    ~Tile();

    void DrawTile();
};

class Tree:public Object
{
    private:
    //Rectangle hitbox;
    public:
    Tree(Vector2 _position);
    Tree();
    ~Tree();
    void collision(EntityList &entity);
};

#endif