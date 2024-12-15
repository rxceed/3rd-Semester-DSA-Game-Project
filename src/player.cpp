#include "raylib.h"
#include "entity.h"
#include "AttackList.h"
#include <iostream>

Player::Player(Vector2 position):Entity(health, position, speed, defense, attack, AttackSpeed)
{
    SetHealth(100);
    SetPosition(position);
    SetSpeed(100);
    SetDefense(10);
    SetAttack(10);
    SetASPD(1.0);
    
    tex_list.idle = LoadTexture("./assets/player/IDLE.png");
    tex_list.run = LoadTexture("./assets/player/RUN.png");
    tex_list.walk = LoadTexture("./assets/player/WALK.png");
    tex_list.attack1 = LoadTexture("./assetes/player/ATTACK 1.png");
    tex_list.attack2 = LoadTexture("./assetes/player/ATTACK 2.png");
    tex_list.attack3 = LoadTexture("./assetes/player/ATTACK 3.png");
    
    texture = tex_list.idle;

    //action_attack = PlayerAttack::PlayerAttack(*this);

    TextureFrame = Rectangle({28, 25, 32, 38});
    DestFrame = Rectangle({position.x, position.y, TextureFrame.width*2, TextureFrame.height*2});
    hitbox = Rectangle({DestFrame.x - DestFrame.width/2.0f, DestFrame.y - DestFrame.height/2.0f, DestFrame.width, DestFrame.height});
    
    AnimationTime = 0;
    AnimationKeyframe = 0;
    AnimationActionSet = IDLE;

    orientation = RIGHT;

}
Player::Player():Player({0,0})
{
    
}
Player::~Player()
{
    //UnloadTexture(tex_list.idle);
    //UnloadTexture(tex_list.walk);
    //UnloadTexture(tex_list.run);
}

