#include "raylib.h"
#include "entity.h"
#include "AttackList.h"

/*
Melee::Melee()
{

}
Melee::~Melee()
{

}

void Melee::TargetSearch(Entity target)
{
    TargetEntity = &target;
}
bool Melee::IsTargetHit()
{
    if(CheckCollisionRecs(hitbox, TargetEntity->GetHitbox()) && IsActive())
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool Melee::IsActive()
{
    if(active)
    {
        return true;
    }
    else
    {
        return false;
    }    
}
void Melee::StartAttack()
{
    if(!IsActive())
    {
        active = true;
    }
}
void Melee::EndAttack()
{
    if(IsActive)
    {
        active = false;
    }
    AttackTimerCount = 0;
}

void Melee::DebugDraw()
{
    DrawRectangleRec(hitbox, RED);
}

PlayerAttack::PlayerAttack(Player player)
{
    CasterEntity = &player;
    hitbox = {CasterEntity->GetPosition().x, CasterEntity->GetHitbox().y, 80, CasterEntity->GetHitbox().height};
}
PlayerAttack::PlayerAttack()
{

}

void PlayerAttack::update()
{
    if(IsActive())
    {
        AttackTimerCount += GetFrameTime();
        if(AttackTimerCount >= CasterEntity->GetASPD())
        {
            EndAttack();
        }
    }

    if(CasterEntity->GetOrientation() == RIGHT)
    {
        hitbox = {CasterEntity->GetPosition().x, CasterEntity->GetHitbox().y, 80, CasterEntity->GetHitbox().height};
    }
    else if(CasterEntity->GetOrientation() == LEFT)
    {
        hitbox = {CasterEntity->GetPosition().x-hitbox.width, CasterEntity->GetHitbox().y, 80, CasterEntity->GetHitbox().height};
    }
}
*/