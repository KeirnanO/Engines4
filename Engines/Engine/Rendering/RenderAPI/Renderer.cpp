#include "Renderer.h"

#include "RenderCommand.h"

void Renderer::BeginScene()
{
}

void Renderer::EndScene()
{
}

void Renderer::Submit(std::shared_ptr<VertexArray>& vertexArray)
{
	vertexArray->Bind();
	RenderCommand::DrawIndexed(vertexArray);
}
