#include <math.h>
#include "raylib.h"
#include "camera.h"
#include "entity.h"
#include "settings.h"
#include <iostream>

PlayerCamera::PlayerCamera(Entity& target)
{
    TargetEntity = &target;
    SetOffset({WINDOW_WIDTH/2, WINDOW_HEIGHT/2});
    camera.target = TargetEntity->GetPosition();
    SetRotation(0);
    SetZoom(1);
    SetTrackSpeed(100);
}
PlayerCamera::PlayerCamera()
{
    
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
void PlayerCamera::SetTrackSpeed(float val)
{
    CameraTrackSpeed = val;
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
float PlayerCamera::GetTrackSpeed()
{
    return CameraTrackSpeed;
}



void PlayerCamera::update()
{
    //camera.target = TargetEntity->GetPosition();
    if(fabs(camera.target.x - TargetEntity->GetPosition().x) >= 600)
    {
        if(camera.target.x < TargetEntity->GetPosition().x)
        {
            camera.target.x += TargetEntity->GetSpeed()*GetFrameTime();
        }
        else if(camera.target.x > TargetEntity->GetPosition().x)
        {
            camera.target.x -= TargetEntity->GetSpeed()*GetFrameTime();
        }
    }

    if(fabs(camera.target.y - TargetEntity->GetPosition().y) >= 300)
    {
        if(camera.target.y < TargetEntity->GetPosition().y)
        {
            camera.target.y += TargetEntity->GetSpeed()*GetFrameTime();
        }
        else if(camera.target.y > TargetEntity->GetPosition().y)
        {
            camera.target.y -= TargetEntity->GetSpeed()*GetFrameTime();
        }
    }


    if(!TargetEntity->IsMoving(GENERAL))
    {
        if((camera.target.x - TargetEntity->GetPosition().x < 5) && (camera.target.x - TargetEntity->GetPosition().x > -5))
        {
            camera.target.x = TargetEntity->GetPosition().x;
        }
        if((camera.target.y - TargetEntity->GetPosition().y < 5) && (camera.target.y - TargetEntity->GetPosition().y > -5))
        {
            camera.target.y = TargetEntity->GetPosition().y;
        }

        if(camera.target.x < TargetEntity->GetPosition().x)
        {
            camera.target.x += CameraTrackSpeed*GetFrameTime();
        }
        else if(camera.target.x > TargetEntity->GetPosition().x)
        {
            camera.target.x -= CameraTrackSpeed*GetFrameTime();
        }

        if(camera.target.y < TargetEntity->GetPosition().y)
        {
            camera.target.y += CameraTrackSpeed*GetFrameTime();
        }
        else if(camera.target.y > TargetEntity->GetPosition().y)
        {
            camera.target.y -= CameraTrackSpeed*GetFrameTime();
        }
    }
}