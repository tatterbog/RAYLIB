#ifndef CHARACTER_H
#define CHARACTER_H

#include "raylib.h"
#define TILE_SIZE 32
#define WIDTH 800 
#define HEIGHT 600 
#define TILE_COLS 200
#define TILE_ROWS (HEIGHT / TILE_SIZE)


class Character {
public:
    virtual void Update(int level[][TILE_COLS]) = 0;
    virtual void Draw() = 0;
    virtual void Unload() = 0;
    virtual Vector2 getPosition() = 0;
    virtual ~Character() {};
};

#endif