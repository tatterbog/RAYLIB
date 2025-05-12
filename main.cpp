#include <iostream>
#include <fstream>
#include "raylib.h"

#include "Player.h"
#include "Character.h"
#include "Camera.h"
#include "Stand.h"
#include "Level.h"

#define totalLevels 3

int** LoadLevel(const std::string& filename);

int main() {

    int** level0 = LoadLevel("levels/level0.txt");
    int** level1 = LoadLevel("levels/level1.txt");
    int** level2 = LoadLevel("levels/level2.txt");

    if (level0 == nullptr || level1 == nullptr || level2 == nullptr) {
        std::cerr << "Error loading level." << std::endl;
        return 2;
    }


    InitWindow(WIDTH, HEIGHT, "Raylib Test");
    SetTargetFPS(60);

    InitAudioDevice();

    Texture2D GiornoDir = LoadTexture("pngs/Giorno.png");
    if (GiornoDir.id == 0) {
        std::cout << "Failed to load Giorno texture!\n";
    }

    Vector2 v2 = { GetScreenWidth() / 2, GetScreenHeight() / 2 };
    Character* Giorno = new Player("pngs/Giorno.png", v2, 0.11f);

    Texture2D dirtDir = LoadTexture("pngs/dirt.png");
    Texture2D grassDir = LoadTexture("pngs/grass.png");
    Texture2D endDir = LoadTexture("pngs/end.png");

    Stand* GoldExp = new Stand("pngs/GoldenExperience.png");
    CameraControl cam(Giorno->getPosition(), { WIDTH / 2.0f, HEIGHT / 2.0f }, 1.0f);

    Music MainSong = LoadMusicStream("songs/MainSong.wav"); //change the songs here for each level
    Sound summon = LoadSound("songs/GoldenExpCall.wav");

    Level* levels[totalLevels] = {
    new Level(level0, dirtDir, grassDir, endDir, MainSong), // here
    new Level(level1, dirtDir, grassDir, endDir, MainSong),
    new Level(level2, dirtDir, grassDir, endDir, MainSong)
    };

    int currentLevel = 0;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        cam.Begin();
        cam.Update(Giorno->getPosition());

        UpdateMusicStream(MainSong);

        if (GoldExp != nullptr) {
            GoldExp->Update(Giorno->getPosition(), summon, cam.GetCamera());
        }
        
        currentLevel = levels[currentLevel]->Draw(Giorno, currentLevel, totalLevels);
        levels[currentLevel]->DrawTutorial(currentLevel);
        Giorno->Update(levels[currentLevel]->getTiles(), currentLevel);
        Giorno->Draw();

        if (GoldExp && GoldExp->isActive()) {
            GoldExp->Draw();
        }

        DrawText("Yee Yee Ahh game", 10, 10, 20, DARKGRAY);
        cam.End();
        EndDrawing();
    }

    UnloadTexture(endDir);
    UnloadTexture(dirtDir);
    UnloadTexture(grassDir);
    UnloadTexture(GiornoDir);

    Giorno->Unload();
    delete Giorno;

    GoldExp->Unload();
    delete GoldExp;

    for (int i = 0; i < totalLevels; ++i) {
        delete levels[i];
    }
    
    UnloadSound(summon);
    UnloadMusicStream(MainSong);

    CloseAudioDevice();
    CloseWindow();
    return 0;
}




int** LoadLevel(const std::string& filename) {
    int** level = new int* [TILE_ROWS]; 
    
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return nullptr;
    }
    
    for (int i = 0; i < TILE_ROWS; i++) {
        level[i] = new int[TILE_COLS];

        for (int j = 0; j < TILE_COLS; j++) {
            file >> level[i][j];  // reading the values
        }
    }

    file.close();
    return level; 
}
