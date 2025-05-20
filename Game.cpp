#include "Game.h"
#include <iostream>
#include <fstream>

#define MAX_ENEMIES 5

int** LoadLevel(const std::string& filename);

Game::Game()
    : Giorno(nullptr), GoldExp(nullptr), cam({ 0, 0 }, { WIDTH / 2.0f, HEIGHT / 2.0f }, 1.0f), 
    currentLevel(0), running(true) {

    Init();
}

Game::~Game() {
    Unload();
}

void Game::Init() {
    int** level0 = LoadLevel("levels/level0.txt");
    int** level1 = LoadLevel("levels/level1.txt");
    int** level2 = LoadLevel("levels/level2.txt");

    if (!level0 || !level1 || !level2) {
        std::cerr << "Error loading level.\n" << std::endl;
        running = false;
        return;
    }

    InitWindow(WIDTH, HEIGHT, "Raylib Test");
    SetTargetFPS(60);
    InitAudioDevice();

    GiornoDir = LoadTexture("pngs/Giorno.png");
    dirtDir = LoadTexture("pngs/dirt.png");
    grassDir = LoadTexture("pngs/grass.png");
    endDir = LoadTexture("pngs/end.png");
    Background = LoadTexture("pngs/background.png");
    WinningDir = LoadTexture("pngs/win.png");
    LosingDir = LoadTexture("pngs/lose.png");

    Vector2 spawnPos = { GetScreenWidth() / 2, GetScreenHeight() / 2 };
    Giorno = new Player("pngs/Giorno.png", spawnPos, PLAYER_SCALE);
    GoldExp = new Stand("pngs/GoldenExperience.png", "pngs/GiornoShoot.png");

    cam = CameraControl(Giorno->getPosition(), { WIDTH / 2.0f, HEIGHT / 2.0f }, 1.0f);

    MainSong = LoadMusicStream("songs/MainSong.wav");
    summon = LoadSound("songs/GoldenExpCall.wav");

    levels[0] = new Level(level0, dirtDir, grassDir, endDir, Background, MainSong);
    levels[1] = new Level(level1, dirtDir, grassDir, endDir, Background, MainSong);
    levels[2] = new Level(level2, dirtDir, grassDir, endDir, Background, MainSong);

    enemySummon1 = LoadSound("songs/Metallica.wav");
    enemySummon2 = LoadSound("songs/GreenDayCall.wav");
    enemySummon3 = LoadSound("songs/enemy3Summon.wav");

    enemies[0] = new Enemy({(float)(GetScreenWidth() / 2 + 1600), (float)(GetScreenHeight() / 2 + FONT) }, "pngs/Polpo.png", "pngs/PolpoStand.png",
        enemySummon3, "pngs/PolpoShoot.png", 0);

    enemies[1] = new Enemy({(float)(GetScreenWidth() / 2 + 1600), (float)(GetScreenHeight() / 2 + FONT) }, "pngs/rissoto.png", "pngs/rissotoStand.png",
        enemySummon1, "pngs/metallicaShoot.png", 1);

    enemies[2] = new Enemy({ (float)(GetScreenWidth() / 2 + 1600), (float)(GetScreenHeight() / 2 + FONT) }, "pngs/Ciocolatta.png", "pngs/CiocolattaStand.png",
        enemySummon2, "pngs/ciocolattaShoot.png", 2);

 
}

void Game::Run() {
    if (!running) { return; }

    while (!ShouldClose()) {
        Update();
        Draw();
    }
}

bool Game::ShouldClose() {
    return WindowShouldClose();
}

void Game::Update() {
    cam.Update(Giorno->getPosition() );
    UpdateMusicStream(MainSong);

    if (GoldExp) {
        GoldExp->Update(Giorno->getPosition(), summon, cam.GetCamera());
    }

    Giorno->Update(levels[currentLevel]->getTiles(), currentLevel);

    if (GoldExp->isActive() && IsKeyPressed(KEY_H) && Giorno->GetHealth() < MAX_HEALTH) {
        Giorno->setHealth(HIT);
    }

    if (enemies[currentLevel]) {
        enemies[currentLevel]->Update(levels[currentLevel]->getTiles(), currentLevel,
            Giorno, cam.GetCamera());
    }
    if (Giorno->isDead()) {
        float scale = 0.5f; 

        float destWidth = LosingDir.width * scale;
        float destHeight = LosingDir.height * scale;

        float posX = (GetScreenWidth() - destWidth) / 2;
        float posY = (GetScreenHeight() - destHeight) / 2;

        DrawTexturePro(LosingDir,
            { 0, 0, (float)LosingDir.width, (float)LosingDir.height }, 
            { posX, posY, destWidth, destHeight }, { 0, 0 }, 0.0f, WHITE );

        EndDrawing();
        WaitTime(2.0); 
        CloseWindow();
        exit(0);
    }

    for (auto& enemy : enemies) {
        if (!enemy) { continue; }
        for (int i = 0; i < GoldExp->projectileCount; i++) {
            Projectile& p = GoldExp->projectiles[i];
            if (!p.IsActive()) { continue; }

            if (p.CheckCollision(enemy->getPosition(), enemy->getWidth(),
                enemy->getHeight()) && enemy->getLevel() == currentLevel) {
                enemy->TakeDamage(HIT);
                p.Deactivate();
            }
        }
    }
    for (int i = 0; i < totalLevels; i++) {
        if (enemies[i] && enemies[i]->getPosition().y <= 0 && enemies[i]->toBeDeleted) {
            enemies[i]->Unload();
            delete enemies[i];
            enemies[i] = nullptr;
        }
    }
}


void Game::Draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    cam.Begin();

    currentLevel = levels[currentLevel]->Draw(Giorno, currentLevel, totalLevels, WinningDir);

    levels[currentLevel]->DrawTutorial(Giorno, currentLevel);
    Giorno->Draw();

    if (GoldExp && GoldExp->isActive()) {
        GoldExp->Draw();
    }

    if (enemies[currentLevel]) {
        enemies[currentLevel]->Draw();
    }
    cam.End();

    
    
    if (Giorno->getGravity() >= 0) {
        DrawText("Gravity toggled: off", 0, GetScreenHeight() / 2, FONT, PURPLE);
    }  else {
        DrawText("Gravity toggled: on", 0, GetScreenHeight() / 2, FONT, PURPLE);
    }
    DrawText("Yee Yee Ahh game", 10, 10, FONT, DARKGRAY);

    EndDrawing();
}

void Game::Unload() {
    if (!running) { return; }

    UnloadTexture(Background);
    UnloadTexture(endDir);
    UnloadTexture(dirtDir);
    UnloadTexture(grassDir);
    UnloadTexture(GiornoDir);
    UnloadTexture(LosingDir);
    UnloadTexture(WinningDir);

    if (Giorno) {
        Giorno->Unload();
        delete Giorno;
    }

    if (GoldExp) {
        GoldExp->Unload();
        delete GoldExp;
    }

    for (int i = 0; i < totalLevels; i++) {
        delete levels[i];
    }

    for (int i = 0; i < totalLevels; i++) {
        if (enemies[i]) {
            enemies[i]->Unload();
            delete enemies[i];
        }
    }


    UnloadSound(enemySummon1);
    UnloadSound(enemySummon2);
    UnloadSound(enemySummon3);
    UnloadSound(summon);
    UnloadMusicStream(MainSong);

    CloseAudioDevice();
    CloseWindow();
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
            file >> level[i][j];
        }
    }

    file.close();
    return level;
}