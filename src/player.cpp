#include "raylib.h"
#include "entity.h"

Player::Player(Vector2 position):Entity(health, position, speed, defense, attack)
{
    SetHealth(100);
    SetPosition(position);
    SetSpeed(1);
    SetDefense(10);
    SetAttack(10);
}
Player::~Player()
{

}

void Player::update()
{
    DetectInput();
}
void Player::DetectInput()
{
    if(IsKeyDown(KEY_W))
    {
        MoveUp();
    }
    else if(IsKeyDown(KEY_S))
    {
        MoveDown();
    }
    if(IsKeyDown(KEY_D))
    {
        MoveRight();
    }
    else if(IsKeyDown(KEY_A))
    {
        MoveLeft();
    }
}

void Player::draw()
{
    DrawRectangle(GetPosition().x, GetPosition().y, 50, 50, BLUE);
}