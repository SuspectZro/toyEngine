#pragma once
#include "Types.h"

using namespace data;
struct CollisionResult {
    bool collision;
    real penetrationX;
    real penetrationY;
};
CollisionResult CheckCollision(const Collision& col1, const Position& pos1, const Collision& col2, const Position& pos2);
