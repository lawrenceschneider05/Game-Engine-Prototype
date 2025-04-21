#include "rendercommand.h"
#include <glad/glad.h>

namespace GameEngine
{
	void RenderCommand::init()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	void RenderCommand::setClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}
	void RenderCommand::clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}
	void RenderCommand::drawIndexed(const shared_ptr<VertexArray>& va)
	{
		va->bind();
		u32 count = va->getIndexBuffer()->getCount();
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	}
	void RenderCommand::setDebugMode(bool wireFrame)
	{
		if (wireFrame)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			return;
		}
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}