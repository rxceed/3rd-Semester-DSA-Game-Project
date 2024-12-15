#ifndef ENTITY_H
#define ENTITY_H

#include "raylib.h"
#include "AssetsLoading.h"
#include "AttackList.h"


enum Direction
{
    GENERAL, UP, DOWN, RIGHT, LEFT
};


class Entity
{
protected:
    Vector2 position;
    Vector2 PreviousPosition;
    float health;
    float speed;
    float defense;
    float attack;
    float AttackSpeed;

    bool MovingUp = false;
    bool MovingDown = false;
    bool MovingLeft = false;
    bool MovingRight = false;

    bool alive = true;

    bool RunState = false;

    Rectangle hitbox;
    Rectangle TextureFrame;
    Rectangle DestFrame;
    Vector2 CenterPoint;

    int orientation;
    
    Texture2D texture;

    float AnimationTime;
    int AnimationKeyframe;
    int AnimationActionSet;

public:
    Entity(float health, Vector2 position, float speed, float defense, float attack, float AttackSPeed);
    Entity();
    ~Entity();
    void SetHealth(float value);        //Set healt value
    void SetSpeed(float value);         //Set speed value
    void SetPosition(Vector2 value);    //Set position value
    void SetDefense(float value);
    void SetAttack(float value);
    void SetASPD(float value);
    void draw();

    float GetHealth();
    float GetSpeed();
    Vector2 GetPosition();
    float GetDefense();
    float GetAttack();
    float GetASPD();

    //entity movement functions. Affected by speed. position after movement = current position + speed
    void MoveUp();
    void MoveDown();
    void MoveRight();
    void MoveLeft();
    void Displace(Vector2 value);

    void RecordPosition();          //record current position to PreviousPosition variable
    void DetectMovement();          //detect movement. If true, change the value of respective movement boolean to true
    int GetOrientation();

    bool IsMoving(int direction);   //return true if entity is moving in the specified direction
    bool IsRunStateTrue();

    Rectangle GetHitbox();

    void TakeDamage(float damage);

    void ResetAnimationTime();

};

class Player:public Entity
{
    private:
    struct TextureList
    {
        Texture2D idle;
        Texture2D walk;
        Texture2D run;
        Texture2D attack1;
        Texture2D attack2;
        Texture2D attack3;
    };
    enum TextureListIndex
    {
        IDLE, WALK, RUN, ATTACK1, ATTACK2, ATTACK3
    };

    TextureList tex_list;

    //PlayerAttack action_attack;

    public:
    Player(Vector2 position);
    Player();
    ~Player();
    void update();
    void DetectInput();
    void UpdateTexture();
    void UpdateFrame();

    void draw();
};

class Enemy:public Entity
{
    protected:
    Rectangle DetectionRadiusIdle;
    Rectangle DetectionRadiusChasing;

    bool wandering = false;
    bool chasing = false;
    bool idle = true;;

    public:
    Enemy(Vector2 position);
    Enemy();
    ~Enemy();

    void UpdateWander();

    void draw();
};

class Orc:public Enemy
{
    private:

    struct TextureList
    {
        Texture2D idle;
        Texture2D walk;
        Texture2D attack1;
        Texture2D attack2;
    };
    enum TextureListIndex
    {
        IDLE, WALK, ATTACK1, ATTACK2
    };

    TextureList tex_list;

    public:
    Orc(Vector2 position);
    Orc();
    ~Orc();
    void update();
    void UpdateTexture();
    void UpdateFrame();
};


#endif
