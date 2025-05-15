#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "raylib.h"
#include "Globals.h"


class Projectile {
public:
    Projectile();
    void Spawn(Vector2 pos, Vector2 dir);
    void Update();
    void Draw() const;
    bool IsActive() const;
    Vector2 GetPosition() const { return position; }
    void Deactivate() { active = false; }

private:
    Vector2 position;
    Vector2 velocity;
    bool active;
    float speed = 8.0f;
    float radius = 5.0f;
};

#endif

