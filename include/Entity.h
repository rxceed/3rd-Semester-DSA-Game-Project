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
    bool AllowMovement = true;

    bool alive = true;
    bool despawn = false;

    float DespawnCounter = 0;

    bool RunState = false;
    bool AttackState = false;
    bool AttackUpdateRun = false;
    float AttackTime = 0;

    Rectangle hitbox;
    Rectangle TextureFrame;
    Rectangle DestFrame;
    Vector2 CenterPoint;

    Rectangle MeleeAttackHitbox;
    bool MeleeHasBeenHit;

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
    bool IsAlive();
    bool IsDespawned();
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
    bool GetAttackState();
    void SetAttackState(bool var);
    
    bool HasMeleeBeenHit();
    bool HasAttackUpdateRan();
    void SetAttackUpdateRun(bool var);
    void SetHasMeleeBeenHit(bool val);

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
        Texture2D death;
    };
    enum TextureListIndex
    {
        IDLE, WALK, RUN, ATTACK1, ATTACK2, ATTACK3, DEAD
    };

    TextureList tex_list;

    public:
    Player(Vector2 position);
    Player();
    ~Player();
    void update();
    void DetectInput();
    void UpdateTexture();
    void UpdateFrame();

    void UpdateMelee(Entity &target);

    void draw();
};

class Enemy:public Entity
{
    protected:
    Rectangle DetectionRadiusIdle;
    Rectangle DetectionRadiusChasing;
    Rectangle DetectionRadius;

    Vector2 MovementTarget;

    bool wandering = false;
    bool chasing = false;
    bool idle = true;;

    public:
    Enemy(Vector2 position);
    Enemy();
    ~Enemy();

    void UpdateWander();
    Vector2 GetMovementTarget();

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
        Texture2D death;
    };
    enum TextureListIndex
    {
        IDLE, WALK, ATTACK1, ATTACK2, DEAD
    };

    TextureList tex_list;

    public:
    Orc(Vector2 position);
    Orc();
    ~Orc();
    void update();
    void UpdateTexture();
    void UpdateFrame();
    void UpdateMelee(Entity &target);

    void DetectPlayer(Player *player);
};


#endif
