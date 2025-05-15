#ifndef LEVEL_H
#define LEVEL_H

#include "raylib.h"
#include "Character.h"

#include "Globals.h"

class Level {
private:
    int tiles[TILE_ROWS][TILE_COLS];
    Texture2D dirtTex;
    Texture2D grassTex;
    Texture2D endTex, backgroundTex;
    Music music;
    bool musicPlaying = false;

public:
    Level(int **layout, Texture2D dirt, Texture2D grass, Texture2D end, Texture2D backgroundTex, const Music& song);
    int Draw(Character* player, int currentLevel, int totalLevels);
    void DrawTutorial(Character* player, int levelIndex);
    void StopMusic();
    int (*getTiles())[TILE_COLS];
};

#endif