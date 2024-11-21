#include "raylib.h"
#include "camera.h"
#include "entity.h"

PlayerCamera::PlayerCamera(Entity& target)
{
    TargetEntity = &target;
    SetOffset(TargetEntity->GetPosition());
    camera.target = TargetEntity->GetPosition();
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
    camera.target = TargetEntity->GetPosition();
    
}