#ifndef PHYSICSSOLVER_H
#define PHYSICSSOLVER_H

#include "../Rendering/3D/GameObject.h"
#include "../Components/Rigidbody.h"
#include <vector>

class PhysicsSolver
{
public:
    PhysicsSolver() = default;

    void addObject(Rigidbody* rigidbody_)
    {
        m_objects.emplace_back(rigidbody_);
    }

    void update(float deltaTime)
    {
        m_frame_dt = deltaTime;
        m_time += m_frame_dt;
        const float step_dt = getStepDt();
        for (uint32_t i{ m_sub_steps }; i--;) {
            applyGravity();
            checkCollisions(step_dt);
            applyConstraint();
            updateObjects(step_dt);
        }
    }

    void setSimulationUpdateRate(uint32_t rate)
    {
        m_frame_dt = 1.0f / static_cast<float>(rate);
    }

    void setConstraint(glm::vec3  position, float radius)
    {
        m_constraint_center = position;
        m_constraint_radius = radius;
    }

    void setSubStepsCount(uint32_t sub_steps)
    {
        m_sub_steps = sub_steps;
    }

    void setObjectVelocity(Rigidbody& object, glm::vec3  v)
    {
        object.setVelocity(v, getStepDt());
    }

    const std::vector<Rigidbody*> getObjects() const
    {
        return m_objects;
    }

    glm::vec3 getConstraint() const
    {
        return { m_constraint_center.x, m_constraint_center.y, m_constraint_radius };
    }

    uint32_t getObjectsCount() const
    {
        return m_objects.size();
    }

    float getTime() const
    {
        return m_time;
    }

    float getStepDt() const
    {
        return m_frame_dt / static_cast<float>(m_sub_steps);
    }

private:
    uint32_t                  m_sub_steps = 8;
    glm::vec3                 m_gravity = { 0.0f, -20.81f, 0.0f };
    glm::vec3                 m_constraint_center;
    float                     m_constraint_radius = 10.0f;
    std::vector<Rigidbody*>   m_objects;
    float                     m_time = 0.0f;
    float                     m_frame_dt = 0.0f;

    void applyGravity()
    {
        for (auto& obj : m_objects) {

            if(obj->isKinematic)
                obj->Accelerate(m_gravity * obj->mass);
        }
    }

    void checkCollisions(float dt)
    {
        const float    response_coef = 0.15f;
        const uint32_t objects_count = m_objects.size();
        // Iterate on all objects
        for (uint32_t i{ 0 }; i < objects_count; ++i) {
            Rigidbody* object_1 = m_objects[i];
            // Iterate on object involved in new collision pairs
            for (uint32_t k{ i + 1 }; k < objects_count; ++k) {
                Rigidbody* object_2 = m_objects[k];
                const glm::vec3  v = object_1->position - object_2->position;
                const float        dist2 = v.x * v.x + v.y * v.y;
                const float        min_dist = object_1->getRadius() + object_2->getRadius();
                // Check overlapping
                if (dist2 < min_dist * min_dist) {
                    const float        dist = sqrt(dist2);
                    const glm::vec3  n = v / dist;
                    const float mass_ratio_1 = object_1->mass;
                    const float mass_ratio_2 = object_2->mass;
                    const float delta = 0.5f * response_coef * (dist - min_dist);
                    // Update positions
                    object_1->position -= n * (mass_ratio_2 * delta);
                    object_2->position += n * (mass_ratio_1 * delta);
                }
            }
        }
    }

    void applyConstraint()
    {
        for (auto& obj : m_objects) {
            const glm::vec3  v = m_constraint_center - obj->position;
            const float        dist = sqrt(v.x * v.x + v.y * v.y);
            if (dist > (m_constraint_radius - obj->getRadius())) {
                const glm::vec3  n = v / dist;
                obj->position = m_constraint_center - n * (m_constraint_radius - obj->getRadius());
            }
        }
    }

    void updateObjects(float dt)
    {
        for (auto& obj : m_objects) {
            obj->Update(dt);
        }
    }
};

#endif // !PHYSICSSOLVER_H