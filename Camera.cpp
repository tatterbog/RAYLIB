#include "raylib.h"
#include "Camera.h"

CameraControl::CameraControl(Vector2 startTarget, Vector2 offset, float zoom){
    camera.target = startTarget;
    camera.offset = offset;
    camera.rotation = 0.0f;
    camera.zoom = zoom;
}

void CameraControl::Update(Vector2 targetPos) {
    camera.target.x = targetPos.x;
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