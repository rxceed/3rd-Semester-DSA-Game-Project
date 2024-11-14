#ifndef ENTITY_H
#define ENTITY_H

#include "raylib.h"

class Entity
{
private:
    Vector2 position;
    float health;
    float speed;
public:
    Entity();
    ~Entity();
    

};


#endif
