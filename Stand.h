#ifndef STAND_H
#define STAND_H

#include "raylib.h"
#include "StandBase.h"
#include "Projectile.h"


class Stand : public StandBase {
public:
    Stand(const char* texturePath);
    void Update(Vector2 playerPos, const Sound& summon, const Camera2D& camera);
    bool isActive() const;
    void Draw();
    void Unload();
    ~Stand();

private:
    Texture2D texture;
    Vector2 position;
    bool active = false;
    bool punching = false;
    bool firstUpdate = true;
    float facingRight = 1.0f;

    Projectile* projectiles = nullptr; 
    int projectileCount = 0;
    void Shoot(Vector2 direction);
};

#endif