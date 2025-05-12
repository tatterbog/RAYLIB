#include "Level.h"
#include <iostream>

Level::Level(int **layout, Texture2D dirt, Texture2D grass, Texture2D end, const Music& song)
    : dirtTex(dirt),  grassTex(grass), endTex(end), music(song) {
    for (int i = 0; i < TILE_ROWS; i++) {
        for (int j = 0; j < TILE_COLS; j++) {
            tiles[i][j] = layout[i][j];
        }
    }

}

int Level::Draw(Character* player, int currentLevel, int totalLevels) {
    if (!musicPlaying) {
        PlayMusicStream(music);
        musicPlaying = true;
    }

    UpdateMusicStream(music); 

    Vector2 playerPos = player->getPosition();
    Rectangle playerRect = { playerPos.x, playerPos.y, TILE_SIZE, TILE_SIZE };

    for (int i = 0; i < TILE_ROWS; i++) {
        for (int j = 0; j < TILE_COLS; j++) {
            int tile = tiles[i][j];
            int x = j * TILE_SIZE;
            int y = i * TILE_SIZE;
            Rectangle tileRect = { x, y, TILE_SIZE, TILE_SIZE };

            switch (tile) {
            case 3:
                DrawRectangle(x, y, TILE_SIZE, TILE_SIZE, DARKPURPLE);
                if (CheckCollisionRecs(playerRect, tileRect)) {
                    StopMusic(); 
                    currentLevel = (currentLevel + 1) % totalLevels;
                    player->setPosition({ (float)GetScreenWidth()/2 , (float)GetScreenHeight() / 2 });
                    player->setGravity(0.4f);
                }
                break;
            case 2:
                DrawTexture(dirtTex, x, y, WHITE);
                break;
            case 1:
                DrawTexture(grassTex, x, y, WHITE);
                break;
            default:
                DrawRectangle(x, y, TILE_SIZE, TILE_SIZE, SKYBLUE);
                break;
            }
        }
    }
    return currentLevel;
}

int (*Level::getTiles())[TILE_COLS] {
    return tiles;
}

void Level::DrawTutorial(int levelIndex) {
    if (levelIndex != 0) { return; } // Only show in level 0
    DrawText("Welcome to the tutorial!", 10, 200, 20, DARKGRAY);

    Vector2 movePos = { GetScreenWidth() / 2 - 100, GetScreenHeight() / 2};  // Centered for move tutorial
    Vector2 jumpPos = { GetScreenWidth() / 2 - 100, GetScreenHeight() / 2 + 40 };        // Below for jump tutorial
    Vector2 summonPos = { GetScreenWidth() / 2 + 450, GetScreenHeight() / 2 + 20 };  // Below jump tutorial
    Vector2 proceedPos = { GetScreenWidth() / 2 + 1600, GetScreenHeight() / 2 + 20 };      // At the bottom for proceed tutorial

    DrawText("Press [A]/[D] to move (the arrow keys work too)", movePos.x, movePos.y, 20, BLACK);
    DrawText("Press [SPACE] to jump", jumpPos.x, jumpPos.y, 20, BLACK);
    DrawText("Press [F] to summon Stand", summonPos.x, summonPos.y, 20, BLACK);
    DrawText("(he's a helpful fella can do a lot of things, at least in the future)", summonPos.x, summonPos.y + 20, 20, BLACK); 
    DrawText("That's the end of the level, oh noooo how will you reach there?",
        proceedPos.x, proceedPos.y, 20, DARKGREEN);
    DrawText("Press [G] to flip the gravity and jump",
        proceedPos.x, proceedPos.y + 20, 20 , DARKGREEN);
}

void Level::StopMusic() {
    StopMusicStream(music);
    musicPlaying = false;
}