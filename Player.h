#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include "raylib.h"
#include "Globals.h"

class Player : public Character{
private:
    Texture2D texture;
    Vector2 position;
    float scale;

    float velocityY = 0.0f;
    bool OnGround = false;
    float gravity = 0.4f;
    float facingRight = 1.0f;
    bool isTile(int el);
    int deaths = 0;
    int health = 100;
    int maxHealth = 100;
    float jumpForce = 6.5f;
    bool Dead = false;

public:
    
    Player(const char* texturePath = "", Vector2 startPos = {0, 0}, float startScale = 1.1f);

    void Update(int level[][TILE_COLS], int currentLevel);
    void Draw();
    void Unload();
    int getDeathCount();
    bool isDead();
    void setPosition(const Vector2& vec);
    float getGravity();
    void setGravity(float f);
    Vector2 getPosition();
    float getHeight() { return texture.height; };
    float getWidth() { return texture.width; };
    void TakeDamage(int amount);
    int GetHealth() const;
    void setHealth(int amount);
    void DrawHealthBar() const;
};

#endif