#include "Buffer.h"

#include "OpenGLBuffer.h"
#include "..\..\Core\Debug.h"
#include "..\3D\Mesh.h"
#include "RendererAPI.h"
#include "Renderer.h"

VertexBuffer* VertexBuffer::Create(Vertex* vertices, uint32_t size)
{
	switch (RendererAPI::GetRendererAPI()) 
	{	
		case RendererAPI::API::None: Debug::Error("RendererType::None is not supported", "Buffer.cpp", __LINE__);
		case RendererAPI::API::OpenGL: return new OpenGLVertexBuffer(vertices, size);
	}

	Debug::Error("Unknown Renderer Type", "Buffer.cpp", __LINE__);
	return nullptr;
}

IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
{
	switch (RendererAPI::GetRendererAPI())
	{
		case RendererAPI::API::None: Debug::Error("RendererType::None is not supported", "Buffer.cpp", __LINE__);
		case RendererAPI::API::OpenGL: return new OpenGLIndexBuffer(indices, size);
	}

	Debug::Error("Unknown Renderer Type", "Buffer.cpp", __LINE__);
	return nullptr;
}

void BufferLayout::CalculateOffsetAndStride()
{
	uint32_t offset = 0;
	m_Stride = 0;
	for (auto& element : m_Elements) 
	{
		element.Offset = offset;
		offset += element.Size;
		m_Stride += element.Size;
	}
}

uint32_t BufferElement::GetComponentCount() const
{
	switch (Type) {
		case ShaderDataType::Float:		return 1;
		case ShaderDataType::Float2:	return 2;
		case ShaderDataType::Float3:	return 3;
		case ShaderDataType::Float4:	return 4;
		case ShaderDataType::Mat3:		return 3 * 3;
		case ShaderDataType::Mat4:		return 4 * 4;
		case ShaderDataType::Int:		return 1;
		case ShaderDataType::Int2:		return 2;
		case ShaderDataType::Int3:		return 3;
		case ShaderDataType::Int4:		return 4;
		case ShaderDataType::Bool:		return 1;
	}

	Debug::Error("Unknown ShaderDataType", "Buffer.h", __LINE__);
	return 0;
}
