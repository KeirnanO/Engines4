#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../FX/LightSource.h"
#include "../Math/Frustum.h"
#include <vector>

class Camera
{
public:
	Camera();
	~Camera();

	void SetPosition(glm::vec3 position_);
	void SetRotation(float yaw_, float pitch_);

	glm::mat4 GetView() const;
	glm::mat4 GetPerspective() const;
	glm::mat4 GetOrthographic() const;
	glm::vec3 GetPosition() const;
	float GetNearPlane() const;
	float GetFarPlane() const;

	void AddLightSource(LightSource* newLightSource);
	std::vector<LightSource*> GetLightSources() const;

	void ProcessMouseMovement(glm::vec2 offset_);
	void ProcessRotMovement(glm::vec2 offset_);
	void ProcessMouseZoom(int y_);
	
	Frustum frustum;

	glm::vec3 GetForward();
	glm::vec3 GetUp();

private:
	void UpdateCameraVectors();
	glm::vec3 position;
	glm::mat4 perspective, orthographic, view;
	float fieldOfView;
	float yaw, pitch;
	float nearPlane, farPlane;
	glm::vec3 forward, up, right, worldUp;

	std::vector<LightSource*> lights;	
};

#endif // !CAMERA_H