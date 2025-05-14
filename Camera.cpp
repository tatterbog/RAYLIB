#include "raylib.h"
#include "Camera.h"
#include <cmath>

CameraControl::CameraControl(Vector2 startTarget, Vector2 offset, float zoom) 
    : camera{ startTarget, offset, 0.0f, zoom } {
  
    camera.rotation = 0.0f;
    worldSize = { TILE_COLS * TILE_SIZE, (TILE_ROWS + 0.5) * TILE_SIZE };
}

void CameraControl::Update(Vector2 targetPos) {
    float cameraHalfWidth = (GetScreenWidth() / 2.0f) / camera.zoom;
    float cameraHalfHeight = (GetScreenHeight() / 2.0f) / camera.zoom;
    if (IsKeyDown(KEY_W)) {
        camera.offset.y -= 10.0f; // move camera up
    }
    if (IsKeyDown(KEY_S)) {
        camera.offset.y += 10.0f; // move camera down
    }
    camera.target.x = fminf(fmaxf(targetPos.x, cameraHalfWidth), worldSize.x - cameraHalfWidth);
    camera.target.y = fminf(fmaxf(targetPos.y, cameraHalfHeight), worldSize.y - cameraHalfHeight);
}

void CameraControl::Begin() {
    BeginMode2D(camera);
}

void CameraControl::End() {
    EndMode2D();
}

Camera2D CameraControl::GetCamera() const {
    return camera;
}