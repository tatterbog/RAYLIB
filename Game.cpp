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

    Vector2 spawnPos = { GetScreenWidth() / 2, GetScreenHeight() / 2 };
    Giorno = new Player("pngs/Giorno.png", spawnPos, 0.11f);
    GoldExp = new Stand("pngs/GoldenExperience.png");

    cam = CameraControl(Giorno->getPosition(), { WIDTH / 2.0f, HEIGHT / 2.0f }, 1.0f);

    MainSong = LoadMusicStream("songs/MainSong.wav");
    summon = LoadSound("songs/GoldenExpCall.wav");
    summon = LoadSound("songs/GoldenExpCall.wav");

    levels[0] = new Level(level0, dirtDir, grassDir, endDir, Background, MainSong);
    levels[1] = new Level(level1, dirtDir, grassDir, endDir, Background, MainSong);
    levels[2] = new Level(level2, dirtDir, grassDir, endDir, Background, MainSong);

    Sound enemySummon1 = LoadSound("songs/Metallica.wav");
    Sound enemySummon2 = LoadSound("songs/enemy2Summon.wav");
    Sound enemySummon3 = LoadSound("songs/enemy3Summon.wav");

    enemies[0] = new Enemy({(float) (GetScreenWidth() / 2 + 1600), (float)(GetScreenHeight() / 2 + 20) }, "pngs/rissoto.png", "pngs/rissotoStand.png",
        enemySummon1, "pngs/metallicaShoot.png");

    enemies[1] = new Enemy({ 800, 420 }, "pngs/enemy2.png", "pngs/enemyStand2.png",
        enemySummon2, "pngs/enemyProjectile2.png");

    enemies[2] = new Enemy({ 600, 420 }, "pngs/enemy3.png", "pngs/enemyStand3.png", 
        enemySummon3, "pngs/enemyProjectile3.png");
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

    if (enemies[currentLevel]) {
        enemies[currentLevel]->Update(levels[currentLevel]->getTiles(), currentLevel,
            Giorno->getPosition(), cam.GetCamera());

        for (int i = 0; i < MAX_ENEMY_PROJECTILES; i++) {
            Projectile& p = enemies[currentLevel]->stand.projectiles[i];
            if (p.IsActive()) {
                Vector2 projPos = p.GetPosition();
                Vector2 playerPos = Giorno->getPosition();

                float dx = projPos.x - playerPos.x;
                float dy = projPos.y - playerPos.y;
                float distSq = dx * dx + dy * dy;

                if (distSq < 30 * 30) {
                    Giorno->TakeDamage(10);
                    p.Deactivate();         
                }
            }
        }
    }
}


void Game::Draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    cam.Begin();

    currentLevel = levels[currentLevel]->Draw(Giorno, currentLevel, totalLevels);

    levels[currentLevel]->DrawTutorial(Giorno, currentLevel);
    Giorno->Draw();

    if (GoldExp && GoldExp->isActive()) {
        GoldExp->Draw();
    }

    if (enemies[currentLevel]) {
        enemies[currentLevel]->Draw();
    }
    cam.End();

    

    DrawText("Yee Yee Ahh game", 10, 10, 20, DARKGRAY);

    EndDrawing();
}

void Game::Unload() {
    if (!running) { return; }

    UnloadTexture(Background);
    UnloadTexture(endDir);
    UnloadTexture(dirtDir);
    UnloadTexture(grassDir);
    UnloadTexture(GiornoDir);

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