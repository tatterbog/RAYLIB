#include "Stand.h"
#include "raylib.h"
#include <iostream>

Stand::Stand(const char* texturePath) {
    texture = LoadTexture(texturePath);
}

void Stand::Update(Vector2 playerPos) {

    Vector2 desiredPos = { playerPos.x + 40, playerPos.y - 10 };
    Vector2 toPlayer = {
        desiredPos.x - position.x,
        desiredPos.y - position.y
    };

    position.x += toPlayer.x * 0.1f;
    position.y += toPlayer.y * 0.1f;

    Vector2 mouse = GetMousePosition();
    Vector2 toMouse = {
        mouse.x - position.x,
        mouse.y - position.y
    };

    float distToMouse = sqrtf(toMouse.x * toMouse.x + toMouse.y * toMouse.y);

    if (distToMouse > 0.01f) {
        toMouse.x /= distToMouse;
        toMouse.y /= distToMouse;

        float maxMove = 5.0f;
        float moveAmount = fminf(distToMouse, maxMove);

        position.x += toMouse.x * moveAmount;
        position.y += toMouse.y * moveAmount;
    }

    rotation = atan2f(mouse.y - position.y, mouse.x - position.x) * RAD2DEG;

    if (IsKeyPressed(KEY_F)) {
        active = !active;  
    }

    if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
        punching = true;
    }
    if (IsMouseButtonReleased(MOUSE_RIGHT_BUTTON)) {
        active = false;
    }
}

void Stand::Draw() {
    DrawTextureEx(texture, {position.x, position.y}, .0f, 0.6f, WHITE);
}

bool Stand::isActive() {
    return active;
}

void Stand::Unload() {
    UnloadTexture(texture);
}