#include "raylib.h"
#include "entity.h"
#include "EntityList.hpp"
#include "LinkedList.h"
#include <iostream>

EntityList::EntityList()
{
    player = Player::Player({400,400});
    EnemyList_Orc = LinkedList<Orc>::LinkedList();
}
EntityList::~EntityList()
{
    
}
void EntityList::draw()
{
    player.draw();
    for(int i = 0; i < EnemyList_Orc.GetSize(); i++)
    {
        EnemyList_Orc.GetNode(i+1)->data.draw();
    }
}

void EntityList::ResetAllEntityAnimationTime()
{
    player.ResetAnimationTime();
    for(int i = 0; i < EnemyList_Orc.GetSize(); i++)
    {
        EnemyList_Orc.GetNode(i+1)->data.ResetAnimationTime();
    }

}

void EntityList::SpawnOrc(Vector2 position)
{
    Node<Orc> *NewSpawn = new Node<Orc>(Orc(position));
    EnemyList_Orc.AppendToHead(NewSpawn);
    std::cout<<"NEW SPAWN POS: "<<EnemyList_Orc.GetNode(EnemyList_Orc.GetSize())->data.GetPosition().x<<std::endl;
    std::cout<<"SPAWNED"<<std::endl;
}
