#include "Level.h"
#include <iostream>

Level::Level(int **layout, Texture2D dirt, Texture2D grass, Texture2D end, Texture2D bckg, const Music& song)
    : dirtTex(dirt),  grassTex(grass), endTex(end), backgroundTex(bckg), music(song) {
    for (int i = 0; i < TILE_ROWS; i++) {
        for (int j = 0; j < TILE_COLS; j++) {
            tiles[i][j] = layout[i][j];
        }
    }

}

int Level::Draw(Character* player, int currentLevel, int totalLevels, Texture2D winTexture) {
    if (IsKeyPressed(KEY_M)) {
        musicPlaying = !musicPlaying;

        if (musicPlaying) {
            PlayMusicStream(music);
        }
        else {
            PauseMusicStream(music);  // or StopMusicStream(music);
        }
    }

    if (musicPlaying) {
        UpdateMusicStream(music);
    }

    Vector2 playerPos = player->getPosition();
    Rectangle playerRect = { playerPos.x, playerPos.y, TILE_SIZE, TILE_SIZE };
    DrawTexturePro( backgroundTex, 
        { 0, 0, (float)backgroundTex.width, (float)backgroundTex.height },
        { 0, 0, (float)(TILE_COLS * TILE_SIZE), (float)HEIGHT }, { 0, 0 }, 0.0f, WHITE);

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
                    if (currentLevel == totalLevels - 1) {
                        while (!WindowShouldClose() && !IsKeyPressed(KEY_ENTER)) {
                            BeginDrawing();
                            ClearBackground(BLACK);

                            float scale = 0.5f;
                            float width = winTexture.width * scale;
                            float height = winTexture.height * scale;
                            float posX = (GetScreenWidth() - width) / 2;
                            float posY = (GetScreenHeight() - height) / 2;

                            DrawTexturePro(winTexture,
                                { 0, 0, (float)winTexture.width, (float)winTexture.height },
                                { posX, posY, width, height },
                                { 0, 0 }, 0.0f, WHITE);

                            DrawText("YOU WIN! Press ENTER to exit.", posX, posY + height + 20, 20, WHITE);
                            EndDrawing();
                        }

                        CloseWindow();
                        exit(0);
                    }

                    currentLevel = (currentLevel + 1) % totalLevels;
                    player->setPosition({ (float)GetScreenWidth() / 2 , (float)GetScreenHeight() / 2 });
                    player->setGravity(GRAVITY);
                }
                break;
            case 2:
                DrawTexture(dirtTex, x, y, WHITE);
                break;
            case 1:
                DrawTexture(grassTex, x, y, WHITE);
                break;
            default:
                // DrawRectangle(x, y, TILE_SIZE, TILE_SIZE, SKYBLUE);
                break;
            }
        }
    }
    return currentLevel;
}

int (*Level::getTiles())[TILE_COLS] {
    return tiles;
}

void Level::DrawTutorial(Character* player, int levelIndex) {
    if (levelIndex != 0) { return; } // Only show in level 0
    DrawText("Welcome to the tutorial!", 10, 200, FONT, DARKGRAY);

    Vector2 movePos = { GetScreenWidth() / 2 - 100, GetScreenHeight() / 2};  // Centered for move tutorial
    Vector2 jumpPos = { GetScreenWidth() / 2 - 100, GetScreenHeight() / 2 + 40 };        // Below for jump tutorial
    Vector2 summonPos = { GetScreenWidth() / 2 + 450, GetScreenHeight() / 2 + FONT };  // Below jump tutorial
    Vector2 proceedPos = { GetScreenWidth() / 2 + 1600, GetScreenHeight() / 2 + FONT };      // At the bottom for proceed tutorial

    if (player->getDeathCount() > 0 && levelIndex == 0) {
        DrawText("You can only respawn in the tutorial", GetScreenWidth() / 4 + 100, GetScreenHeight() / 4, FONT, RED);
    }
    DrawText("Press [A]/[D] to move (the arrow keys work too)", movePos.x, movePos.y, FONT, BLACK);
    DrawText("Press [SPACE] to jump", jumpPos.x, jumpPos.y, FONT, BLACK);
    DrawText("Press [F] to summon Stand, and press [C] to shoot ", summonPos.x, summonPos.y, FONT, BLACK);
    DrawText("(He's a helpful fella can do a lot of things, Press [H] to heal)", summonPos.x, summonPos.y + FONT, FONT, BLACK); 
    DrawText("That's the end of the level, oh noooo how will you reach there?",
        proceedPos.x, proceedPos.y, FONT, DARKGREEN);
    DrawText("Press [G] to flip the gravity and jump",
        proceedPos.x, proceedPos.y + FONT, FONT , DARKGREEN);
}

void Level::StopMusic() {
    StopMusicStream(music);
    musicPlaying = false;
}