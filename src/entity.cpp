#include "raylib.h"
#include "entity.h"

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

void Entity::draw()
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

void Entity::RecordPosition()
{
    PreviousPosition = position;
}

void Entity::DetectMovement()
{
    if(position.y < PreviousPosition.y)
    {
        MovingUp = true;
    }
    else if(position.y > PreviousPosition.y)
    {
        MovingDown = true;
    }
    else
    {
        MovingUp = false;
        MovingDown = false;
    }

    if(position.x > PreviousPosition.x)
    {
        MovingRight = true;
    }
    else if(position.x < PreviousPosition.x)
    {
        MovingLeft = true;
    }
    else
    {
        MovingRight = false;
        MovingLeft = false;
    }
}

bool Entity::IsMoving(int direction)
{
    switch(direction)
    {
    case GENERAL:
        if(MovingUp || MovingDown || MovingRight || MovingLeft)
        {
            return true;
        }
        else
        {
            return false;
        }
        break;
    
    case UP:
        if(MovingUp)
        {
            return true;
        }
        else
        {
            return false;
        }
        break;    

    case DOWN:
        if(MovingDown)
        {
            return true;
        }
        else
        {
            return false;
        }
        break;

    case RIGHT:
        if(MovingRight)
        {
            return true;
        }
        else
        {
            return false;
        }
        break;

    case LEFT:
        if(MovingLeft)
        {
            return true;
        }
        else
        {
            return false;
        }
        break;
    default:
        break;
    }
}