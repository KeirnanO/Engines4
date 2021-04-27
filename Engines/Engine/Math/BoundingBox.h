#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include "CollisionDetection.h"

struct BoundingBox {
	glm::vec3 maxVert, minVert;
	glm::mat4 transform;

	inline BoundingBox() {
		maxVert = minVert = glm::vec3();
		transform = glm::mat4();
	}

	inline BoundingBox(glm::vec3 maxVert_, glm::vec3 minVert_, glm::mat4 transform_) {
		maxVert = maxVert_;
		minVert = minVert_;
		transform = transform_;
	}

	inline bool Intersects(BoundingBox* box_) {
		glm::vec3 minCorner = GetTransformPoint(minVert, transform);
		glm::vec3 maxCorner = GetTransformPoint(maxVert, transform);

		glm::vec3 otherMinCorner = GetTransformPoint(box_->minVert, box_->transform);
		glm::vec3 otherMaxCorner = GetTransformPoint(box_->maxVert, box_->transform);

		//Compares ranges of of each box and returns if true if they intersect
		return (minCorner.x <= otherMaxCorner.x && maxCorner.x >= otherMinCorner.x) &&
			   (minCorner.y <= otherMaxCorner.y && maxCorner.y >= otherMinCorner.y) &&
			   (minCorner.z <= otherMaxCorner.z && maxCorner.z >= otherMinCorner.z);
	}

private:
	inline glm::vec3 GetTransformPoint(glm::vec3 point_, glm::mat4 transform_) {
		return glm::vec3(transform_[3].x, transform_[3].y, transform_[3].z) + point_;
	}
};

#endif // BOUNDINGBOX_H