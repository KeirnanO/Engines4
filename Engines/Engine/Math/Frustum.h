#ifndef FRUSTUM_H
#define FRUSTUM_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define NEAR  0
#define FAR   1
#define LEFT  2
#define RIGHT 3
#define UP    4
#define DOWN  5


class Frustum
{
public:
	Frustum();
	~Frustum();

	/// <summary>
	/// If M is the projection matrix, we get the clipping planes in world space				                     
	/// If M is view matrix * projection matrix, we get the clippping planes in view space
	/// If M is model matrix * view matrix * projection matrix, we get the clipping planes in object space 
	/// Where M is martrix
	/// </summary>
	glm::mat4 matrix;

	bool BoxIntersection(glm::vec4 position);

};

#endif // !FRUSTUM_H
