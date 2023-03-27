#include "CollisionDetection.h"
#include "Ray.h"
#include "../Core/Engine.h"

CollisionDetection::~CollisionDetection() {
}

Ray CollisionDetection::ScreenToWorldRay(glm::vec2 mouseCoords_, float screenWidth_, float screenHeight_, Camera* camera_) {
	glm::vec4 rayStartNDC((mouseCoords_.x / screenWidth_ - 0.5f) * 2.0f, (mouseCoords_.y / screenHeight_ - 0.5f) * 2.0f, -1.0f, 1.0f);
	glm::vec4 rayEndNDC((mouseCoords_.x / screenWidth_ - 0.5f) * 2.0f, (mouseCoords_.y / screenHeight_ - 0.5f) * 2.0f, 0.0f, 1.0f);

	glm::mat4 inverse = glm::inverse(camera_->GetPerspective() * camera_->GetView());

	glm::vec4 rayStartWorld = inverse * rayStartNDC;
	rayStartWorld /= rayStartWorld.w;

	glm::vec4 rayEndWorld = inverse * rayEndNDC;
	rayEndWorld /= rayEndWorld.w;

	glm::vec3 rayDirWorld(rayEndWorld - rayStartWorld);
	rayDirWorld = glm::normalize(rayDirWorld);

	return Ray(glm::vec3(rayStartWorld), rayDirWorld);
}

bool CollisionDetection::RayObbIntersection(Ray* ray_, BoundingBox* box_) {
	glm::mat4 modelMatrix = box_->transform;
	glm::vec3 rayOrigin = ray_->origin;
	glm::vec3 rayDirection = ray_->direction;
	glm::vec3 boxMin = box_->minVert;
	glm::vec3 boxMax = box_->maxVert;

	float tMin = Engine::GetInstance()->GetCamera()->GetNearPlane();
	float tMax = Engine::GetInstance()->GetCamera()->GetFarPlane();

	glm::vec3 worldPos(modelMatrix[3].x, modelMatrix[3].y, modelMatrix[3].z);
	glm::vec3 delta = worldPos - rayOrigin;

	//X axis
	glm::vec3 xAxis(modelMatrix[0].x, modelMatrix[0].y, modelMatrix[0].z);
	float dotDelta = glm::dot(xAxis, delta);
	float dotDir = glm::dot(rayDirection, xAxis);
	if (fabs(dotDir) > 0.001f) { //Check to see if ray is orthogonal to the bounding box - this results in a dot product of 0 -- we dont want to divide by 0
		float t1 = (dotDelta + boxMin.x) / dotDir;
		float t2 = (dotDelta + boxMax.x) / dotDir;

		//Make sure t1 is min
		if (t1 > t2) {
			float w = t1;
			t1 = t2;
			t2 = w;
		}

		//Swap, following the above swap
		if (t2 < tMax) {
			tMax = t2;
		}
		if (t1 > tMin) {
			tMin = t1;
		}

		//Does not pass through both planes
		if (tMax < tMin) {
			return false;
		}
	}
	else {
		//if we are orthogonal -- check to see if we actually make it to the box  -- i think this is wrong, i dont fully understand whats happening here
		if (-dotDelta + boxMin.x > 0.0f || -dotDelta + boxMax.x < 0.0f) {
			return false;
		}
	}
	//Ray passes through the x plane of the bounding box

	//Y axis
	glm::vec3 yAxis(modelMatrix[1].x, modelMatrix[1].y, modelMatrix[1].z);
	dotDelta = glm::dot(yAxis, delta);
	dotDir = glm::dot(rayDirection, yAxis);
	if (fabs(dotDir) > 0.001f) {
		float t1 = (dotDelta + boxMin.y) / dotDir;
		float t2 = (dotDelta + boxMax.y) / dotDir;

		//Make sure t1 is min
		if (t1 > t2) {
			float w = t1;
			t1 = t2;
			t2 = w;
		}
		//Swap, following the above swap
		if (t2 < tMax) {
			tMax = t2;
		}
		if (t1 > tMin) {
			tMin = t1;
		}

		//Does not pass through both planes
		if (tMax < tMin) {
			return false;
		}
	}
	else {
		if (-dotDelta + boxMin.y > 0.0f || -dotDelta + boxMax.y < 0.0f) {
			return false;
		}
	}

	//Z axis
	glm::vec3 zAxis(modelMatrix[2].x, modelMatrix[2].y, modelMatrix[2].z);
	dotDelta = glm::dot(zAxis, delta);
	dotDir = glm::dot(rayDirection, zAxis);
	if (fabs(dotDir) > 0.001f) {
		float t1 = (dotDelta + boxMin.z) / dotDir;
		float t2 = (dotDelta + boxMax.z) / dotDir;

		//Make sure t1 is min
		if (t1 > t2) {
			float w = t1;
			t1 = t2;
			t2 = w;
		}
		//Swap, following the above swap
		if (t2 < tMax) {
			tMax = t2;
		}
		if (t1 > tMin) {
			tMin = t1;
		}

		//Does not pass through both planes
		if (tMax < tMin) {
			return false;
		}
	}
	else {
		if (-dotDelta + boxMin.z > 0.0f || -dotDelta + boxMax.z < 0.0f) {
			return false;
		}
	}
	ray_->intersectionDistance = tMin;
	return true;
}
