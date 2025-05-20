#include "Stand.h"
#include "raylib.h"
#include <iostream>
#include <cmath>

Stand::Stand(const char* standTexturePath, const char* projectileTexturePath)
    : projectiles(new Projectile[MAX_PROJECTILES]), projectileCount(0) {
    texture = LoadTexture(standTexturePath);
    projectileTexture = LoadTexture(projectileTexturePath); 
}

void Stand::Update(Vector2 playerPos, const Sound& summon, const Camera2D& camera) {

    float maxRadius = 100.0f;  
    Vector2 desiredPos = { playerPos.x + 50, playerPos.y - 10 };
    Vector2 toPlayer = {
        desiredPos.x - position.x,
        desiredPos.y - position.y
    };

    position.x += toPlayer.x * 0.1f;
    position.y += toPlayer.y * 0.1f;

    Vector2 mouse = GetScreenToWorld2D(GetMousePosition(), camera);
    Vector2 toMouse = {
        mouse.x - position.x,
        mouse.y - position.y
    };

    float distToMouse = sqrtf(toMouse.x * toMouse.x + toMouse.y * toMouse.y);

    if (distToMouse < maxRadius) {
        position.x += toMouse.x * 0.1f;
        position.y += toMouse.y * 0.1f;
    }
    else {
        float maxMove = 5.0f;
        if (distToMouse > 0.01f) {
            toMouse.x /= distToMouse;  
            toMouse.y /= distToMouse;

            float moveAmount = fminf(distToMouse, maxMove);
            position.x += toMouse.x * moveAmount;
            position.y += toMouse.y * moveAmount;
        }
    }
    facingRight = 1.0f;
    if (mouse.x < position.x) {
        facingRight = -1.0f;
    }


    if (IsKeyPressed(KEY_F)) {
        active = !active;  
        if (active) {
            PlaySound(summon);
        }
    }

    if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
        punching = true;
    }
    if (IsMouseButtonReleased(MOUSE_RIGHT_BUTTON)) {
        active = false;
    }

    if (active) {
        if (IsKeyPressed(KEY_C)) {
            Shoot(toMouse);
        }

        int activeCount = 0;
        for (int i = 0; i < projectileCount; i++) {
            projectiles[i].Update();
            if (projectiles[i].IsActive()) {
                if (i != activeCount) {
                    projectiles[activeCount] = projectiles[i];
                }
                activeCount++;
            }
        }
        projectileCount = activeCount;
    }
}

void Stand::Shoot(Vector2 direction) {
    float len = sqrtf(direction.x * direction.x + direction.y * direction.y);
    if (len == 0 || projectileCount > MAX_ENEMY_PROJECTILES) { return; }

    Projectile* prr = new Projectile[(size_t)projectileCount + 1];
    for (int i = 0; i < projectileCount; i++) {
        prr[i] = projectiles[i];
    }

    Vector2 dirNorm = { direction.x / len, direction.y / len };
    prr[projectileCount].Spawn(position, dirNorm, projectileTexture);

    delete[] projectiles;
    projectiles = prr;
    projectileCount++;
}

void Stand::ClearProjectiles() {
    projectileCount = 0;
}

void Stand::Draw() {
    Rectangle source = { 0.0f, 0.0f, (float)texture.width, (float)texture.height };
    if (facingRight < 0) {
        source.width = -source.width;
    }

    Rectangle dest = { position.x, position.y, texture.width * 0.6f, texture.height * 0.6f };
    Vector2 origin = { 0.0f, 0.0f };

    DrawTexturePro(texture, source, dest, origin, 0.0f, WHITE);

    if (active) {
        for (int i = 0; i < projectileCount; i++) {
            if (projectiles[i].IsActive()) {
                projectiles[i].Draw();
            }
        }
    }
}


bool Stand::isActive() const{
    return active;
}

void Stand::Unload() {
    if (projectiles) {
        delete[] projectiles;
        projectiles = nullptr;
    }

    projectileCount = 0;
    UnloadTexture(projectileTexture);
    UnloadTexture(texture);
}

Stand::~Stand() {
     Unload();
     if (projectiles) {
            delete[] projectiles;
            projectiles = nullptr;
     }
}

