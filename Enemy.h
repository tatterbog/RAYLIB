#ifndef ENEMY_H
#define ENEMY_H

#include "Globals.h"
#include "EnemyStand.h"
#include "Character.h"
#include "EnemyStand.h"

class Enemy : public Character {
public:
    bool toBeDeleted = false;
    Enemy(Vector2 startPos, const char* texturePath, const char* standTexturePath,
        Sound summonSound, const char* projectileTexturePath, int LevelID);
    void Update(int level[][TILE_COLS], int currentLevel) override;
    void Update(int level[][TILE_COLS], int currentLevel, Character* player, const Camera2D& camera);
    int getDeathCount();
    void setGravity(float f);
    void TakeDamage(int amount);
    void setHealth(int amount);
    int GetHealth() const;
    void DrawHealthBar() const;
    bool isDead() { return false; };
    void ClearProjectiles();
    float getGravity() { return gravity; };
    Vector2 getPosition();
    float getHeight() { return texture.height; };
    float getWidth() { return texture.width; };
    void setPosition(const Vector2& vec);
    bool isActive() { return Active; };
    int getLevel() const;
    void Draw();
    void Unload();
    ~Enemy();

private:
    Texture2D texture;
    Texture2D projectileTexture;
    Vector2 position;
    Vector2 startPos;
    float speed = 1.0f;
    float roamRange = 200.0f;
    float gravity = 4.0f;
    float shootRate = 0.5f;
    float velocityY = 0;
    bool OnGround = false;
    bool movingRight = true;
    bool facingRight = true;
    bool Active = false;
    float scale = 0.65f;
    int health = 120;
    int maxHealth = 120;
    int levelID;

    Sound summonSound;
    EnemyStand stand;
    float shootCooldown = 0;
};

#endif