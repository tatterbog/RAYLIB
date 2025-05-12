#ifndef STAND_H
#define STAND_H

#include "raylib.h"

class Stand {
public:
    Stand(const char* texturePath);
    void Update(Vector2 playerPos, const Sound& summon, const Camera2D& camera);
    bool isActive();
    void Draw();
    void Unload();
private:
    Texture2D texture;
    Vector2 position;
    bool active = false;
    bool punching = false;
    bool firstUpdate=true;
    float facingRight = 1.0f;
};

#endif