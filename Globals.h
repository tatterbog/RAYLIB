#ifndef GLOBALS_H
#define GLOBALS_H

const int TILE_SIZE = 32;
const int WIDTH = 800;
const int HEIGHT = 600;
const int TILE_COLS = 100;
const int TILE_ROWS = (HEIGHT / TILE_SIZE);
const int WORLD_WIDTH = (TILE_COLS * TILE_SIZE);
const float WORLD_HEIGHT = ((TILE_ROWS + 0.5f) * TILE_SIZE);
const int MAX_PROJECTILES = 100;
const int MAX_ENEMY_PROJECTILES = 100;
const float	GRAVITY = 0.4f;
const int FONT = 20;
const float	PLAYER_SCALE = 0.11f;

const float	playerOffset = 5.0f;
const int MAX_HEALTH = 100;
const int HIT = 10;
const float activationDistance = 150.0f;

#endif