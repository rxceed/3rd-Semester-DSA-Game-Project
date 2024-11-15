#ifndef CAMERA_H
#define CAMERA_H

#include "raylib.h"

class Camera
{
    private:
    Camera2D camera;
    Vector2 offset;
    Vector2 target;
    float rotation;
    float zoom; 
    public:
    Camera();
    
    void MoveUp();
    void MoveDown();
    void MoveRight();
    void MoveLeft();
};



#endif
