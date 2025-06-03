#include "physicssystem.h"
#include "ecs/components/componenttypes.h"
#include "log/logger.h"
#include "ecs/components/components.h"

#include <iostream>

using std::cout;

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
		possibleCollisions.clear();
		PhysicsObject tile = {};
		for (const TileCollider& t : tm.getChunk().getTiles())
		{
			tile.x = t.x;
			tile.y = t.y;
			tile.w = t.w;
			tile.h = t.h;
			tile.vx = 0;
			tile.vy = 0;
			tile.ax = 0;
			tile.ay = 0;
			possibleCollisions.push_back(tile);
		}
		for (int i = 0; i < entities.size(); i++)
		{
			Entity e = entities[i];

			PhysicsObject obj = physicsObjectFromEntity(e);

			Physics::applyGravity(obj, dt);
			applyPhysicsObject(e, obj);

			

			for (int j = i + 1; j < entities.size(); j++)
			{
				possibleCollisions.push_back(physicsObjectFromEntity(entities[j]));
			}

			
			Physics::processCollisions(obj, possibleCollisions, dt);
			applyPhysicsObject(e, obj);
			possibleCollisions.clear();
			


			Physics::processMovement(obj, dt);
			applyPhysicsObject(e, obj);
		}
	}

	void PhysicsSystem::onComponentChanged()
	{
		entities = cm.getFilteredEntities(signature);
	}
}