#pragma once
#include <memory>
#include "vertexbuffer.h"
#include "indexbuffer.h"

using std::shared_ptr;

namespace GameEngine
{
	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();
		void bind();
		void unbind();
		void setVertexBuffer(const shared_ptr<VertexBuffer>& vertexBuffer);
		void setIndexBuffer(const shared_ptr<IndexBuffer>& indexBuffer);

		const shared_ptr<IndexBuffer>& getIndexBuffer() { return indexBuffer; }
	private:
		u32 vao;
		shared_ptr<VertexBuffer> vertexBuffer;
		shared_ptr<IndexBuffer> indexBuffer;
	};
}