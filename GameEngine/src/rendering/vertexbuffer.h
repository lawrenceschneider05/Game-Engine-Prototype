#pragma once
#include "types.h"
namespace GameEngine
{
	class VertexBuffer
	{
	public:
		//could add another constructor for static draw, may need to.
		VertexBuffer(i32 size);
		~VertexBuffer();
		void bind();
		void unbind();
		void setData(const void* data, u32 sizee);
	private:
		u32 vbo;
	};
}