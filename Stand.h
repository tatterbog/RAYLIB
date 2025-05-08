#ifndef STAND_H
#define STAND_H

#include "raylib.h"

class Stand {
public:
    Stand(const char* texturePath);
    void Update(Vector2 playerPos);
    bool isActive();
    void Draw();
    void Unload();
private:
    Texture2D texture;
    Vector2 position;
    bool active = false;
    bool punching = false;
    float rotation = 1.0f;
    bool firstUpdate=true;
};

#endif