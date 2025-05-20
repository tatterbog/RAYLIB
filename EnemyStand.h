#ifndef ENEMYSTAND_H
#define ENEMYSTAND_H

#include "StandBase.h"
#include "raylib.h"
#include "Globals.h"
#include "Projectile.h"
#include "Player.h"

const float xAxis = 60.0f;

class EnemyStand{
private:
    Texture2D texture;
    Texture2D projectileTexture;
    Vector2 position;
    bool facingRight = false;
    bool active = false;
    bool firstUpdate = true;
    Projectile* projectiles = nullptr;
    int projectileCount = 0;
    float scale = 0.6f;

public:
    EnemyStand(const char* texturePath, const char* projectileTexturePath);
    void Update(Vector2 enemyPos, Character* player, const Sound& summon, const Camera2D& camera, bool enemyFacingRight);
    void Draw();
    void ClearProjectiles();
    bool isActive() const;
    void Unload();
    void Shoot(Vector2 direction);
    ~EnemyStand();
};

#endif