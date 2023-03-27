#include "VertexArray.h"
#include "OpenGLVertexArray.h"

#include "RendererAPI.h"
VertexArray* VertexArray::Create()
{
	switch (RendererAPI::GetRendererAPI())
	{
		case RendererAPI::API::None: Debug::Error("RendererType::None is not supported", "Buffer.cpp", __LINE__);
		case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
	}

	Debug::Error("Unknown Renderer Type", "Buffer.cpp", __LINE__);
	return nullptr;
}
