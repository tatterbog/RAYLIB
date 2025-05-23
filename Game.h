#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include "Character.h"
#include "Player.h"
#include "Camera.h"
#include "Stand.h"
#include "Level.h"
#include "Enemy.h"
#include "EnemyStand.h"

#define totalLevels 3

class Game {
public:
    Game();
    ~Game();
    void Run();

private:
    void Init();
    void Update();
    void Draw();
    void Unload();
    bool ShouldClose();

    int currentLevel;
    bool running;

    Character* Giorno;
    Stand* GoldExp;
    CameraControl cam;
    Level* levels[totalLevels];
    Enemy* enemies[totalLevels];
    int LevelsCompleted = 0;

    Texture2D GiornoDir;
    Texture2D dirtDir;
    Texture2D grassDir;
    Texture2D endDir;
    Texture2D Background;
    Texture2D WinningDir;
    Texture2D LosingDir;
    Music MainSong;
    Sound summon;

    Sound enemySummon1;
    Sound enemySummon2;
    Sound enemySummon3;
};

#endif
