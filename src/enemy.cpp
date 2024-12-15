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
}
Enemy::Enemy():Enemy({0,0})
{

}
Enemy::~Enemy()
{

}
void Enemy::draw()
{
    DrawTexturePro(texture, TextureFrame, DestFrame, {DestFrame.width/2.0f, DestFrame.height/2.0f}, 0, WHITE);
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
    SetSpeed(50);
    SetDefense(5);
    SetAttack(5);
    
    tex_list.idle = LoadTexture("./assets/enemy/orc/Orc-Idle.png");
    tex_list.walk = LoadTexture("./assets/enemy/orc/Orc-Walk.png");
    tex_list.attack1 = LoadTexture("./assets/enemy/orc/Orc-Attack01.png");
    tex_list.attack2 = LoadTexture("./assets/enemy/orc/Orc-Attack02.png");
    
    texture = tex_list.idle;

    DetectionRadiusIdle = {position.x-DetectionRadiusIdle.width/2, position.y-DetectionRadiusIdle.height/2, 50*GRID_SIZE, 50*GRID_SIZE};
    DetectionRadiusChasing = {position.x-DetectionRadiusChasing.width/2, position.y-DetectionRadiusChasing.height/2, 100*GRID_SIZE, 100*GRID_SIZE};

    TextureFrame = Rectangle({42, 38, 25, 25});
    DestFrame = Rectangle({position.x, position.y, TextureFrame.width*3, TextureFrame.height*3});
    hitbox = Rectangle({DestFrame.x - DestFrame.width/2.0f, DestFrame.y - DestFrame.height/2.0f, DestFrame.width, DestFrame.height});

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
    RecordPosition();
    DetectMovement();

    UpdateWander();
    
    UpdateTexture();
    
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

    UpdateFrame();
    UpdateTexture();

    DestFrame = {position.x, position.y, float(fabs(TextureFrame.width*3)), float(fabs(TextureFrame.height*3))};
    hitbox = Rectangle({DestFrame.x - DestFrame.width/2.0f, DestFrame.y - DestFrame.height/2.0f, DestFrame.width, DestFrame.height});
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
    
    default:
        break;
    }

}

void Orc::UpdateTexture()
{
    if(!IsMoving(GENERAL))
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
    else if(IsMoving(GENERAL))
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

}