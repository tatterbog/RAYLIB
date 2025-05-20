#include "EnemyStand.h"
#include <cmath>

EnemyStand::EnemyStand(const char* standTexturePath, const char* projectileTexturePath)
    : position({ 0, 0 }), projectiles(new Projectile[MAX_ENEMY_PROJECTILES]), projectileCount(0) {
    texture = LoadTexture(standTexturePath);
    projectileTexture = LoadTexture(projectileTexturePath);
}

void EnemyStand::Update(Vector2 enemyPos, Character* player, const Sound& summon, const Camera2D& camera, bool enemyFacingRight) {
    float xOffset = xAxis;
    if (!enemyFacingRight) {
        xOffset *= -1;
    }
    Vector2 desiredPos = { enemyPos.x + xOffset, enemyPos.y + 10 };
    Vector2 toEnemy = { desiredPos.x - position.x, desiredPos.y - position.y };
    position.x += toEnemy.x * 0.05f;
    position.y += toEnemy.y * 0.05f;

    Vector2 playerPos = player->getPosition(); 
    Vector2 toPlayer = { playerPos.x - position.x, playerPos.y - position.y };

    float dx = toPlayer.x;
    float dy = toPlayer.y;
    float sqrDist = dx * dx + dy * dy;

    facingRight = (toPlayer.x >= 0);

    if (firstUpdate) {
        PlaySound(summon);
        active = true;
        firstUpdate = false;
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

    // checking collision against the player
    for (int i = 0; i < projectileCount; i++) {
        if (projectiles[i].CheckCollision(player->getPosition(), player->getWidth(), player->getHeight())) {
            player->TakeDamage(HIT);
            projectiles[i].Deactivate(); 
        }
    }
}

void EnemyStand::Shoot(Vector2 direction) {
    float len = sqrtf(direction.x * direction.x + direction.y * direction.y);
    if (len == 0 || projectileCount >= MAX_ENEMY_PROJECTILES) return;

    Vector2 normDir = { direction.x / len, direction.y / len };
    projectiles[projectileCount++].Spawn(position, normDir, projectileTexture); 
}


void EnemyStand::Draw() {
    Rectangle source = { 0.0f, 0.0f, (float)texture.width, (float)texture.height };
    if (!facingRight) {
        source.width *= -1; 
    }
    Rectangle dest = { position.x, position.y, texture.width * scale, texture.height * scale };
    DrawTexturePro(texture, source, dest, { 0, 0 }, 0.0f, WHITE);

    for (int i = 0; i < projectileCount; i++) {
        projectiles[i].Draw();
    }
}

void EnemyStand::ClearProjectiles() {
    projectileCount = 0;
}

bool EnemyStand::isActive() const{
    return active;
}

EnemyStand::~EnemyStand() {
    Unload();
    delete[] projectiles;
}

void EnemyStand::Unload() {
    UnloadTexture(texture);
}