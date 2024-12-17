#include "raylib.h"
#include "entity.h"
#include "GameRule.h"
#include <math.h>
#include <iostream>

Enemy::Enemy(Vector2 position):Entity(health, position, speed, defense, attack, AttackSpeed)
{
    SetPosition(position);
    AnimationTime = 0;
    AnimationKeyframe = 0;

    orientation = RIGHT;
    MovementTarget = position;
    DespawnCounter = 0;
}
Enemy::Enemy():Enemy({0,0})
{

}
Enemy::~Enemy()
{

}
Vector2 Enemy::GetMovementTarget()
{
    return MovementTarget;
}
void Enemy::draw()
{
    if(!IsDespawned())
    {
        //DrawRectangleRec(hitbox, YELLOW);
        DrawTexturePro(texture, TextureFrame, DestFrame, {DestFrame.width/2.0f, DestFrame.height/2.0f}, 0, WHITE);
    }
}
void Enemy::UpdateWander()
{
    if(!wandering && !chasing)
    {

    }
}


Orc::Orc(Vector2 position):Enemy(position)
{
    SetHealth(50);
    SetPosition(position);
    SetSpeed(40);
    SetDefense(5);
    SetAttack(10);
    SetASPD(1.0);
    
    tex_list.idle = LoadTexture("./assets/enemy/orc/Orc-Idle.png");
    tex_list.walk = LoadTexture("./assets/enemy/orc/Orc-Walk.png");
    tex_list.attack1 = LoadTexture("./assets/enemy/orc/Orc-Attack01.png");
    tex_list.attack2 = LoadTexture("./assets/enemy/orc/Orc-Attack02.png");
    tex_list.death = LoadTexture("./assets/enemy/orc/Orc-Death.png");
    
    texture = tex_list.idle;

    DetectionRadiusIdle = {position.x-DetectionRadiusIdle.width/2, position.y-DetectionRadiusIdle.height/2, 50*GRID_SIZE, 50*GRID_SIZE};
    DetectionRadiusChasing = {position.x-DetectionRadiusChasing.width/2, position.y-DetectionRadiusChasing.height/2, 100*GRID_SIZE, 100*GRID_SIZE};
    DetectionRadius = DetectionRadiusIdle;

    TextureFrame = Rectangle({42, 38, 25, 25});
    DestFrame = Rectangle({position.x, position.y, TextureFrame.width*3, TextureFrame.height*3});
    hitbox = Rectangle({DestFrame.x - DestFrame.width/2.0f, DestFrame.y - DestFrame.height/2.0f, DestFrame.width, DestFrame.height});

    MovementTarget= position;

    orientation = RIGHT;

    AnimationActionSet = IDLE;
}
Orc::Orc():Orc({0,0})
{

}
Orc::~Orc()
{

}
void Orc::update()
{
    if(alive)
    {
        if(IsMoving(RIGHT))
        {
            if(orientation != RIGHT)
            {
                orientation = RIGHT;
            }
        }
        else if(IsMoving(LEFT))
        {
            if(orientation != LEFT)
            {
                orientation = LEFT;
            }
        }
        std::cout<<IsMoving(LEFT)<<std::endl;

        //ATTACK RELATED

        if(AttackState)
        {
            AllowMovement = false;
            AttackTime += GetFrameTime();
            if(AttackTime >= GetASPD())
            {
                AttackTime = 0;
                AttackState = false;
                AllowMovement = true;
            }
        }
        if(GetOrientation() == RIGHT)
        {
            MeleeAttackHitbox = {GetPosition().x, GetHitbox().y, 40, GetHitbox().height};
        }
        else if(GetOrientation() == LEFT)
        {
            MeleeAttackHitbox = {GetPosition().x-MeleeAttackHitbox.width, GetHitbox().y, 40, GetHitbox().height};
        }

        UpdateFrame();
        UpdateTexture();

       DestFrame = Rectangle({position.x, position.y, abs(TextureFrame.width*3), abs(TextureFrame.height*3)});
       hitbox = Rectangle({DestFrame.x - DestFrame.width/2.0f, DestFrame.y - DestFrame.height/2.0f, DestFrame.width, DestFrame.height});
       if(health <= 0)
       {
            alive = false;
       }
       std::cout<<speed<<std::endl;
    }
    else
    {
        DespawnCounter += GetFrameTime();
        UpdateFrame();
        UpdateTexture();
        DestFrame = {position.x, position.y, float(fabs(TextureFrame.width*3)), float(fabs(TextureFrame.height*3))};
        hitbox = Rectangle({DestFrame.x - DestFrame.width/2.0f, DestFrame.y - DestFrame.height/2.0f, DestFrame.width, DestFrame.height});
        if(DespawnCounter >= 5.0)
        {
            despawn = true;
        }
    }
    
}
void Orc::UpdateFrame()
{
    float TIME_PER_FRAME;
    float TextureFrameJump;
    switch(AnimationActionSet)
    {
    case IDLE:
        if(orientation == RIGHT)
        {
            TextureFrame.width = 25;
        }
        else
        {
            TextureFrame.width = -25;
        }
        
        TextureFrame.height = 25;
        TextureFrameJump = 100;
        TIME_PER_FRAME = 1.0f/6.0f;

        if(AnimationTime <= TIME_PER_FRAME*1)
        {
            if(AnimationKeyframe != 0)
            {
                TextureFrame.x += TextureFrameJump;
                AnimationKeyframe = 0;
            }
        }
        else if(AnimationTime <= TIME_PER_FRAME*2)
        {
            if(AnimationKeyframe != 1)
            {
                TextureFrame.x += TextureFrameJump;
                AnimationKeyframe = 1;
            }
        }
        else if(AnimationTime <= TIME_PER_FRAME*3)
        {
            if(AnimationKeyframe != 2)
            {
                TextureFrame.x += TextureFrameJump;
                AnimationKeyframe = 2;
            }
        }
        else if(AnimationTime <= TIME_PER_FRAME*4)
        {
            if(AnimationKeyframe != 3)
            {
                TextureFrame.x += TextureFrameJump;
                AnimationKeyframe = 3;
            }
        }
        else if(AnimationTime <= TIME_PER_FRAME*5)
        {
            if(AnimationKeyframe != 4)
            {
                TextureFrame.x += TextureFrameJump;
                AnimationKeyframe = 4;
            }
            
        }
        else if(AnimationTime <= TIME_PER_FRAME*6)
        {
            if(AnimationKeyframe != 5)
            {
                TextureFrame.x = 42;
                AnimationTime = 0;
                AnimationKeyframe = 5;
            }
        }
        AnimationTime += GetFrameTime();
        
        break;
    case WALK:
    if(orientation == RIGHT)
        {
            TextureFrame.width = 25;
        }
        else
        {
            TextureFrame.width = -25;
        }
        
        TextureFrame.height = 25;
        TextureFrameJump = 100;
        TIME_PER_FRAME = 1.0f/8.0f;

        if(AnimationTime <= TIME_PER_FRAME*1)
        {
            if(AnimationKeyframe != 0)
            {
                TextureFrame.x += TextureFrameJump;
                AnimationKeyframe = 0;
            }
        }
        else if(AnimationTime <= TIME_PER_FRAME*2)
        {
            if(AnimationKeyframe != 1)
            {
                TextureFrame.x += TextureFrameJump;
                AnimationKeyframe = 1;
            }
        }
        else if(AnimationTime <= TIME_PER_FRAME*3)
        {
            if(AnimationKeyframe != 2)
            {
                TextureFrame.x += TextureFrameJump;
                AnimationKeyframe = 2;
            }
        }
        else if(AnimationTime <= TIME_PER_FRAME*4)
        {
            if(AnimationKeyframe != 3)
            {
                TextureFrame.x += TextureFrameJump;
                AnimationKeyframe = 3;
            }
        }
        else if(AnimationTime <= TIME_PER_FRAME*5)
        {
            if(AnimationKeyframe != 4)
            {
                TextureFrame.x += TextureFrameJump;
                AnimationKeyframe = 4;
            }
            
        }
        else if(AnimationTime <= TIME_PER_FRAME*6)
        {
            if(AnimationKeyframe != 5)
            {
                TextureFrame.x += TextureFrameJump;

                AnimationKeyframe = 5;
            }
        }
        else if(AnimationTime <= TIME_PER_FRAME*7)
        {
            if(AnimationKeyframe != 6)
            {
                TextureFrame.x += TextureFrameJump;
                AnimationKeyframe = 6;
            }
            
        }
        else if(AnimationTime <= TIME_PER_FRAME*8)
        {
            if(AnimationKeyframe != 7)
            {
                TextureFrame.x = 42;
                AnimationTime = 0;
                AnimationKeyframe = 7;
            }
            
        }
        AnimationTime += GetFrameTime();
        
        break;

    case DEAD:
        if(orientation == RIGHT)
        {
            TextureFrame.width = 30;
        }
        else
        {
            TextureFrame.width = -30;
        }
        
        TextureFrame.height = 25;
        TextureFrameJump = 100;
        TIME_PER_FRAME = 1.0f/4.0f;

        if(AnimationTime <= TIME_PER_FRAME*1)
        {
            if(AnimationKeyframe != 0)
            {
                TextureFrame.x += TextureFrameJump;
                AnimationKeyframe = 0;
            }
        }
        else if(AnimationTime <= TIME_PER_FRAME*2)
        {
            if(AnimationKeyframe != 1)
            {
                TextureFrame.x += TextureFrameJump;
                AnimationKeyframe = 1;
            }
        }
        else if(AnimationTime <= TIME_PER_FRAME*3)
        {
            if(AnimationKeyframe != 2)
            {
                TextureFrame.x += TextureFrameJump;
                AnimationKeyframe = 2;
            }
        }
        else if(AnimationTime <= TIME_PER_FRAME*4)
        {
            if(AnimationKeyframe != 3)
            {
                TextureFrame.x += TextureFrameJump;
                AnimationKeyframe = 3;
            }
        }
        AnimationTime += GetFrameTime();
        
        break;
    case ATTACK1:
        if(orientation == RIGHT)
        {
            TextureFrame.width = 30;
        }
        else
        {
            TextureFrame.width = -30;
        }
        
        TextureFrame.height = 25;
        TextureFrameJump = 100;
        TIME_PER_FRAME = AttackSpeed/6.0f;

        if(AnimationTime <= TIME_PER_FRAME*1)
        {
            if(AnimationKeyframe != 0)
            {
                TextureFrame.x += TextureFrameJump;
                AnimationKeyframe = 0;
            }
        }
        else if(AnimationTime <= TIME_PER_FRAME*2)
        {
            if(AnimationKeyframe != 1)
            {
                TextureFrame.x += TextureFrameJump;
                AnimationKeyframe = 1;
            }
        }
        else if(AnimationTime <= TIME_PER_FRAME*3)
        {
            if(AnimationKeyframe != 2)
            {
                TextureFrame.x += TextureFrameJump;
                AnimationKeyframe = 2;
            }
        }
        else if(AnimationTime <= TIME_PER_FRAME*4)
        {
            if(AnimationKeyframe != 3)
            {
                TextureFrame.x += TextureFrameJump;
                AnimationKeyframe = 3;
            }
        }
        else if(AnimationTime <= TIME_PER_FRAME*5)
        {
            if(AnimationKeyframe != 4)
            {
                TextureFrame.x += TextureFrameJump;
                AnimationKeyframe = 4;
            }
        }
        else if(AnimationTime <= TIME_PER_FRAME*6)
        {
            if(AnimationKeyframe != 5)
            {
                TextureFrame.x = 42;
                AnimationTime = 0;
                AnimationKeyframe = 5;
            }
        }
        AnimationTime += GetFrameTime();
        
    default:
        break;
    }

}

