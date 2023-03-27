#ifndef BUFFER_H
#define BUFFER_H

//#include "..\..\Core\Engine.h"
#include "..\..\Core\Debug.h"

#include <vector>

enum class ShaderDataType {
	None = 0,
	Float, Float2, Float3, Float4,
	Mat3, Mat4,
	Int, Int2, Int3, Int4,
	Bool
};


struct Vertex;

static uint32_t ShaderDataTypeSize(ShaderDataType type) {
	switch (type) {
		case ShaderDataType::Float:		return 4;
		case ShaderDataType::Float2:	return 4 * 2;
		case ShaderDataType::Float3:	return 4 * 3;
		case ShaderDataType::Float4:	return 4 * 4;
		case ShaderDataType::Mat3:		return 4 * 3 * 3;
		case ShaderDataType::Mat4:		return 4 * 4 * 4;
		case ShaderDataType::Int:		return 4;
		case ShaderDataType::Int2:		return 4 * 2;
		case ShaderDataType::Int3:		return 4 * 3;
		case ShaderDataType::Int4:		return 4 * 4;
		case ShaderDataType::Bool:		return 1;
	}

	Debug::Error("Uknown ShaderDataType", "Buffer.h", __LINE__);
	return 0;
}

struct BufferElement {
	std::string Name;
	ShaderDataType Type;
	uint32_t Size;
	uint32_t Offset;

	BufferElement() : Name(""), Type(ShaderDataType::None), Size(0), Offset(0) {}
	BufferElement(ShaderDataType type, const std::string& name)
		: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0) {}

	uint32_t GetComponentCount() const;
};

class BufferLayout {
public:
	BufferLayout() {}
	BufferLayout(const std::initializer_list<BufferElement>& elements) : m_Elements(elements) {
		CalculateOffsetAndStride();
	}

	inline uint32_t GetStride() const { return m_Stride; }
	inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }

	std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
	std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
	std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
	std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
private:
	void CalculateOffsetAndStride();

	std::vector<BufferElement> m_Elements;
	uint32_t m_Stride = 0;
};

class VertexBuffer {
public:
	virtual ~VertexBuffer() {}

	virtual void Bind() const = 0;
	virtual void UnBind() const = 0;

	virtual const BufferLayout GetLayout() const = 0;
	virtual void SetLayout(const BufferLayout& layout) = 0;

	static VertexBuffer* Create(Vertex* vertices, uint32_t size);
};

class IndexBuffer {
public:
	virtual ~IndexBuffer() {}

	virtual void Bind() const = 0;
	virtual void UnBind() const = 0;

	virtual uint32_t GetCount() const = 0;
	
	static IndexBuffer* Create(uint32_t* indices, uint32_t size);
};

#endif