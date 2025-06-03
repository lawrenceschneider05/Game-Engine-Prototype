#pragma once
#include "ecs/entities/entity.h"
#include <vector>
#include "ecs/components/componentmanager.h"

using std::vector;

namespace GameEngine
{
	class InputSystem
	{
	public:
		InputSystem(ComponentManager& _cm) : cm(_cm) {}
		void init();
		void update(f32 dt);

		void onComponentChanged();
	private:
		Signature signature;
		ComponentManager& cm;
		vector<Entity> entities;
	};
}