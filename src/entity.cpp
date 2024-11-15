#include "raylib.h"
#include "Entity.h"

//Entity Class Implementation
Entity::Entity(float health, Vector2 position, float speed, float defense, float attack)
{
    SetHealth(health);
    SetPosition(position);
    SetSpeed(speed);
    SetDefense(defense);
    SetAttack(attack);
}
Entity::~Entity()
{
    
}

void Entity::SetHealth(float val)
{
    health = val;
}
void Entity::SetSpeed(float val)
{
    speed = val;
}
void Entity::SetPosition(Vector2 val)
{
    position = val;
}
void Entity::SetDefense(float val)
{
    defense = val;
}
void Entity::SetAttack(float val)
{
    attack = val;
}

void Entity::Draw()
{
    
}

float Entity::GetHealth()
{
    return health;
}
Vector2 Entity::GetPosition()
{
    return position;
}
float Entity::GetSpeed()
{
    return speed;
}
float Entity::GetDefense()
{
    return defense;
}
float Entity::GetAttack()
{
    return attack;
}

void Entity::MoveUp()
{
    position.y -= speed;
}
void Entity::MoveDown()
{
    position.y += speed;
}
void Entity::MoveRight()
{
    position.x += speed;
}
void Entity::MoveLeft()
{
    position.x -= speed;
}