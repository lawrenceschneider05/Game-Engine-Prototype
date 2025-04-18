#include "physicssystem.h"
#include "componenttypes.h"
#include "log/logger.h"
#include "components.h"

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
		for (auto e : entities)
		{
			Position& p = *cm.getComponent<Position>(e);
			Size& s = *cm.getComponent<Size>(e);
			Velocity& v = *cm.getComponent<Velocity>(e);
			Acceleration& a = *cm.getComponent<Acceleration>(e);

			v.vx += a.ax;
			v.vy += a.ay;

			p.x += v.vx;
			p.y += v.vy;

			
		}
	}
	void PhysicsSystem::onComponentChanged()
	{
		entities = cm.getFilteredEntities(signature);
	}
}