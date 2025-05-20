#ifndef STAND_BASE_H
#define STAND_BASE_H

#include "raylib.h"

class StandBase {
public:
    virtual void Update(Vector2 targetPos, const Sound& summon, const Camera2D& camera) = 0;
    virtual void Draw() = 0;
    virtual bool isActive() const = 0;
    virtual void ClearProjectiles() = 0;
    virtual void Unload() = 0;
    virtual ~StandBase() {}
};

#endif