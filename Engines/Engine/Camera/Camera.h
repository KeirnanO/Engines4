#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
private:
	void UpdateCameraVectors();
	glm::vec3 position;
	glm::mat4 perspective, orthographic, view;
	float fieldOfView;
	float yaw, pitch;
	float nearPlane, farPlane;
	glm::vec3 forward, up, right, worldUp;
};

#endif // !CAMERA_H