#include "CollisionHandler.h"
#include "../Core/Engine.h"

std::unique_ptr<CollisionHandler> CollisionHandler::collisionInstance = nullptr;
std::vector<GameObject*> CollisionHandler::prevCollisions = std::vector<GameObject*>();
OctSpatialPartition* CollisionHandler::scenePartition = nullptr;
std::list<GameObject*> gameObjects = std::list<GameObject*>();

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
    gameObjects.push_back(go_);
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
void CollisionHandler::Update(const float deltaTime) {
    ApplyGravity();
    ApplyConstraint();
    UpdatePositions(deltaTime);    
}
    

void CollisionHandler::UpdatePositions(const float deltaTime) {
    /*for (GameObject* go_ : gameObjects) {
        Rigidbody* rb = go_->GetComponent<Rigidbody>();

        if (rb != nullptr) {
            rb->UpdatePositions(deltaTime);
        }
        
    }*/
}

void CollisionHandler::ApplyGravity() {
    /*for (GameObject* go_ : gameObjects) {
        Rigidbody* rb = go_->GetComponent<Rigidbody>();

        if (rb != nullptr) {
            rb->Accelerate(gravity);
        }
        
    }   */
}

void CollisionHandler::ApplyConstraint() {
    glm::vec3 position = { 0.0f,0.0f,0.0f };
    float radius = 10.0f;

    /*for (GameObject* go_ : gameObjects) {
        Rigidbody* rb = go_->GetComponent<Rigidbody>();

        if (rb != nullptr) {
            const glm::vec3 to_obj = go_->GetPosition() - position;
            const float distance = glm::length(to_obj);

            if (distance > radius) {
                const glm::vec3 n = to_obj / distance;
                rb->position = (position + n * (distance - 50.0f));

                rb->Accelerate(-n);
            }
        }
        
    }*/
}

void CollisionHandler::Step(const float deltaTime_) {
    /*for (GameObject* go_ : gameObjects) {
        Rigidbody* rb = go_->GetComponent<Rigidbody>();

        if (rb != nullptr) {
            rb->AddForce(gravity);
        }
    }
    */
}


void CollisionHandler::OnDestroy() {
    delete scenePartition;
    scenePartition = nullptr;

    for (auto entry : prevCollisions) {
        entry = nullptr;
    }
    prevCollisions.clear();
}


