#include "physicssystem.h"
#include "ecs/components/componenttypes.h"
#include "log/logger.h"
#include "ecs/components/components.h"


namespace GameEngine
{
	PhysicsSystem::~PhysicsSystem()
	{
	}
	void PhysicsSystem::init()
	{
		
		signature = ComponentTypes::POSITION_SIGNATURE | ComponentTypes::SIZE_SIGNATURE | 
					ComponentTypes::VELOCITY_SIGNATURE | ComponentTypes::ACCELERATION_SIGNATURE;
		entities = cm.getFilteredEntities(signature);
	}

	void PhysicsSystem::update(f64 dt)
	{
		
		for (int i = 0; i < entities.size(); i++)
		{
			Entity e = entities[i];

			PhysicsObject obj = physicsObjectFromEntity(e);

			Physics::applyGravity(obj, dt);
			applyPhysicsObject(e, obj);

			Physics::processMovement(obj, dt);
			applyPhysicsObject(e, obj);

			for (int j = i + 1; j < entities.size(); j++)
			{
				possibleCollisions.push_back(physicsObjectFromEntity(entities[j]));
			}

			Physics::processCollisions(obj, possibleCollisions, dt);
			possibleCollisions = {};
			
		}
	}

	void PhysicsSystem::onComponentChanged()
	{
		entities = cm.getFilteredEntities(signature);
	}
}