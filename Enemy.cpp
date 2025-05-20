#include "Enemy.h"
#include "raylib.h"
#include <cmath>
#include "EnemyStand.h"


Enemy::Enemy(Vector2 startPos, const char* texturePath, const char* standTexturePath,
    Sound summonSound, const char* projectileTexturePath, int levelID)
    : position(startPos), startPos(startPos), stand(standTexturePath, projectileTexturePath), summonSound(summonSound), levelID(levelID) {
    texture = LoadTexture(texturePath);
    projectileTexture = LoadTexture(projectileTexturePath);
}

Enemy::~Enemy() {
    Unload();
}

void Enemy::Update(int level[][TILE_COLS], int currentLevel) {}

void Enemy::Update(int level[][TILE_COLS], int currentLevel, Character* player, const Camera2D& camera) {
    // roaming logic
    if (movingRight) {
        position.x += speed;
    }
    else { 
        position.x += -speed;
    }
    if (movingRight && position.x > startPos.x + roamRange) {
        movingRight = false;
    }
    else if (!movingRight && position.x < startPos.x - roamRange) {
        movingRight = true;
        facingRight = false;
    }


    // collision with ground
    if (!OnGround) { velocityY += gravity; }
    position.y += velocityY;

    int tileX = (int)(position.x + texture.width * scale / 2) / TILE_SIZE;
    int tileY = (int)(position.y + texture.height * scale) / TILE_SIZE;

    if (tileY >= 0 && tileY < TILE_ROWS && tileX >= 0 && tileX < TILE_COLS) {
        if (level[tileY][tileX]==1) {
            position.y = tileY * TILE_SIZE - texture.height * scale;
            velocityY = 0;
            OnGround = true;
        }

        else {
            OnGround = false;
        }
    }

    // Face the player
    facingRight = player->getPosition().x > position.x;

    stand.Update(position, player, summonSound, camera, facingRight);

    float dx = position.x - player->getPosition().x;
    float dy = position.y - player->getPosition().y;
    float distSq = dx * dx + dy * dy;

    if (distSq < activationDistance * activationDistance) {
        if (shootCooldown <= 0.0f) {
            Vector2 direction = { player->getPosition().x - position.x, player->getPosition().y - position.y };
            stand.Shoot(direction);
            shootCooldown = shootRate;
        }
    }

    // reduce cooldown over time
    if (shootCooldown > 0.0f) {
        shootCooldown -= GetFrameTime();
    }

    if (health <= 0) {
        gravity *= -1.0f;
        OnGround = false;
    }

}

int Enemy::getDeathCount() {
    return 0;
}
void Enemy::setGravity(float f) {}


Vector2 Enemy::getPosition() {
    return position;
}

void Enemy::setPosition(const Vector2& vec) {
    position.x = vec.x;
    position.y = vec.y;
}

int Enemy::getLevel() const {
    return levelID;
}

void Enemy::Draw() {
    Rectangle source = { 0.0f, 0.0f, (float)texture.width, (float)texture.height };
    if (!facingRight) {
        source.width *= -1;
    }

    Rectangle dest = { position.x, position.y, texture.width * scale, texture.height * scale };
    DrawTexturePro(texture, source, dest, { 0, 0 }, 0.0f, WHITE);
    DrawEllipse(position.x + (texture.width * scale) / 2 , position.y + texture.height * scale, 15, 8, Fade(BLACK, 0.3f));
    
    stand.Draw();
    DrawHealthBar();
}

void Enemy::DrawHealthBar() const {
    float barWidth = 50;
    float barHeight = 6;
    float x = position.x + (texture.width * scale / 2) - barWidth / 2;
    float y = position.y - 10;

    float healthRatio = (float)health / (float)maxHealth;
    DrawRectangle(x, y, barWidth, barHeight, DARKGRAY);
    DrawRectangle(x, y, barWidth * healthRatio, barHeight, RED);
    DrawRectangleLines(x, y, barWidth, barHeight, BLACK);
}

void Enemy::TakeDamage(int amount) {
    health -= amount;
    if (health <= 0) {
        health = 0;
        toBeDeleted = true; 
        OnGround = false;
        Active = false;
    }
}

int Enemy::GetHealth() const {
    return health;
}

void Enemy::setHealth(int amount) {
    health += amount;
}

void Enemy::ClearProjectiles() {
    stand.ClearProjectiles();
}



void Enemy::Unload() {
    UnloadTexture(texture);
    stand.Unload();
    UnloadTexture(projectileTexture);
}