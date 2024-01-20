#pragma once
#include "Types.h"

using namespace data;
struct CollisionResult {
    bool collisionX;
    bool collisionY;
    real penetrationX;
    real penetrationY;
};
CollisionResult CheckCollisionY(const Collision& col1, const Position& pos1, const Collision& col2, const Position& pos2, double yCushion);

CollisionResult CheckCollisionX(const Collision& col1, const Position& pos1, const Collision& col2, const Position& pos2);