void Player::update()
{
    if(alive)
    {
        RecordPosition();
        DetectInput();
        DetectMovement();

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

        DestFrame = Rectangle({position.x, position.y, abs(TextureFrame.width*2), abs(TextureFrame.height*2)});
        hitbox = Rectangle({DestFrame.x - DestFrame.width/2.0f, DestFrame.y - DestFrame.height/2.0f, DestFrame.width, DestFrame.height});
    }
}
void Player::DetectInput()
{
    //Movement
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

    if(IsKeyDown(KEY_LEFT_SHIFT))
    {
        SetSpeed(200);
        RunState = true;
    }
    else if(IsKeyReleased(KEY_LEFT_SHIFT))
    {
        SetSpeed(100);
        RunState = false;
    }

    //Action
    //Attack
    if(IsKeyPressed(MOUSE_BUTTON_LEFT))
    {
        //action_attack.StartAttack();
    }
}
void Player::UpdateFrame()
{
    float TIME_PER_FRAME;
    switch(AnimationActionSet)
    {
    case IDLE:
        if(orientation == RIGHT)
        {
            TextureFrame.width = 32;
        }
        else
        {
            TextureFrame.width = -32;
        }
        
        TextureFrame.height = 38;
        TIME_PER_FRAME = 1.4f/7.0f;

        if(AnimationTime <= TIME_PER_FRAME*1)
        {
            if(AnimationKeyframe != 0)
            {
                TextureFrame.x += 96;
                AnimationKeyframe = 0;
            }
        }
        else if(AnimationTime <= TIME_PER_FRAME*2)
        {
            if(AnimationKeyframe != 1)
            {
                TextureFrame.x += 96;
                AnimationKeyframe = 1;
            }
        }
        else if(AnimationTime <= TIME_PER_FRAME*3)
        {
            if(AnimationKeyframe != 2)
            {
                TextureFrame.x += 96;
                AnimationKeyframe = 2;
            }
        }
        else if(AnimationTime <= TIME_PER_FRAME*4)
        {
            if(AnimationKeyframe != 3)
            {
                TextureFrame.x += 96;
                AnimationKeyframe = 3;
            }
        }
        else if(AnimationTime <= TIME_PER_FRAME*5)
        {
            if(AnimationKeyframe != 4)
            {
                TextureFrame.x += 96;
                AnimationKeyframe = 4;
            }
            
        }
        else if(AnimationTime <= TIME_PER_FRAME*6)
        {
            if(AnimationKeyframe != 5)
            {
                TextureFrame.x += 96;
                AnimationKeyframe = 5;
            }
            
        }
        else if(AnimationTime <= TIME_PER_FRAME*7)
        {
            if(AnimationKeyframe != 6)
            {
                TextureFrame.x = 28;
                AnimationTime = 0;
                AnimationKeyframe = 6;
            }
        }
        
        AnimationTime += GetFrameTime();
        break;
    
    case WALK:
    if(orientation == RIGHT)
        {
            TextureFrame.width = 42;
        }
        else
        {
            TextureFrame.width = -42;
        }
        TextureFrame.height = 38;
        TIME_PER_FRAME = 1.5f/8.0f;

        if(AnimationTime <= TIME_PER_FRAME*1)
        {
            if(AnimationKeyframe != 0)
            {
                TextureFrame.x += 96;
                AnimationKeyframe = 0;
            }
        }
        else if(AnimationTime <= TIME_PER_FRAME*2)
        {
            if(AnimationKeyframe != 1)
            {
                TextureFrame.x += 96;
                AnimationKeyframe = 1;
            }
        }
        else if(AnimationTime <= TIME_PER_FRAME*3)
        {
            if(AnimationKeyframe != 2)
            {
                TextureFrame.x += 96;
                AnimationKeyframe = 2;
            }
        }
        else if(AnimationTime <= TIME_PER_FRAME*4)
        {
            if(AnimationKeyframe != 3)
            {
                TextureFrame.x += 96;
                AnimationKeyframe = 3;
            }
        }
        else if(AnimationTime <= TIME_PER_FRAME*5)
        {
            if(AnimationKeyframe != 4)
            {
                TextureFrame.x += 96;
                AnimationKeyframe = 4;
            }
            
        }
        else if(AnimationTime <= TIME_PER_FRAME*6)
        {
            if(AnimationKeyframe != 5)
            {
                TextureFrame.x += 96;
                AnimationKeyframe = 5;
            }
            
        }
        else if(AnimationTime <= TIME_PER_FRAME*7)
        {
            if(AnimationKeyframe != 6)
            {
                TextureFrame.x += 96;
                AnimationKeyframe = 6;
            }
        }
        else if(AnimationTime <= TIME_PER_FRAME*8)
        {
            if(AnimationKeyframe != 7)
            {
                TextureFrame.x = 28;
                AnimationKeyframe = 7;
                AnimationTime = 0;
            }
        }
        AnimationTime += GetFrameTime();
        break;
    case RUN:
    if(orientation == RIGHT)
        {
            TextureFrame.width = 43;
        }
        else
        {
            TextureFrame.width = -43;
        }
        TextureFrame.height = 38;
        TIME_PER_FRAME = 1.0f/8.0f;

        if(AnimationTime <= TIME_PER_FRAME*1)
        {
            if(AnimationKeyframe != 0)
            {
                TextureFrame.x += 96;
                AnimationKeyframe = 0;
            }
        }
        else if(AnimationTime <= TIME_PER_FRAME*2)
        {
            if(AnimationKeyframe != 1)
            {
                TextureFrame.x += 96;
                AnimationKeyframe = 1;
            }
        }
        else if(AnimationTime <= TIME_PER_FRAME*3)
        {
            if(AnimationKeyframe != 2)
            {
                TextureFrame.x += 96;
                AnimationKeyframe = 2;
            }
        }
        else if(AnimationTime <= TIME_PER_FRAME*4)
        {
            if(AnimationKeyframe != 3)
            {
                TextureFrame.x += 96;
                AnimationKeyframe = 3;
            }
        }
        else if(AnimationTime <= TIME_PER_FRAME*5)
        {
            if(AnimationKeyframe != 4)
            {
                TextureFrame.x += 96;
                AnimationKeyframe = 4;
            }
            
        }
        else if(AnimationTime <= TIME_PER_FRAME*6)
        {
            if(AnimationKeyframe != 5)
            {
                TextureFrame.x += 96;
                AnimationKeyframe = 5;
            }
            
        }
        else if(AnimationTime <= TIME_PER_FRAME*7)
        {
            if(AnimationKeyframe != 6)
            {
                TextureFrame.x += 96;
                AnimationKeyframe = 6;
            }
        }
        else if(AnimationTime <= TIME_PER_FRAME*8)
        {
            if(AnimationKeyframe != 7)
            {
                TextureFrame.x = 28;
                AnimationKeyframe = 7;
                AnimationTime = 0;
            }
        }
        AnimationTime += GetFrameTime();
        break;
    default:
        break;
    }
}
void Player::UpdateTexture()
{

    if(IsMoving(GENERAL) && !IsRunStateTrue())
    {
        if(AnimationActionSet != WALK)
        {
            texture = tex_list.walk;
            AnimationActionSet = WALK;
            if(AnimationTime >= 0)
            {
                AnimationTime = 0;
                AnimationKeyframe = 0;
            }
        }
    }
    else if(!IsMoving(GENERAL))
    {
        if(AnimationActionSet != IDLE)
        {
            texture = tex_list.idle;
            AnimationActionSet = IDLE;
            if(AnimationTime >= 0)
            {
                AnimationTime = 0;
                AnimationKeyframe = 0;
            }
        }
    }
    else if(IsMoving(GENERAL) && IsRunStateTrue())
    {
        if(AnimationActionSet != RUN)
        {
            texture = tex_list.run;
            AnimationActionSet = RUN;
            if(AnimationTime >=0 )
            {
                AnimationTime = 0;
                AnimationKeyframe = 0;
            }
        }
    }
}

void Player::draw()
{
    //action_attack.DebugDraw();
    DrawTexturePro(texture, TextureFrame, DestFrame, {DestFrame.width/2.0f, DestFrame.height/2.0f}, 0, WHITE);
}