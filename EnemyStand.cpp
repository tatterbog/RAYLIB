#include "EnemyStand.h"
#include <cmath>

EnemyStand::EnemyStand(const char* texturePath) : position({ 0, 0 }), projectiles(new Projectile[MAX_ENEMY_PROJECTILES]){
    texture = LoadTexture(texturePath);
}

void EnemyStand::Update(Vector2 enemyPos, Vector2 playerPos, const Sound& summon, const Camera2D& camera) {
    Vector2 desiredPos = { enemyPos.x - 40, enemyPos.y + 10 };
    Vector2 toEnemy = { desiredPos.x - position.x, desiredPos.y - position.y };
    position.x += toEnemy.x * 0.05f;
    position.y += toEnemy.y * 0.05f;

    Vector2 toPlayer = { playerPos.x - position.x, playerPos.y - position.y };
    float dx = toPlayer.x;
    float dy = toPlayer.y;
    float sqrDist = dx * dx + dy * dy;

    if (toPlayer.x < 0) {
        facingRight = -1.0f;
    }
    else {
        facingRight = 1.0f;
    }

    if (firstUpdate) {
        PlaySound(summon);
        active = true;
        firstUpdate = false;
    }
    
    int activeCount = 0;
    // using the same logic for shooting projectiles as my player stand
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

void EnemyStand::Shoot(Vector2 direction) {
    float len = sqrtf(direction.x * direction.x + direction.y * direction.y);
    if (len == 0 || projectileCount >= MAX_ENEMY_PROJECTILES) { return; }

    Vector2 normDir = { direction.x / len, direction.y / len };
    projectiles[projectileCount++].Spawn(position, normDir);
}

void EnemyStand::Draw() {
    Rectangle src = { 0.0f, 0.0f, (float)texture.width, (float)texture.height };
    if (facingRight < 0) {
        src.width *= -1;
    }

    Rectangle dst = { position.x, position.y, texture.width * 0.6f, texture.height * 0.6f };
    DrawTexturePro(texture, src, dst, { 0, 0 }, 0.0f, WHITE);

    for (int i = 0; i < projectileCount; i++) {
        if (projectiles[i].IsActive()) {
            projectiles[i].Draw();
        }
    }
}

bool EnemyStand::isActive() const{
    return active;
}

void EnemyStand::Unload() {
    UnloadTexture(texture);
}