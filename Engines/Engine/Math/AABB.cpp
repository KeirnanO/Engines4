#include "AABB.h"

AABB::AABB(const glm::vec3& min, const glm::vec3& max) : center{ (max + min) * 0.5f }, extents{ max.x - center.x, max.y - center.y, max.z - center.z }
{

}

AABB::AABB(const glm::vec3& inCenter, float iI, float iJ, float iK) : center{ inCenter }, extents{ iI, iJ, iK }
{

}