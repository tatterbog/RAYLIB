#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "raylib.h"
#include "Globals.h"

class CameraControl {
private:
    Camera2D camera;
    float followSpeed = 1.0f;
    Vector2 worldSize;
    float cameraSpeed = 10.0f;
public:
    CameraControl(Vector2 startTarget, Vector2 offset = { 0, 0 }, float zoom = 1.0f);

    void Update(Vector2 targetPos);
    void Begin();
    void End();

    Camera2D GetCamera() const;
};
#endif