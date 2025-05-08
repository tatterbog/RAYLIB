#include "Player.h"
#include <iostream>
#include "raylib.h"

Player::Player(const char* texturePath, Vector2 startPos, float startScale) :
    texture(LoadTexture(texturePath)), position(startPos), scale(startScale) {}

bool Player::isTile(int el) {
    return el == 1;
}
void Player::Update(int level[][TILE_COLS])
{
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        facingRight = 1.0f;
        position.x += 5.0f;
    }
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        facingRight = -1.0f;
        position.x -= 5.0f;
    }

    if (!OnGround) { velocityY += gravity; }
    position.y += velocityY;

    int tileX = (int)(position.x + texture.width * scale / 2) / TILE_SIZE;
    int tileY = (int)(position.y + texture.height * scale) / TILE_SIZE;

    if (tileY >= 0 && tileY < TILE_ROWS && tileX >= 0 && tileX < TILE_COLS) {
        if (isTile(level[tileY][tileX])) {
            position.y = tileY * TILE_SIZE - texture.height * scale;
            velocityY = 0;
            OnGround = true;
        }
        else {
            OnGround = false;
        }
    }

    if (IsKeyPressed(KEY_G)) {
        gravity *= -1.0f;
    }

    if (IsKeyPressed(KEY_SPACE) && OnGround) {
        velocityY = -6.5f;
        OnGround = false;
    }

    if (position.y > HEIGHT + 2 || position.y < -30) {
        CloseWindow();
        exit(0);
    }

    
}

void Player::Draw()
{
    Rectangle source = { 0.0f, 0.0f, (float)texture.width, (float)texture.height };
   
    source.width *= facingRight; 

    Rectangle dest = { position.x, position.y, texture.width * scale, texture.height * scale };
    DrawTexturePro(texture, source, dest, {0,0}, 0.0f, WHITE);
    DrawEllipse(position.x + (texture.width * scale) / 2 + 1, position.y + texture.height * scale, 15, 8, Fade(BLACK, 0.3f));
}
Vector2 Player::getPosition() {
    return position;
}

float Player::getGravity() {
    return gravity;
}

void Player::Unload()
{
    UnloadTexture(texture);
}