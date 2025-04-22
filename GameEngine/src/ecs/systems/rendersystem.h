#pragma once
#include "types.h"
#include <ecs/components/componentmanager.h>

namespace GameEngine
{
	class RenderSystem
	{
	public:
		RenderSystem(ComponentManager& _cm) : cm(_cm) {};

		void init();
		void render();
		void onComponentChanged();
	private:
		ComponentManager& cm;
		vector<Entity> entities;
		Signature signature;
	};
}