#include "raylib.h"
#include "entity.h"

//Entity Class Implementation
Entity::Entity(float health, Vector2 position, float speed, float defense, float attack, float AttackSpeed)
{
    SetHealth(health);
    SetPosition(position);
    SetSpeed(speed);
    SetDefense(defense);
    SetAttack(attack);
    SetASPD(AttackSpeed);
    PreviousPosition = position;

    MeleeHasBeenHit = false;
}
Entity::Entity()
{

    
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
void Entity::SetASPD(float val)
{
    AttackSpeed = val;
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
float Entity::GetASPD()
{
    return AttackSpeed;
}
bool Entity::IsAlive()
{
    return alive;
}
bool Entity::IsDespawned()
{
    return despawn;
}
void Entity::MoveUp()
{
    position.y -= speed*GetFrameTime();
}
void Entity::MoveDown()
{
    position.y += speed*GetFrameTime();
}
void Entity::MoveRight()
{
    position.x += speed*GetFrameTime();
}
void Entity::MoveLeft()
{
    position.x -= speed*GetFrameTime();
}
void Entity::Displace(Vector2 value)
{
    position.x += value.x*GetFrameTime();
    position.y += value.y*GetFrameTime();
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
        MovingDown = false;
    }
    else if(position.y > PreviousPosition.y)
    {
        MovingUp = false;
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
        MovingLeft = false;
    }
    else if(position.x < PreviousPosition.x)
    {
        MovingRight = false;
        MovingLeft = true;
    }
    else
    {
        MovingRight = false;
        MovingLeft = false;
    }
}
int Entity::GetOrientation()
{
    return orientation;
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
        return false;
        break;
    }
}
bool Entity::IsRunStateTrue()
{
    return RunState;
}
bool Entity::GetAttackState()
{
    return AttackState;
}
void Entity::SetAttackState(bool var)
{
    if(var)
    {
        AttackState = true;
    }
    else
    {
        
        AttackState = false;
    }
    
}
bool Entity::HasAttackUpdateRan()
{
    return AttackUpdateRun;
}
void Entity::SetAttackUpdateRun(bool var)
{
    if(var)
    {
        AttackUpdateRun = true;
    }
    else
    {
        AttackUpdateRun = false;
    }
    
}
bool Entity::HasMeleeBeenHit()
{
    return MeleeHasBeenHit;
}
void Entity::SetHasMeleeBeenHit(bool var)
{
    if(var)
    {
        MeleeHasBeenHit = true;
    }
    else
    {
        MeleeHasBeenHit = false;
    }
    
}

Rectangle Entity::GetHitbox()
{
    return hitbox;
}

void Entity::TakeDamage(float damage)
{
    float HealthAfterDamage = GetHealth() - damage*(150/(150+defense));
    SetHealth(HealthAfterDamage);
}

void Entity::ResetAnimationTime()
{
    AnimationTime = 0;
}