#ifndef RENDERER_H
#define RENDERER_H

#include <memory>
#include <glm\glm.hpp>
//#include "../../Camera/Camera.h"
//#include "..\Core\Engine.h"

#include "VertexArray.h"
#include "RendererAPI.h"

class Renderer
{
public:
	static void BeginScene();
	static void EndScene();

	static void Submit(std::shared_ptr<VertexArray>& vertexArray);

	inline static RendererAPI::API GetAPI() { return RendererAPI::GetRendererAPI(); }

};


#endif
