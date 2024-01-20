#pragma once

#include "Types.h"
#include "CollisionSystem.h"
#include <algorithm>
using namespace data;


CollisionResult CheckCollisionX(const Collision& col1, const Position& pos1, const Collision& col2, const Position& pos2) {
    CollisionResult result;

    // Adjusted rectangles based on scale
    real left1 = pos1.x - (col1.width);
    real right1 = pos1.x + (col1.width);
    real top1 = pos1.y - (col1.height);
    real bottom1 = pos1.y + (col1.height);

    real left2 = pos2.x - (col2.width);
    real right2 = pos2.x + (col2.width);
    real top2 = pos2.y - (col2.height);
    real bottom2 = pos2.y + (col2.height);

    // Check for overlap in the y axis
    result.collisionX = !(right1 < left2 || left1 > right2 || bottom1 < top2 || top1 > bottom2);

    if (result.collisionX) {
        real xOverlap = std::min(right1, right2) - std::max(left1, left2);
        result.penetrationX = xOverlap;
    }
    else {
        result.penetrationX = 0.0;
    }
    result.collisionY = false;
    result.penetrationY = 0.0;
    
    return result;
}


CollisionResult CheckCollisionY(const Collision& col1, const Position& pos1, const Collision& col2, const Position& pos2, double yCushion) {
    CollisionResult result;

    // Adjusted rectangles based on scale
    real left1 = pos1.x - (col1.width);
    real right1 = pos1.x + (col1.width);
    real top1 = pos1.y - (col1.height) - yCushion;  // Add cushion to the top
    real bottom1 = pos1.y + (col1.height) + yCushion;  // Add cushion to the bottom

    real left2 = pos2.x - (col2.width);
    real right2 = pos2.x + (col2.width);
    real top2 = pos2.y - (col2.height);
    real bottom2 = pos2.y + (col2.height);

    // Check for overlap in the y axis
    result.collisionY = !(right1 < left2 || left1 > right2 || bottom1 < top2 || top1 > bottom2);

    if (result.collisionY) {
        real yOverlap = std::min(bottom1, bottom2) - std::max(top1, top2);
        result.penetrationY = yOverlap;
    }
    else {
        result.penetrationY = 0.0;
    }

    result.collisionX = false;
    result.penetrationX = 0.0;

    return result;
}






