#include "rendersystem.h"
#include "ecs/components/componenttypes.h"
#include "ecs/components/components.h"
#include "rendering/renderer.h"

namespace GameEngine
{
	void RenderSystem::init()
	{
		signature = ComponentTypes::POSITION_SIGNATURE | 
					ComponentTypes::SIZE_SIGNATURE | 
					ComponentTypes::COLOR_SIGNATURE;
	}
	void RenderSystem::render()
	{
		Logger::log(LOG_SUCCESS, entities.size());
		for (auto e : entities)
		{
			Position& p = *cm.getComponent<Position>(e);
			Size& s = *cm.getComponent<Size>(e);
			Color& c = *cm.getComponent<Color>(e);

			Renderer::drawQuad({ p.x, p.y }, { s.w, s.h }, { c.r, c.g, c.b, c.a });
			Logger::log(LOG_SUCCESS, "entity drawn");
		}
	}
	void RenderSystem::onComponentChanged()
	{
		entities = cm.getFilteredEntities(signature);
	}
}