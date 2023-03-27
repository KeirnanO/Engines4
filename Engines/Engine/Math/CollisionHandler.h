#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#include "Ray.h"
#include "../Rendering/3D/GameObject.h"
#include "../Rendering/Gui/GUIObject.h"
#include "../Core/OctSpatialPartition.h"
#include <list>

class CollisionHandler {
public:
	CollisionHandler(const CollisionHandler&) = delete;
	CollisionHandler(CollisionHandler&&) = delete;
	CollisionHandler& operator=(const CollisionHandler&) = delete;
	CollisionHandler&& operator=(CollisionHandler&&) = delete;

	static CollisionHandler* GetInstance();

	void OnCreate(float worldSize_);
	void AddObject(GameObject* go_);
	void MouseUpdate(glm::vec2 mousePosition_, int buttonType_);
	void Update(const float deltaTime);
	void UpdatePositions(const float deltaTime);
	void ApplyGravity();
	void ApplyConstraint();
	void OnDestroy();
	void Step(const float deltaTime_);
private:
	CollisionHandler();
	~CollisionHandler();

	static std::unique_ptr<CollisionHandler> collisionInstance;
	friend std::default_delete<CollisionHandler>;

	static std::vector<GameObject*> prevCollisions;
	static std::vector<GUIObject*> prevGUICollisions;
	static OctSpatialPartition* scenePartition;
	std::list<GameObject*> gameObjects;

	glm::vec3 gravity = { 0.0f, -0.01f, 0.0f };
};

#endif // !COLLISIONHANDLER_H
