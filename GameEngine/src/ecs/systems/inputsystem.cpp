#include "inputsystem.h"
#include "ecs/components/componenttypes.h"
#include "input/input.h"
#include "physics/physics.h"
#include <ecs/components/components.h>

namespace GameEngine
{
	void InputSystem::init()
	{
		signature = ComponentTypes::PLAYER_MOVEMENT_SIGNATURE;
	}
	void InputSystem::update(f32 dt)
	{
		for (Entity e : entities)
		{
			if (cm.hasComponent<Acceleration>(e))
			{
				Acceleration* a = cm.getComponent<Acceleration>(e);
				if (Input::isKeyPressed(GLFW_KEY_A))
				{
					a->ax -= 100 * METER * dt;
					if (a->ax <= -150 * METER * dt)
					{
						a->ax = -150 * METER * dt;
					}
				}
				else if (Input::isKeyPressed(GLFW_KEY_D))
				{
					a->ax += 100 * METER * dt;
					if (a->ax >= 150 * METER * dt)
					{
						a->ax = 150 * METER * dt;
					}
				}
				else
				{
					a->ax /= 100;
				}
			}
		}
	}
	void InputSystem::onComponentChanged()
	{
		entities = cm.getFilteredEntities(signature);
	}
}