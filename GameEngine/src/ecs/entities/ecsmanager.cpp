#include "ecsmanager.h"
#include "ecs/components/components.h"
#include "ecs/components/componenttypes.h"

namespace GameEngine
{
	ECSManager::ECSManager(TileManager& tm) : sm(cm, tm)
	{
		size = 0;
	}

	Entity ECSManager::addEntity()
	{
		return size++;
	}

	void ECSManager::init()
	{
		// Doesn't need to be dynamic, hardcode it.
		ComponentTypes::POSITION_SIGNATURE = cm.registerComponentType<Position>();
		ComponentTypes::SIZE_SIGNATURE = cm.registerComponentType<Size>();
		ComponentTypes::VELOCITY_SIGNATURE = cm.registerComponentType<Velocity>();
		ComponentTypes::ACCELERATION_SIGNATURE = cm.registerComponentType<Acceleration>();
		ComponentTypes::TAG_SIGNATURE = cm.registerComponentType<Tag>();
		ComponentTypes::COLOR_SIGNATURE = cm.registerComponentType<Color>();

		sm.init();
	}

	void ECSManager::update(f64 dt)
	{
		sm.update(dt);
	}
	void ECSManager::render()
	{
		sm.render();
	}
}