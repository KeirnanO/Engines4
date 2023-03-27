#ifndef AABB_H
#define AABB_H

#include "BoundingBox.h"


struct AABB : public BoundingBox
{
public:
    glm::vec3 center;
    glm::vec3 extents;

    AABB(const glm::vec3& min, const glm::vec3& max);
    AABB(const glm::vec3& inCenter, float iI, float iJ, float iK);
};

#endif // !AABB_H