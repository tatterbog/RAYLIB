#ifndef ENEMYSTAND_H
#define ENEMYSTAND_H

#include "StandBase.h"
#include "raylib.h"
#include "Globals.h"
#include "Projectile.h"

class EnemyStand {
private:
    Texture2D texture;
    Vector2 position;
    float facingRight = 1.0f;
    bool active = false;
    bool firstUpdate = true;

    Projectile* projectiles = nullptr;
    int projectileCount = 0;

public:
    EnemyStand(const char* texturePath);
    void Update(Vector2 enemyPos, Vector2 playerPos, const Sound& summon, const Camera2D& camera);
    void Draw();
    bool isActive() const;
    void Unload();
    void Shoot(Vector2 direction);
};

#endif