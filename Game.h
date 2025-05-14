#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include "Character.h"
#include "Player.h"
#include "Camera.h"
#include "Stand.h"
#include "Level.h"

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

    Texture2D GiornoDir;
    Texture2D dirtDir;
    Texture2D grassDir;
    Texture2D endDir;
    Texture2D Background;
    Music MainSong;
    Sound summon;
};

#endif
