#include "renderer.h"
#include "quadvertex.h"
#include "types.h"
#include <memory>
#include "vertexarray.h"
#include <glm/glm.hpp>
#include "shader.h"
#include "rendercommand.h"
#include "log/logger.h"

using std::shared_ptr;
using glm::mat4;

using std::make_shared;

namespace GameEngine
{
	struct RendererState
	{
		static const u32 MAX_QUADS = 1000;
		static const u32 MAX_VERTICES = 4 * MAX_QUADS;
		static const u32 MAX_INDICES = 6 * MAX_QUADS;

		shared_ptr<VertexArray> vertexArray;
		shared_ptr<VertexBuffer> vertexBuffer;

		shared_ptr<Shader> shader;
		// how to store vertices??
		QuadVertex* bufferData;
		QuadVertex* bufferPointer;

		u32 quadIndexCount;

		mat4 viewProjection;
	} *rendererState;
	void Renderer::init()
	{
		rendererState = new RendererState();
		rendererState->vertexArray = make_shared<VertexArray>();
		rendererState->vertexBuffer = make_shared<VertexBuffer>(rendererState->MAX_VERTICES * sizeof(QuadVertex));
		rendererState->vertexArray->setVertexBuffer(rendererState->vertexBuffer);
		u32 offset = 0;
		vector<u32> indices = vector<u32>(rendererState->MAX_INDICES);
		for (unsigned int i = 0; i < RendererState::MAX_INDICES; i += 6)
		{
			indices[i + 0] = 0 + offset;
			indices[i + 1] = 1 + offset;
			indices[i + 2] = 2 + offset;
			indices[i + 3] = 2 + offset;
			indices[i + 4] = 3 + offset;
			indices[i + 5] = 0 + offset;

			offset += 4;
		}

		shared_ptr<IndexBuffer> indexBuffer = std::make_shared<IndexBuffer>(indices);
		rendererState->vertexArray->setIndexBuffer(indexBuffer);


		rendererState->bufferData = new QuadVertex[rendererState->MAX_VERTICES];
		rendererState->bufferPointer = rendererState->bufferData;
		
		rendererState->shader = make_shared<Shader>("shaders/batch.vert", "shaders/batch.frag");

	}
	void Renderer::shutdown()
	{
		delete[] rendererState->bufferData;
		delete rendererState;
	}

	void Renderer::beginScene(Camera camera)
	{
		//RenderCommand::clear();
		rendererState->viewProjection = camera.GetViewProjectionMatrix();
		rendererState->quadIndexCount = 0;
		rendererState->bufferPointer = rendererState->bufferData;
	}
	void Renderer::endScene()
	{
		flush();
	}
	void Renderer::drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		if (rendererState->quadIndexCount + 6 > rendererState->MAX_INDICES)
		{
			flush();
		}

		vec2 pos[4] = {
		position,
		position + vec2(size.x, 0.0f),
		position + size,
		position + vec2(0.0f, size.y)
		};

		for (int i = 0; i < 4; i++) {
			rendererState->bufferPointer->position = pos[i];
			rendererState->bufferPointer->color = color;
			rendererState->bufferPointer++;
		}

		rendererState->quadIndexCount += 6;
		
	}
	void Renderer::flush()
	{
		if (rendererState->quadIndexCount == 0)
		{
			rendererState->vertexBuffer->setData(nullptr, 0);
			return;
		}

		//u32 size = (u32*)rendererState->bufferPointer - (u32*)rendererState->bufferData;
		u32 size = (u8*)rendererState->bufferPointer - (u8*)rendererState->bufferData;
		//u32 fullSize = rendererState->MAX_VERTICES * sizeof(QuadVertex);
		rendererState->vertexBuffer->setData(rendererState->bufferData, size);

		rendererState->shader->bind();
		rendererState->shader->setMat4("uniformViewProj", rendererState->viewProjection);

		RenderCommand::drawIndexed(rendererState->vertexArray, rendererState->quadIndexCount);

		rendererState->quadIndexCount = 0;

		rendererState->bufferPointer = rendererState->bufferData;
	}
	void Renderer::setDebugMode(bool debug)
	{
		RenderCommand::setDebugMode(debug);
	}
}