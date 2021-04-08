#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include <glm/gtc/matrix_transform.hpp>

#pragma once
class LightSource {
public:
	LightSource(glm::vec3 pos_, float ambient_, float diffuse_, float specular_, glm::vec3 color_);
	~LightSource();

	glm::vec3 GetPosition();
	glm::vec3 GetColor();

	float GetAmbient();
	float GetDiffuse();

	void SetPosition(glm::vec3 pos_);
	void SetColor(glm::vec3 color_);
	void SetAmbient(float ambient_);
	void SetDiffuse(float diffuse_);

private:	
	glm::vec3 position;		
	float ambient;
	float diffuse;
	float specular;
	glm::vec3 color;
};

#endif //!LIGHTSOUCRE_H