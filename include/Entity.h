#ifndef ENTITY_H
#define ENTITY_H

#include "raylib.h"

class Entity
{
protected:
    Vector2 position;
    float health;
    float speed;
    float defense;
    float attack;
public:
    Entity(float health, Vector2 position, float speed, float defense, float attack);
    ~Entity();
    void SetHealth(float value);        //Set healt value
    void SetSpeed(float value);         //Set speed value
    void SetPosition(Vector2 value);    //Set position value
    void SetDefense(float value);
    void SetAttack(float value);
    void draw();

    float GetHealth();
    float GetSpeed();
    Vector2 GetPosition();
    float GetDefense();
    float GetAttack();

    void MoveUp();
    void MoveDown();
    void MoveRight();
    void MoveLeft();
};

class Player:public Entity
{
    public:
    Player(Vector2 position);
    ~Player();
    void update();
    void DetectInput();

    void draw();
};


#endif
