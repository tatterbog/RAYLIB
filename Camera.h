#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "raylib.h"

#define TILE_SIZE 32
#define WIDTH 800 
#define HEIGHT 600 
#define TILE_COLS 100
#define TILE_ROWS (HEIGHT / TILE_SIZE)


class CameraControl {
private:
    Camera2D camera;
    float followSpeed = 1.0f;
    Vector2 worldSize;
public:
    CameraControl(Vector2 startTarget, Vector2 offset = { 0, 0 }, float zoom = 1.0f);

    void Update(Vector2 targetPos);
    void Begin();
    void End();

    Camera2D GetCamera() const;
};
#endif