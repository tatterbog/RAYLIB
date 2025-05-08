#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include "raylib.h"

#define TILE_SIZE 32
#define WIDTH 800 
#define HEIGHT 600 
#define TILE_COLS 200
#define TILE_ROWS (HEIGHT / TILE_SIZE)

class Player : public Character{
private:
    Texture2D texture;
    Vector2 position;
    float scale;
    int health = 100;
    float velocityY = 0.0f;
    bool OnGround = false;
    float gravity = 0.4f;
    float facingRight = 1.0f;
    bool isTile(int el);


public:
    Player(const char* texturePath = "", Vector2 startPos = {0, 0}, float startScale = 1.1f);

    void Update(int level[][TILE_COLS]);
    void Draw();
    void Unload();

    float getGravity();
    Vector2 getPosition();
};

#endif