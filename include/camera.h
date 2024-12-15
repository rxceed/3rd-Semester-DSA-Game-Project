#ifndef CAMERA_H
#define CAMERA_H

#include "raylib.h"
#include "entity.h"

class PlayerCamera
{
    private:

    Camera2D camera;
    Vector2 offset;

    Entity *TargetEntity;

    float rotation;
    float zoom;

    float CameraTrackSpeed;

    public:
    PlayerCamera(Entity& target);
    PlayerCamera();
    ~PlayerCamera();

    void SetOffset(Vector2 val);
    void SetTarget(Entity& target);
    void SetRotation(float val);
    void SetZoom(float val);
    void SetTrackSpeed(float val);

    Camera2D GetCamera();
    Vector2 GetOffset();
    Entity GetTarget();
    float GetRotation();
    float GetZoom();
    float GetTrackSpeed();

    void update();
    
    void MoveUp();
    void MoveDown();
    void MoveRight();
    void MoveLeft();
};

#endif