void Orc::UpdateTexture()
{
    if(!IsMoving(GENERAL) && IsAlive() && !AttackState)
    {
        if(AnimationActionSet != IDLE)
        {
            AnimationActionSet = IDLE;
            texture = tex_list.idle;
            if(AnimationTime >= 0)
            {
                AnimationTime = 0;
                AnimationKeyframe = 0;
            }
        }
    }
    else if(IsMoving(GENERAL) && IsAlive() && !AttackState)
    {
        if(AnimationActionSet != WALK)
        {
            AnimationActionSet = WALK;
            texture = tex_list.walk;
            if(AnimationTime >= 0)
            {
                AnimationTime = 0;
                AnimationKeyframe = 0;
            }
        }
    }
    else if(!IsAlive())
    {
        if(AnimationActionSet != DEAD)
        {
            AnimationActionSet = DEAD;
            texture = tex_list.death;
            TextureFrame.x = 36;
            if(AnimationTime >= 0)
            {
                AnimationTime = 0;
                AnimationKeyframe = 0;
                
            }
        }
    }
    else if(AttackState)
    {
        if(AnimationActionSet != ATTACK1)
        {
            AnimationActionSet = ATTACK1;
            texture = tex_list.attack1;
            TextureFrame.x = 42;
            if(AnimationTime >= 0)
            {
                AnimationTime = 0;
                AnimationKeyframe = 0;
                
            }
        }
    }
}
void Orc::UpdateMelee(Entity &target)
{
    if(AttackState && IsAlive())
    {
        if(!target.HasMeleeBeenHit() && CheckCollisionRecs(MeleeAttackHitbox, target.GetHitbox()) && target.IsAlive())
        {
            target.TakeDamage(GetAttack());
            target.SetHasMeleeBeenHit(true);
            if(GetOrientation() == RIGHT)
            {
                target.SetPosition({target.GetPosition().x+20, target.GetPosition().y});
            }
            else
            {
                target.SetPosition({target.GetPosition().x-20, target.GetPosition().y});
            }
            
            
            //std::cout<<target.GetPosition().x<<std::endl;
        }
    }
    else
    {
        target.SetHasMeleeBeenHit(false);
    }
}
void Orc::DetectPlayer(Player *player)
{
    if(CheckCollisionRecs(player->GetHitbox(), DetectionRadius))
    {
        DetectionRadius = DetectionRadiusChasing;
        MovementTarget = player->GetPosition();
    }
}