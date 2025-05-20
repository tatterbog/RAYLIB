#ifndef CHARACTER_H
#define CHARACTER_H

#include "raylib.h"
#include "Globals.h"


class Character {
public:
    virtual void Update(int level[][TILE_COLS],int currentLevel) = 0;
    virtual void Draw() = 0;
    virtual void Unload() = 0;
    virtual int getDeathCount() = 0;
    virtual void DrawHealthBar() const = 0;
    virtual void TakeDamage(int amount) = 0;
    virtual float getHeight() = 0;
    virtual float getWidth() =  0;
    virtual int GetHealth() const = 0;
    virtual void setHealth(int amount) = 0;
    virtual void setGravity(float f) = 0;
    virtual float getGravity() = 0;
    virtual bool isDead() = 0;
    virtual Vector2 getPosition() = 0;
    virtual void setPosition(const Vector2& vec) = 0;
    virtual ~Character() {};
};

#endif