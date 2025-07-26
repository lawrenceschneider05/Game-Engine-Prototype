#include "vertexarray.h"
#include <glad/glad.h>
#include "quadvertex.h"

namespace GameEngine
{
	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &vao);
		bind();
	}
	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &vao);
	}
	void VertexArray::bind()
	{
		glBindVertexArray(vao);
	}
	void VertexArray::unbind()
	{
		glBindVertexArray(0);
	}
	void VertexArray::setVertexBuffer(const shared_ptr<VertexBuffer>& vertexBuffer)
	{
		bind();
		vertexBuffer->bind();

		u32 stride = sizeof(QuadVertex);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, stride, (const void*)offsetof(QuadVertex, position));

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, stride, (const void*)offsetof(QuadVertex, color));

		this->vertexBuffer = vertexBuffer;
	}
	void VertexArray::setIndexBuffer(const shared_ptr<IndexBuffer>& indexBuffer)
	{
		bind();
		indexBuffer->bind();
		this->indexBuffer = indexBuffer;
	}
}