#include "ecsmanager.h"
#include "components.h"
#include "componenttypes.h"

namespace GameEngine
{
	ECSManager::ECSManager() : sm(cm)
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

		sm.init();
	}

	void ECSManager::update(f64 dt)
	{
		sm.update(dt);
	}
}