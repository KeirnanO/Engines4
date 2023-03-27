#ifndef RENDERERAPI_H
#define RENDERERAPI_H

#include <glm/glm.hpp>
#include <memory>
#include "VertexArray.h"

class RendererAPI {
public:
	enum API {
		None = 0,
		OpenGL
	};
public:
	virtual ~RendererAPI() = default;

	virtual void SetClearColour(const glm::vec4 colour) = 0;
	virtual void Clear() = 0;

	virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

	inline static API GetRendererAPI() { return s_RendererAPI; }
private:
	static API s_RendererAPI;
};

#endif