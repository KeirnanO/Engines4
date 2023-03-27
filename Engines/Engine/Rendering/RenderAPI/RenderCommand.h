#ifndef RENDERCOMMAND_H
#define RENDERCOMMAND_H


#include "RendererAPI.h"

class RenderCommand {
public:
	inline static void SetClearColour(const glm::vec4 colour) {
		s_RendererAPI->SetClearColour(colour);
	}

	inline static void Clear() {
		s_RendererAPI->Clear();
	}

	inline static void DrawIndexed(std::shared_ptr<VertexArray>& vertexArray) {
		s_RendererAPI->DrawIndexed(vertexArray);
	}
private:
	static RendererAPI* s_RendererAPI;
};

#endif