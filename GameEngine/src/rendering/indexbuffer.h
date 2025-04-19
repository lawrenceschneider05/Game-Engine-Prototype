#pragma once
#include <vector>
#include "types.h"

using std::vector;

namespace GameEngine
{
	class IndexBuffer
	{
	public:
		IndexBuffer(const vector<u32>& indices);
		~IndexBuffer();

		void bind();
		void unbind();

		u32 getCount() { return count; }
	private:
		u32 ebo;
		u32 count;
	};
}