#ifndef GLOBALS_H
#define GLOBALS_H

#define TILE_SIZE 32
#define WIDTH 800 
#define HEIGHT 600 
#define TILE_COLS 100
#define TILE_ROWS (HEIGHT / TILE_SIZE)
#define WORLD_WIDTH  (TILE_COLS * TILE_SIZE)
#define WORLD_HEIGHT ((TILE_ROWS + 0.5f) * TILE_SIZE)
#define MAX_PROJECTILES 20
#define MAX_ENEMY_PROJECTILES 20

const float activationDistance = 150.0f;

#endif