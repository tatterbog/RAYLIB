#include "raylib.h"
#include "Camera.h"
#include <cmath>

CameraControl::CameraControl(Vector2 startTarget, Vector2 offset, float zoom) 
    : camera{ startTarget, offset, 0.0f, zoom } {
  
    worldSize = { TILE_COLS * TILE_SIZE, (TILE_ROWS + 0.5) * TILE_SIZE };
    camera.offset = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
}

void CameraControl::Update(Vector2 targetPos) {
    float screenWidth = GetScreenWidth();
    float screenHeight = GetScreenHeight();
    float zoom = camera.zoom;

    float viewWidth = screenWidth / zoom;
    float viewHeight = screenHeight / zoom;

    float horizontalBias = 0.33f; // Giorno appears on the left third

    camera.target.x = targetPos.x + viewWidth * (0.5f - horizontalBias); // keeping the player on the left
    camera.target.y = targetPos.y;

    
    camera.target.x = fminf(fmaxf(camera.target.x, viewWidth / 2.0f), worldSize.x - viewWidth / 2.0f); //the camera sticks to a box
    camera.target.y = fminf(fmaxf(camera.target.y, viewHeight / 2.0f), worldSize.y - viewHeight / 2.0f);

    if (IsKeyDown(KEY_W)) {
        camera.offset.y -= 10.0f; // move camera up
    }
    if (IsKeyDown(KEY_S)) {
        camera.offset.y += 10.0f; // move camera down
    }

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