#include "vertexbuffer.h"
#include <glad/glad.h>
namespace GameEngine
{
	VertexBuffer::VertexBuffer(i32 size)
	{
		glGenBuffers(1, &vbo);
		bind();
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	}
	
	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &vbo);
	}

	void VertexBuffer::bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
	}
	void VertexBuffer::unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	void VertexBuffer::setData(const void* data, u32 size)
	{
		bind();
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
		//glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
	}
}