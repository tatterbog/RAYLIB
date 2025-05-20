#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "raylib.h"
#include "Globals.h"


class Projectile {
public:
    Projectile();
    void Spawn(Vector2 pos, Vector2 dir, Texture2D& tex);
    void Update();
    void Draw() const;
    bool IsActive() const;
    bool CheckCollision(Vector2 targetPos, float targetWidth, float targetHeight) const;
    Vector2 GetPosition() const { return position; }
    void Deactivate() { active = false; }

private:
    Vector2 position;
    Vector2 velocity;
    Texture2D texture;
    bool active;
    float speed = 8.0f;
    float radius = 5.0f;
    float projWidth = 10.0f;
    float projHeight = 5.0f;
};

#endif

