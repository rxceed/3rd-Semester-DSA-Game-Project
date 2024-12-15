#ifndef ATTACKLIST_H
#define ATTACKLIST_H

#include "raylib.h"
#include "entity.h"

class Melee
{
    protected:
    Entity *TargetEntity;
    Entity *CasterEntity;
    Rectangle hitbox;

    bool active = false;
    bool *HasHitTarget = false;

    float AttackTimerCount = 0;

    public:
    Melee();
    ~Melee();
    void TargetSearch(Entity target);
    bool IsTargetHit();
    bool IsActive();
    void StartAttack();
    void EndAttack();

    void DebugDraw();
};

class PlayerAttack:public Melee
{
    public:
    PlayerAttack(Player player);
    PlayerAttack();
    ~PlayerAttack();
    void update();
};






#endif