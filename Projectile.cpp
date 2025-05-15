#include "Projectile.h"
#include <cmath>

Projectile::Projectile() : active(false), position({ 0, 0 }), velocity({ 0, 0 }) {}

void Projectile::Spawn(Vector2 pos, Vector2 dir) {
    velocity = { dir.x * speed, dir.y * speed };
    position = pos;
    active = true;
}

void Projectile::Update() {
    if (!active) { return; }
    position.x += velocity.x;
    position.y += velocity.y;

    if (position.x < 0 || position.y < 0 ||
        position.x > WORLD_WIDTH || position.y > WORLD_HEIGHT) {
        active = false;
    }
}

void Projectile::Draw() const {
    DrawCircleV(position, 5.0f, RED);
}


bool Projectile::IsActive() const {
    return active;
}

