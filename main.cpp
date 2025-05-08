#include <iostream>
#include "raylib.h"

#include "Player.h"
#include "Character.h"
#include "Camera.h"
#include "Stand.h"


int main() {
    int level[TILE_ROWS][TILE_COLS] = {
    {0},
    {0},
    {0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,2,0,1,0,0,0},
    {0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,2,2,2,2,2,2,2,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,2,2,2,2,2,2,2,2}
    };

    InitWindow(WIDTH, HEIGHT, "Raylib Test");
    Texture2D GiornoDir = LoadTexture("Giorno.png");
    Vector2 v2 = { GetScreenWidth() / 2, GetScreenHeight() / 2};
    SetTargetFPS(60);

   
    Character* Giorno = new Player("Giorno.png", v2, 0.11f);
    
    if (GiornoDir.id == 0) {
        std::cout << "Failed to load texture!" << '\n';
    }
    Texture2D dirtDir = LoadTexture("dirt.png");
    Texture2D grassDir = LoadTexture("grass.png");

    CameraControl cam(Giorno->getPosition(), { WIDTH / 2.0f, HEIGHT / 2.0f }, 1.0f);

    Stand* GoldExp = new Stand("GoldenExperience.png");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        cam.Begin();
        cam.Update(Giorno->getPosition());

        GoldExp->Update(Giorno->getPosition());

        for (int i = 0; i < TILE_ROWS; i++) {
            for (int j = 0; j < TILE_COLS; j++) {
                if (level[i][j] == 2) {
                    DrawTexture(dirtDir, j * TILE_SIZE, i * TILE_SIZE, WHITE);
                }
                else if (level[i][j] == 1) {
                    DrawTexture(grassDir, j * TILE_SIZE, i * TILE_SIZE, WHITE);
                }
                else{
                    DrawRectangle(j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE, SKYBLUE);
                }
            }
        }

        

        Giorno->Update(level);
        Giorno->Draw();
        
        if (GoldExp->isActive()) {
            GoldExp->Draw();
        }
        DrawText("Yee Yee Ahh game", 10, 10, 20, DARKGRAY);
        cam.End();
        EndDrawing();
    }

    UnloadTexture(dirtDir);
    UnloadTexture(grassDir);
    Giorno->Unload();
    GoldExp->Unload();


    delete Giorno;
    delete GoldExp;
    CloseWindow();
    return 0;
}

