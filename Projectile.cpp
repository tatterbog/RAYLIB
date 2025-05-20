#include "Projectile.h"
#include <cmath>

Projectile::Projectile() : active(false), position({ 0, 0 }), velocity({ 0, 0 }) {
    texture.id = 0;
}

void Projectile::Spawn(Vector2 pos, Vector2 dir, Texture2D& tex) {
    velocity = { dir.x * speed, dir.y * speed };
    position = pos;
    active = true;
    texture = tex;
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

bool Projectile::CheckCollision(Vector2 targetPos, float targetWidth, float targetHeight) const {
    if (!active) { return false; }

    Rectangle projectileRect = { position.x, position.y, projWidth, projHeight };
    Rectangle targetRect = { targetPos.x, targetPos.y, targetWidth, targetHeight };

    return CheckCollisionRecs(projectileRect, targetRect);
}

void Projectile::Draw() const {
    if (!active) return;

    if (texture.id != 0) {
        Rectangle src = { 0, 0, (float)texture.width, (float)texture.height };
        Rectangle dst = { position.x, position.y, TILE_SIZE, TILE_SIZE }; // the projectile will be drawn in this size
        Vector2 origin = { 0, 0 };
        DrawTexturePro(texture, src, dst, origin, 0.0f, WHITE);
    }
    else {
        DrawCircleV(position, radius, RED);
    }
}


bool Projectile::IsActive() const {
    return active;
}

