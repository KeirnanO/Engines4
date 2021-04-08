#include "LightSource.h"

LightSource::LightSource(glm::vec3 position_, float ambient_, float diffuse_,float specular_, glm::vec3 color_) : position(glm::vec3()), ambient(0.0f), diffuse(0.0f), specular(0.0f), color(glm::vec3()) {
	position = position_;
	ambient = ambient_;
	diffuse = diffuse_;
	color = color_;
}

LightSource::~LightSource() {

}

glm::vec3 LightSource::GetPosition(){
	return position;
}

glm::vec3 LightSource::GetColor(){
	return color;
}

float LightSource::GetAmbient(){
	return ambient;
}

float LightSource::GetDiffuse(){
	return diffuse;
}

void LightSource::SetPosition(glm::vec3 position_){
	position = position_;
}

void LightSource::SetColor(glm::vec3 color_){
	color = color_;
}

void LightSource::SetAmbient(float ambient_){
	ambient = ambient_;
}

void LightSource::SetDiffuse(float diffuse_){
	diffuse = diffuse_;
}