#ifndef OPENGLVERTEXARRAY_H
#define OPENGLVERTEXARRAY_H

#include "VertexArray.h"

class OpenGLVertexArray : public VertexArray {
public:
	OpenGLVertexArray();
	virtual ~OpenGLVertexArray() {}

	virtual void Bind() const override;
	virtual void UnBind() const override;

	virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
	virtual void AddIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

	virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const override;
	virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override;
private:
	uint32_t m_RendererID;
	std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
	std::shared_ptr<IndexBuffer> m_IndexBuffer;

};

#endif