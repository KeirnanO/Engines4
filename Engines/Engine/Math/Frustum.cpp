#include "Frustum.h"
#include "BoundingBox.h"

Frustum::Frustum() : matrix(glm::mat4()) {
	matrix = glm::mat4();
}

Frustum::~Frustum(){
}

//TODO:
// Allow intersection to include the scale of an object
//We only take in the position here, an object's scale will have no effect on the intersection
bool Frustum::BoxIntersection(glm::vec4 position)
{
	//If any of these identities are false, then the object is outside the frustum

	//Left Plane
	if (!(0 < glm::dot(position, (matrix[3]) + (matrix[0])))) {
		return false;
	}

	//Right Plane
	if (!(0 < glm::dot(position, (matrix[3]) - (matrix[0])))) {
		return false;
	}

	//Bottom Plane
	if (!(0 < glm::dot(position, (matrix[3]) + (matrix[1])))) {
		return false;
	}

	//Top Plane
	if (!(0 < glm::dot(position, (matrix[3]) - (matrix[1])))) {
		return false;
	}

	//Near Plane
	if (!(0 < glm::dot(position, (matrix[3]) + (matrix[2])))) {
		return false;
	}

	//Far Plane
	if (!(0 < glm::dot(position, (matrix[3]) - (matrix[2])))) {
		return false;
	}

	return true;
}

