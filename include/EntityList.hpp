#ifndef ENTITYLIST_H
#define ENTITYLIST_H

#include "raylib.h"
#include "entity.h"
#include "LinkedList.h"

/*
class EnemyOrcNode:public Node
{
    public:
    Orc entity;
    EnemyOrcNode(Orc entity_);
    ~EnemyOrcNode();
};*/

class EntityList
{
    public:
    Player player;
    LinkedList<Orc> EnemyList_Orc;

    EntityList();
    ~EntityList();
    void ResetAllEntityAnimationTime();
    void draw();

    void SpawnOrc(Vector2 position);
};










#endif