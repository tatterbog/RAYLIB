#include "Player.h"
#include <iostream>
#include "raylib.h"

Player::Player(const char* texturePath, Vector2 startPos, float startScale) :
    texture(LoadTexture(texturePath)), position(startPos), scale(startScale) {}

bool Player::isTile(int el) {
    return el == 1;
}

void Player::Update(int level[][TILE_COLS], int currentLevel)
{
    if ((IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) && (position.x < (TILE_COLS * TILE_SIZE))) {
        facingRight = 1.0f;
        position.x += 5.0f;
    }
    if ((IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) && (position.x > 0)) {
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
    
    if ((position.y > HEIGHT + 2) || (position.y < -30) ) {
        if (currentLevel == 0) {
            position.x = 0;
            position.y = 0;
            deaths++;
        }
        else {
            CloseWindow();
            exit(0);
        }
    }

}

void Player::Draw()
{
    Rectangle source = { 0.0f, 0.0f, (float)texture.width, (float)texture.height };
   
    source.width *= facingRight; 

    Rectangle dest = { position.x, position.y, texture.width * scale, texture.height * scale };
    DrawTexturePro(texture, source, dest, {0,0}, 0.0f, WHITE);
    DrawEllipse(position.x + (texture.width * scale) / 2 + 1, position.y + texture.height * scale, 15, 8, Fade(BLACK, 0.3f));
    DrawHealthBar();
}

void Player::TakeDamage(int amount) {
    health -= amount;
    if (health < 0) health = 0;
}

int Player::GetHealth() const {
    return health;
}

void Player::DrawHealthBar() const {
    float barWidth = 50;
    float barHeight = 6;
    float x = position.x + (texture.width * scale / 2) - barWidth / 2;
    float y = position.y - 10;

    float healthRatio = (float)health / maxHealth;
    DrawRectangle(x, y, barWidth, barHeight, DARKGRAY);
    DrawRectangle(x, y, barWidth * healthRatio, barHeight, RED);
    DrawRectangleLines(x, y, barWidth, barHeight, BLACK);
}

Vector2 Player::getPosition() {
    return position;
}

void Player::setPosition(const Vector2& vec) {
    position.x = vec.x;
    position.y = vec.y;
}

int Player::getDeathCount() {
    return deaths;
}


void Player::setGravity(float f) {
    gravity = f;
}

float Player::getGravity() {
    return gravity;
}

void Player::Unload()
{
    UnloadTexture(texture);
}