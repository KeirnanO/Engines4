#ifndef OPENGLBUFFER_H
#define OPENGLBUFFER_H

#include "Buffer.h"
#include <glew.h>


class OpenGLVertexBuffer : public VertexBuffer {
public:
	OpenGLVertexBuffer(Vertex* vertices, uint32_t size);
	virtual ~OpenGLVertexBuffer();

	virtual void Bind() const override;
	virtual void UnBind() const override;

	virtual const BufferLayout GetLayout() const override { return m_Layout; };
	virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; };
private:
	uint32_t m_RendererID;
	BufferLayout m_Layout;
};

class OpenGLIndexBuffer : public IndexBuffer {
public:
	OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
	virtual ~OpenGLIndexBuffer();

	virtual void Bind() const override;
	virtual void UnBind() const override;

	virtual uint32_t GetCount() const { return m_Count; }
private:
	uint32_t m_RendererID;
	uint32_t m_Count;

};

#endif