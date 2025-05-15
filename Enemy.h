#ifndef ENEMY_H
#define ENEMY_H

#include "Globals.h"
#include "EnemyStand.h"
#include "Character.h"
#include "EnemyStand.h"

class Enemy : public Character {
public:
    Enemy(Vector2 startPos, const char* texturePath, const char* standTexturePath,
        Sound summonSound, const char* projectileTexturePath);
    void Update(int level[][TILE_COLS], int currentLevel) override;
    void Update(int level[][TILE_COLS], int currentLevel, Vector2 playerPos, const Camera2D& camera);
    int getDeathCount();
    void setGravity(float f);
    Vector2 getPosition();
    void setPosition(const Vector2& vec);
    void Draw();
    void Unload();

private:
    Texture2D texture;
    Texture2D projectileTexture;
    Vector2 position;
    Vector2 startPos;
    float speed = 1.0f;
    float roamRange = 200.0f;
    float gravity = 0.4f;
    float shootRate = 0.5f;
    float velocityY = 0;
    bool OnGround = false;
    bool movingRight = true;
    bool facingRight = true;
    float scale = 0.65f;
    

    Sound summonSound;
    EnemyStand stand;
    float shootCooldown = 0;
};

#endif