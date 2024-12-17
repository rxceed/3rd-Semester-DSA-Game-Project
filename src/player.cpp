#include "raylib.h"
#include "entity.h"
#include "AttackList.h"
#include <iostream>

Player::Player(Vector2 position):Entity(health, position, speed, defense, attack, AttackSpeed)
{
    SetHealth(500);
    SetPosition(position);
    SetSpeed(100);
    SetDefense(10);
    SetAttack(30);
    SetASPD(0.7f);
    
    tex_list.idle = LoadTexture("./assets/player/IDLE.png");
    tex_list.run = LoadTexture("./assets/player/RUN.png");
    tex_list.walk = LoadTexture("./assets/player/WALK.png");
    tex_list.attack1 = LoadTexture("./assets/player/ATTACK 1.png");
    tex_list.attack2 = LoadTexture("./assets/player/ATTACK 2.png");
    tex_list.attack3 = LoadTexture("./assets/player/ATTACK 3.png");
    tex_list.death = LoadTexture("./assets/player/DEATH.png");
    
    texture = tex_list.idle;
    alive = true;

    TextureFrame = Rectangle({28, 25, 32, 38});
    DestFrame = Rectangle({position.x, position.y, TextureFrame.width*2, TextureFrame.height*2});
    hitbox = Rectangle({DestFrame.x - DestFrame.width/2.0f, DestFrame.y - DestFrame.height/2.0f, DestFrame.width, DestFrame.height});
    
    MeleeAttackHitbox = {GetPosition().x, GetHitbox().y, 80, GetHitbox().height};

    AttackTime = 0;

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
            MeleeAttackHitbox = {GetPosition().x, GetHitbox().y, 60, GetHitbox().height};
        }
        else if(GetOrientation() == LEFT)
        {
            MeleeAttackHitbox = {GetPosition().x-MeleeAttackHitbox.width, GetHitbox().y, 60, GetHitbox().height};
        }

        UpdateFrame();
        UpdateTexture();

        DestFrame = Rectangle({position.x, position.y, abs(TextureFrame.width*2), abs(TextureFrame.height*2)});
        hitbox = Rectangle({DestFrame.x - DestFrame.width/2.0f, DestFrame.y - DestFrame.height/2.0f, DestFrame.width, DestFrame.height});
        std::cout<<health<<std::endl;
        if(health <= 0)
        {
            alive = false;
            AllowMovement = false;
            std::cout<<health<<std::endl;
        }
    }
    else
    {
        UpdateFrame();
        UpdateTexture();
    }
    
}
void Player::DetectInput()
{
    //Movement
    if(AllowMovement)
    {   
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
    }
    //Action
    //Attack
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if(!AttackState)
        {
            AttackState = true;
            if(orientation == RIGHT)
            {
                SetPosition({position.x+20,position.y});
            }
            else
            {
                SetPosition({position.x-20,position.y});
            }
            
            std::cout<<"ATTACK"<<std::endl;
        }
    }
}
void Player::UpdateFrame()
{
    float TIME_PER_FRAME;
    int TextureFrameJump;
    switch(AnimationActionSet)
    {
    case IDLE:
        if(orientation == RIGHT)
        {
            TextureFrame.width = 35;
        }
        else
        {
            TextureFrame.width = -35;
        }
        
        TextureFrame.height = 38;
        TIME_PER_FRAME = 1.4f/7.0f;
        TextureFrameJump = 96;

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
        TextureFrameJump = 96;

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
        TextureFrameJump = 96;

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
                TextureFrame.x = 28;
                AnimationKeyframe = 7;
                AnimationTime = 0;
            }
        }
        AnimationTime += GetFrameTime();
        break;

    case ATTACK1:
        if(orientation == RIGHT && (AnimationKeyframe == 5 || AnimationKeyframe == 5 || AnimationKeyframe == 1))
        {
            TextureFrame.width = 32;
        }
        else if(orientation == LEFT && (AnimationKeyframe == 5 || AnimationKeyframe == 0 || AnimationKeyframe == 1))
        {
            TextureFrame.width = -32;
        }
        else if(orientation == RIGHT && (AnimationKeyframe == 2 || AnimationKeyframe == 3 || AnimationKeyframe == 4))
        {
            TextureFrame.width = 55;
        }
        else if(orientation == LEFT && (AnimationKeyframe == 2 || AnimationKeyframe == 3 || AnimationKeyframe == 4))
        {
            TextureFrame.width = -55;
        }
        TextureFrame.height = 38;
        TIME_PER_FRAME = GetASPD()/6.0f;
        TextureFrameJump = 96;

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
                TextureFrame.x = 302;
                AnimationKeyframe = 2;
            }
        }
        else if(AnimationTime <= TIME_PER_FRAME*4)
        {
            if(AnimationKeyframe != 3)
            {
                TextureFrame.x = 405;
                AnimationKeyframe = 3;
            }
        }
        else if(AnimationTime <= TIME_PER_FRAME*5)
        {
            if(AnimationKeyframe != 4)
            {
                TextureFrame.x = 501;
                AnimationKeyframe = 4;
            }
            
        }
        else if(AnimationTime <= TIME_PER_FRAME*6)
        {
            if(AnimationKeyframe != 5)
                TextureFrame.x = 28;
                AnimationKeyframe = 5;
                AnimationTime = 0;
            }
        AnimationTime = AttackTime;
        break;
    case DEAD:
    if(orientation == RIGHT)
        {
            TextureFrame.width = 43;
        }
        else
        {
            TextureFrame.width = -43;
        }
        TextureFrame.height = 38;
        TIME_PER_FRAME = 2.0f/12.0f;
        TextureFrameJump = 96;

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
                TextureFrame.x += TextureFrameJump;
                AnimationKeyframe = 7;
            }
        }
        else if(AnimationTime <= TIME_PER_FRAME*9)
        {
            if(AnimationKeyframe != 8)
            {
                TextureFrame.x += TextureFrameJump;
                AnimationKeyframe = 8;
            }
        }
        else if(AnimationTime <= TIME_PER_FRAME*10)
        {
            if(AnimationKeyframe != 9)
            {
                TextureFrame.x += TextureFrameJump;
                AnimationKeyframe = 9;
            }
        }
        else if(AnimationTime <= TIME_PER_FRAME*11)
        {
            if(AnimationKeyframe != 10)
            {
                TextureFrame.x += TextureFrameJump;
                AnimationKeyframe = 10;
            }
        }
        else if(AnimationTime <= TIME_PER_FRAME*12)
        {
            if(AnimationKeyframe != 11)
            {
                TextureFrame.x += TextureFrameJump;
                AnimationKeyframe = 11;
            }
        }
        AnimationTime += GetFrameTime();

    default:
        break;
    }
}
void Player::UpdateTexture()
{

    if(IsMoving(GENERAL) && !IsRunStateTrue() && !AttackState && IsAlive())
    {
        if(AnimationActionSet != WALK)
        {
            texture = tex_list.walk;
            AnimationActionSet = WALK;
            if(AnimationTime >= 0)
            {
                AnimationTime = 0;
                AnimationKeyframe = 0;
                TextureFrame.x = 28;
            }
        }
    }
    else if(!IsMoving(GENERAL) && !AttackState && IsAlive())
    {
        if(AnimationActionSet != IDLE)
        {
            texture = tex_list.idle;
            AnimationActionSet = IDLE;
            if(AnimationTime >= 0)
            {
                AnimationTime = 0;
                AnimationKeyframe = 0;
                TextureFrame.x = 28;
            }
        }
    }
    else if(IsMoving(GENERAL) && IsRunStateTrue() && !AttackState && IsAlive())
    {
        if(AnimationActionSet != RUN)
        {
            texture = tex_list.run;
            AnimationActionSet = RUN;
            if(AnimationTime >=0 )
            {
                AnimationTime = 0;
                AnimationKeyframe = 0;
                TextureFrame.x = 28;
            }
        }
    }
    else if(AttackState && IsAlive())
    {
        if(AnimationActionSet != ATTACK1)
        {
            texture = tex_list.attack1;
            AnimationActionSet = ATTACK1;
            if(AnimationTime >=0 )
            {
                AnimationTime = 0;
                AnimationKeyframe = 0;
                TextureFrame.x = 28;
            }
        }
    }
    else if(!IsAlive())
    {
        if(AnimationActionSet != DEAD)
        {
            texture = tex_list.death;
            AnimationActionSet = DEAD;
            if(AnimationTime >=0 )
            {
                AnimationTime = 0;
                AnimationKeyframe = 0;
                TextureFrame.x = 28;
            }
        }
    }
}

void Player::UpdateMelee(Entity &target)
{
    if(AttackState)
    {
        if(!target.HasMeleeBeenHit() && CheckCollisionRecs(MeleeAttackHitbox, target.GetHitbox()))
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
            
            
            std::cout<<target.GetPosition().x<<std::endl;
        }
    }
    else
    {
        target.SetHasMeleeBeenHit(false);
    }
}

void Player::draw()
{
    if(AttackState)
    {
        //DrawRectangleRec(MeleeAttackHitbox, RED);
    }
    DrawTexturePro(texture, TextureFrame, DestFrame, {DestFrame.width/2.0f, DestFrame.height/2.0f}, 0, WHITE);
}