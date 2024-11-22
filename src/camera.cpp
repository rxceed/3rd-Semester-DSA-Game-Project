#include <math.h>
#include "raylib.h"
#include "camera.h"
#include "entity.h"
#include "settings.h"

PlayerCamera::PlayerCamera(Entity& target)
{
    TargetEntity = &target;
    SetOffset({WINDOW_WIDTH/2, WINDOW_HEIGHT/2});
    camera.target = camera.target = TargetEntity->GetPosition();
    SetRotation(0);
    SetZoom(1);
}
PlayerCamera::~PlayerCamera()
{

}

void PlayerCamera::SetOffset(Vector2 val)
{
    camera.offset = val;
}
void PlayerCamera::SetTarget(Entity& target)
{
    TargetEntity = &target;
    camera.target = TargetEntity->GetPosition();
}
void PlayerCamera::SetRotation(float val)
{
    camera.rotation = val;
}
void PlayerCamera::SetZoom(float val)
{
    camera.zoom = val;
}

Camera2D PlayerCamera::GetCamera()
{
    return camera;
}
Vector2 PlayerCamera::GetOffset()
{
    return camera.offset;
}
Entity PlayerCamera::GetTarget()
{
    return *TargetEntity;
}
float PlayerCamera::GetRotation()
{
    return camera.rotation;
}
float PlayerCamera::GetZoom()
{
    return camera.zoom;
}
void PlayerCamera::update()
{
    //camera.target = TargetEntity->GetPosition();
    if(int(fabs(camera.target.x - TargetEntity->GetPosition().x)) >= 600)
    {
        if(camera.target.x < TargetEntity->GetPosition().x)
        {
            camera.target.x += TargetEntity->GetSpeed();
        }
        else if(camera.target.x > TargetEntity->GetPosition().x)
        {
            camera.target.x -= TargetEntity->GetSpeed();
        }
    }

    if(int(fabs(camera.target.y - TargetEntity->GetPosition().y)) >= 300)
    {
        if(camera.target.y < TargetEntity->GetPosition().y)
        {
            camera.target.y += TargetEntity->GetSpeed();
        }
        else if(camera.target.y > TargetEntity->GetPosition().y)
        {
            camera.target.y -= TargetEntity->GetSpeed();
        }
    }


    if(!TargetEntity->IsMoving(GENERAL))
    {
        if(camera.target.x < TargetEntity->GetPosition().x)
        {
            camera.target.x += 0.5;
        }
        else if(camera.target.x > TargetEntity->GetPosition().x)
        {
            camera.target.x -= 0.5;
        }

        if(camera.target.y < TargetEntity->GetPosition().y)
        {
            camera.target.y += 0.5;
        }
        else if(camera.target.y > TargetEntity->GetPosition().y)
        {
            camera.target.y -= 0.5;
        }
    }
}