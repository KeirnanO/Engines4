#include "CollisionHandler.h"
#include "../Core/Engine.h"

std::unique_ptr<CollisionHandler> CollisionHandler::collisionInstance = nullptr;
std::vector<GameObject*> CollisionHandler::prevCollisions = std::vector<GameObject*>();
OctSpatialPartition* CollisionHandler::scenePartition = nullptr;

//Can i set this in the future to lets say GetAllObjects() in scene
CollisionHandler::CollisionHandler() {
    prevCollisions.reserve(2);
}

CollisionHandler::~CollisionHandler() {
    OnDestroy();
}

CollisionHandler* CollisionHandler::GetInstance() {
    if (collisionInstance.get() == nullptr)
    {
        collisionInstance.reset(new CollisionHandler);
    }
    return collisionInstance.get();
}

void CollisionHandler::OnCreate(float worldSize_) {
    prevCollisions.clear();
    scenePartition = new OctSpatialPartition(worldSize_);
}

void CollisionHandler::AddObject(GameObject* go_) {
    scenePartition->AddObject(go_);
}

void CollisionHandler::MouseUpdate(glm::vec2 mousePosition_, int buttonType_) {
    Ray mouseRay = CollisionDetection::ScreenToWorldRay(mousePosition_, Engine::GetInstance()->GetScreenWidth(), Engine::GetInstance()->GetScreenHeight(), Engine::GetInstance()->GetCamera());

    GameObject* hitResult = nullptr;
    float shortestDistance = INFINITY;

    if (scenePartition != nullptr) {
        GameObject* hitResult = scenePartition->GetCollision(mouseRay);

        if (hitResult) {
            hitResult->SetHit(true, buttonType_);
        }

        for (auto c : prevCollisions) {
            if (hitResult != c && c != nullptr) {
                c->SetHit(false, buttonType_);
            }
        }
        prevCollisions.clear();

        if (hitResult) {
            prevCollisions.push_back(hitResult);
        }
    }
}

void CollisionHandler::OnDestroy() {
    delete scenePartition;
    scenePartition = nullptr;

    for (auto entry : prevCollisions) {
        entry = nullptr;
    }
    prevCollisions.clear();
}


